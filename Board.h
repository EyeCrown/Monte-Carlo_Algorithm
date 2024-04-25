#pragma once
#include <chrono>
#include <random>

#include "Player.h"

static int BASE_HP = 20;
static int BASE_MANA = 0;

struct PlayerData
{
    int hp = 0;
    int mana = 0;
    
    std::vector<Card*> deck;
    std::vector<Card*> hand[MAX_CARD_COST+1];
    std::vector<std::pair<int, Card*>> board;

    PlayerData(std::vector<Card*>* playerDeck)
    {
        this->hp = BASE_HP;
        this->mana = BASE_MANA;
        for (int i=0; i<playerDeck->size(); i++)
            deck.push_back(playerDeck->at(i));
        for (int i=MIN_CARD_COST; i<=MAX_CARD_COST; i++)
            if (!hand[i].empty())
                hand[i].clear();
        
        board.clear();
        InitHand();
    }

    constexpr void InitHand()
    {
        for (int i=0; i<4; i++)
        {
            this->hand[deck.back()->_cost].push_back(deck.back());
            this->deck.pop_back();
        }
    }

    // Draw card
    void DrawCard()
    {
        const int randID = rand() % deck.size();
        Card* card = deck.at(randID);
        hand[card->_cost].push_back(card);
        this->deck.erase(deck.begin() + randID);
    }

    void CanPlay_Rec()
    {
        const int currMana = std::min(mana, MAX_CARD_COST);
        for (int i = currMana; i>=MIN_CARD_COST; i--)
        {
            if(!hand[currMana].empty()) // If can a play then play a card
            {
                const int rand_id = rand() % hand[currMana].size();
                board.push_back(std::pair(hand[currMana][rand_id]->_def, hand[currMana][rand_id]));
                hand[currMana].erase(hand[currMana].begin()+rand_id);
                mana -= currMana;
                //std::cout << this << " plays " << board.back().second->ToString() << std::endl;
                CanPlay_Rec();
                break;
            }
        }
    }

    void AttackNoExtraFeature(PlayerData* opponent)
    {
        for (int i=0; i<board.size(); i++)
            opponent->hp -= board[i].second->_atk;
    }

    void AttackOnlyTauntFeature(PlayerData* opponent)
    {
        for (int indexPlayer=0; indexPlayer < board.size(); indexPlayer++)
        {
            bool canAttackPlayer = true;
            for (int indexOpp=0; indexOpp<opponent->board.size(); indexOpp++)
            {
                if (opponent->board.at(indexOpp).second->_hasTaunt && opponent->board.at(indexOpp).first > 0)
                {
                    opponent->board.at(indexOpp).first -= board.at(indexPlayer).second->_atk;
                    board.at(indexPlayer).first -= opponent->board.at(indexOpp).second->_atk;
                    //std::cout << "Taunt has been used." << std::endl;
                    canAttackPlayer = false;
                }

                if (board.at(indexPlayer).first <= 0)
                    break;  // if card is dead break
            }

            if (canAttackPlayer && board.at(indexPlayer).first > 0) // if card alive then do damage
            {
                opponent->hp -= board.at(indexPlayer).second->_atk;
                //std::cout << "Card ID°" << std::to_string( board.at(indexPlayer).second->ID) << " deals " << std::to_string(board.at(indexPlayer).second->_atk) << " damage." << std::endl;
            }
        }

        ClearDeadCards();
        opponent->ClearDeadCards();
    }

    void AttackAllFeatures(PlayerData* opponent)
    {
        for (int indexPlayer=0; indexPlayer < board.size(); indexPlayer++)
        {
            std::pair<int, Card*>* card = &board.at(indexPlayer);
            bool canAttackPlayer = true;

            for (int indexOpp=0; indexOpp<opponent->board.size(); indexOpp++)
            {
                std::pair<int, Card*>* oppCard = &opponent->board.at(indexOpp);

                // Taunt & Distortion
                if (oppCard->second->_hasTaunt &&
                (!card->second->_hasDistortion || oppCard->second->_hasDistortion && card->second->_hasDistortion))
                {
                    // First Strike
                    if (card->second->_hasFirstStrike && !oppCard->second->_hasFirstStrike)
                    {
                        oppCard->first -= card->second->_atk;

                        if (oppCard->first > 0)
                            card->first -= oppCard->second->_atk;
                        // Trample
                        else if (card->second->_hasTrample)
                            opponent->hp -= abs(oppCard->first);
                    }
                    else if (!card->second->_hasFirstStrike && oppCard->second->_hasFirstStrike)
                    {
                        card->first -= oppCard->second->_atk;
                        if (card->first > 0)
                        {
                            oppCard->first -= card->second->_atk;
                            // Trample
                            if (card->second->_hasTrample && oppCard->first <= 0)
                                opponent->hp -= abs(oppCard->first);
                        }
                    }
                    else
                    {
                        oppCard->first -= card->second->_atk;
                        card->first -= oppCard->second->_atk;
                    }
                    canAttackPlayer = false;
                }

                if (card->first <= 0)
                    break;  // if card is dead break
            }

            if (canAttackPlayer && card->first > 0) // if card alive then do damage
            {
                opponent->hp -= card->second->_atk;
                //std::cout << "Card ID°" << std::to_string( board.at(indexPlayer).second->ID) << " deals " << std::to_string(board.at(indexPlayer).second->_atk) << " damage." << std::endl;
            }
        }

        ClearDeadCards();
        opponent->ClearDeadCards();
    }

    void ClearDeadCards()
    {
        if (!board.empty())
        {
            int i=0;
            while (i < board.size())
            {
                if (board.at(i).first <= 0)
                {
                    board.erase(board.begin() + i);
                }
                else
                {
                    board[i].first = board[i].second->_def;
                    i++;
                }
            }
        }
    }
};

class Board
{
public:
    std::chrono::time_point<std::chrono::system_clock> start, end;

    Player* player1;
    Player* player2;
    
    PlayerData* _playerData1;
    PlayerData* _playerData2;
    
    int nbTurn;
    int nbWinP1;

    int poolMana;

    Board(Player* p1, Player* p2)
    {
        player1 = p1;
        player2 = p2;
    }
    
    // Init game
    void Init(Player& p1, Player& p2)
    {
        _playerData1 = new PlayerData(p1._Deck);
        _playerData2 = new PlayerData(p2._Deck);
    }

    // Start Game
    void DoLoop(int nbGame, int& totalNbTurn, int& resNbWin)
    {
        nbWinP1 = 0;
        for (int i=0; i < nbGame/2; i++)
        {
            DoGame(player1, player2);
            totalNbTurn += nbTurn;
        }
        for (int i=0; i < nbGame/2; i++)
        {
            DoGame(player2, player1);
            totalNbTurn += nbTurn;
        }
        resNbWin += nbWinP1;

    }
    
    
    // Game Logic
    void DoGame(Player* player1, Player* player2)
    {
        nbTurn = 0, poolMana = 0;
        Init(*player1, *player2);
        
        while (_playerData1->hp > 0 && _playerData2->hp > 0)
        {
            poolMana++;
            if(_playerData1->hp > 0)
                Turn(_playerData1, _playerData2);
            if (_playerData2->hp > 0)
                Turn(_playerData2, _playerData1);
            nbTurn++;
        }
        
        if (_playerData1->hp > 0 && player1->ID == 1 || _playerData2->hp > 0 && player2->ID == 1)
            nbWinP1++;
    }

    // Game turn
    void Turn(PlayerData* player, PlayerData* opponent)
    {
        player->mana = poolMana;
        player->DrawCard();
        player->CanPlay_Rec();
        //player->AttackNoExtraFeature(opponent);
        //player->AttackNoExtraFeature(opponent);
        player->AttackAllFeatures(opponent);
    }
};
