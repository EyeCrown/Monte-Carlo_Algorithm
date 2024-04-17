#pragma once
#include "OPlayer.h"

static int BASE_HP;
static int BASE_MANA;

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

    // Play card
};

class Board
{
public:
    std::vector<Card>* _DeckPlayer1;
    std::vector<Card>* _DeckPlayer2;
    
    PlayerData* _player1;
    PlayerData* _player2;
    
    Board(OPlayer* player1, OPlayer* player2)
    {
        _DeckPlayer1 = player1->_Deck;
        _DeckPlayer2 = player2->_Deck;

        _player1 = new PlayerData(_DeckPlayer1);
        _player2 = new PlayerData(_DeckPlayer2);
    }
    
    // Init game

    // Start Game

    // Game Logic

    // Game turn

    
};
