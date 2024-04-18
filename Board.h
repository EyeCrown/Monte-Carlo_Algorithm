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

    
    
    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> board;

    PlayerData(std::vector<Card>* playerDeck)
    {
        this->hp = BASE_HP;
        this->mana = BASE_MANA;
        for (auto itr = playerDeck->begin(); itr != playerDeck->end(); itr++)
            deck.push_back(*itr);

        hand.clear();
        board.clear();
    }

    void InitHand()
    {
        for (int i=0; i<4; i++)
        {
            this->hand.push_back(deck.back());
            this->deck.pop_back();
        }
    }

    // Draw card
    void DrawCard()
    {
        int randID = rand() % deck.size();
        
        this->hand.push_back(deck.at(randID));
        this->deck.erase(deck.begin() + randID);
    }

    bool CanPlay()
    {
        for (auto itr = hand.begin(); itr != hand.end(); itr++)
        {
            if (mana >= itr->_cost)
                return true;
        }
        return false;
    }
    
    // Play card
    void PlayCard()
    {
        Card card = *hand.begin();
        auto itr = hand.begin();
        
        for (auto itr = hand.begin(); itr != hand.end(); itr++)
        {
            if (card._cost <= mana)
                card = CardWithHigherCost(*itr, card);
        }

        const auto position = std::find(hand.begin(), hand.end(), card);
        mana -= position->_cost;
        board.push_back(*position);
        hand.erase(position);
    }

    void Attack(PlayerData* opponent)
    {
        int sumDamage = 0;
        for (auto itr = board.begin(); itr != board.end(); itr++)
            sumDamage += itr->_atk;

        opponent->hp -= sumDamage;
    }
};

class Board
{
public:
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    std::vector<Card>* _DeckPlayer1;
    std::vector<Card>* _DeckPlayer2;

    Player* player1;
    Player* player2;
    
    PlayerData* _playerData1;
    PlayerData* _playerData2;
    
    int nbTurn;
    int nbWinP1;
    
    
    // Init game
    void Init(Player& p1, Player& p2)
    {
        _playerData1 = new PlayerData(p1._Deck);
        _playerData2 = new PlayerData(p2._Deck);
    }

    // Start Game
    int DoLoop(Player* p1, Player* p2, int nbGame)
    {
        player1 = p1;
        player2 = p2;
        nbWinP1 = 0;
        
        for (int i=0; i < nbGame/2; i++)
        {
            DoGame(p1, p2);
            //sumTurns += boardGame->nbTurn;
        }
        for (int i=0; i < nbGame/2; i++)
        {
            DoGame(p2, p1);
            //sumTurns += boardGame->nbTurn;
        }

        return nbWinP1;
    }
    
    
    // Game Logic
    void DoGame(Player* player1, Player* player2)
    {
        Init(*player1, *player2);
        
        nbTurn = 0;

        _playerData1->InitHand();
        _playerData2->InitHand();

       
        //start = std::chrono::system_clock::now();
        while (_playerData1->hp > 0 && _playerData2->hp > 0)
        {
            if(_playerData1->hp > 0)
                Turn(_playerData1, _playerData2);
            else
                return 0;
            
            if (_playerData2->hp > 0)
                Turn(_playerData2, _playerData1);
            else
                return 1;
            nbTurn++;
        }
        // end = std::chrono::system_clock::now();
        // std::chrono::duration<double> elapsed_seconds = end - start;
        // std::cout << "Duration game " << elapsed_seconds.count() << " s" << std::endl;
        
        if (_playerData1->hp > 0 && player1->ID == 1)
            nbWinP1++;

        if (_playerData2->hp > 0 && player2->ID == 1)
            nbWinP1++;
    }

    // Game turn
    void Turn(PlayerData* player, PlayerData* opponent)
    {
        
        player->mana++;
        player->DrawCard();

        while (player->CanPlay())
            player->PlayCard();

        player->Attack(opponent);
    }
};
