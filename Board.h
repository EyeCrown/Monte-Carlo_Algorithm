#pragma once
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

    // Draw card
    void DrawCard()
    {   
        this->hand.push_back(deck.back());
        this->deck.pop_back();
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
    std::vector<Card>* _DeckPlayer1;
    std::vector<Card>* _DeckPlayer2;

    Player* player1;
    Player* player2;
    
    PlayerData* _player1;
    PlayerData* _player2;
    
    int nbTurn;

    
    // Init game
    void Init(Player& player1, Player& player2)
    {
        _player1 = new PlayerData(player1._Deck);
        _player2 = new PlayerData(player2._Deck);

        std::random_device rd;
        std::mt19937 g(rd()); 
        std::shuffle(_player1->deck.begin(), _player1->deck.end(), g);
        std::shuffle(_player2->deck.begin(), _player2->deck.end(), g);
    }

    // Start Game

    // Game Logic
    int DoGame(Player& player1, Player& player2)
    {
        Init(player1, player2);
        
        nbTurn = 0;

        for (int i=0; i<4; ++i)
        {
            _player1->DrawCard();
            _player2->DrawCard();
        }
        
        while (true)
        {
            if(_player1->hp > 0)
                Turn(_player1, _player2);
            else
                return 0;
            
            if (_player2->hp > 0)
                Turn(_player2, _player1);
            else
                return 1;
            nbTurn++;
        }
    }

    // Game turn
    void Turn(PlayerData* player, PlayerData* opponent)
    {
        player->mana++;
        player->DrawCard();

        while (player->CanPlay())
        {
            player->PlayCard();
        }

        player->Attack(opponent);
    }
    
};
