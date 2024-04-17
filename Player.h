#pragma once
#include <algorithm>
#include <complex.h>
#include <random>
#include <vector>

#include "Card.h"
#include "SetList.h"

#define SIZE_DECK 30

class Player
{
private:
    int sizeDeck = 30;
    
public:
    int _id;
    
    int _hp;
    int _mana;

    std::vector<Card*>* _deckComplete;
    
    std::vector<Card>* _deck;
    std::vector<Card>* _hand;
    std::vector<Card>* _board;

    Player(int id, SetList set_list)
    {
        _id = id;
        _hp = 0;
        _mana = 0;

        _deckComplete = new std::vector<Card*>;
        _deck = new std::vector<Card>;
        _hand = new std::vector<Card>;
        _board = new std::vector<Card>;

        GenerateDeck(set_list);
        
    }
    
    void Initilaze(int hp, int mana)
    {
        _hp = hp;
        _mana = mana;
        for (int i=0; i<_deckComplete->size(); i++)  
            _deck->push_back(*_deckComplete->at(i));
        
        _hand->clear();
        _board->clear();

        std::random_device rd;
        std::mt19937 g(rd()); 
        std::shuffle(_deck->begin(), _deck->end(), g);

        for (int i=0; i<4; i++)
            DrawCard();
        
    }
    
    void GenerateDeck(SetList setlist)
    {
        for (int i=0; i<sizeDeck; i++)
        {
            int randID = rand() % setlist.size;
            
            Card* card = setlist.AllCards[randID];

            while (ContainCard(*card))
            {
                randID = rand() % setlist.size;
                card = setlist.AllCards[randID];
            }
            
            _deckComplete->push_back(card);
        }
    }

    bool ContainCard(Card card)
    {
        for(int i=0; i<_deck->size(); i++)
        {
            if (card.ID == _deck->at(i).ID)
                return true;
        }
        return false;
    }

    std::string ToString()
    {
        std::string text = "==== Player's deck =============\n";
        for (std::vector<Card>::const_iterator card = _deck->begin(); card != _deck->end(); ++card)
        {
            text += card->ToString() + "\n";
        }
        text += "   Deck size: " + std::to_string(_deck->size()) + "\n";
        text += "=======================\n";

        return text;
    }
    
    void DrawCard()
    {
        _hand->push_back(_deck->front());
        _deck->pop_back();
    }

    bool CanPlay()
    {
        for (std::vector<Card>::const_iterator card = _hand->begin(); card != _hand->end(); ++card)
        {
            if(_mana - card->_cost >= 0)
                return true;
        }
        return false;
    }

    void PlayCard()
    {
        int index = 0;
        std::vector<Card> cardsAvailable;
        std::vector<int> indexCards;

        int maxCost = 0;
        for (std::vector<Card>::const_iterator card = _hand->begin(); card != _hand->end(); ++card)
        {
            if (card->_cost > maxCost)
                maxCost = card->_cost;
        }
        for (std::vector<Card>::const_iterator card = _hand->begin(); card != _hand->end(); ++card)
        {
            if (card->_cost == maxCost)
                cardsAvailable.push_back(*card);
                indexCards.push_back(card - _hand->begin());
        }

        index = rand() % cardsAvailable.size();
        Card card = cardsAvailable.at(index);

        //std::cout << "Player " + std::to_string(_id) + " plays card "+ std::to_string(card.ID)+"\n";
        
        _mana -= card._cost;
        
        _hand->erase( _hand->begin() + indexCards.at(index));
        _board->push_back(card);
    }

    Card SelectCardToPlay()
    {
        int index = 0;
        std::vector<Card> cardsAvailable;

        int maxCost = 0;
        for (std::vector<Card>::const_iterator card = _hand->begin(); card != _hand->end(); ++card)
        {
            if (card->_cost > maxCost)
                maxCost = card->_cost;
        }
        for (std::vector<Card>::const_iterator card = _hand->begin(); card != _hand->end(); ++card)
        {
            if (card->_cost == maxCost)
                cardsAvailable.push_back(*card);
        }

        index = rand() % cardsAvailable.size();
        Card card = cardsAvailable.at(index);
        
        
        _mana -= card._cost;
        
        _hand->erase( _hand->begin() + index);
        return card;
    }

    int GetAllDamage()
    {
        int damage = 0;
        for (std::vector<Card>::const_iterator card = _board->begin(); card != _board->end(); ++card)
        {
            damage += card->_atk;
        }
        
        return damage;
    }

    bool IsAlive()
    {
        return _hp > 0 && _deck->size() > 0;
    }
};
