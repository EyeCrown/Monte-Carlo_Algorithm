#pragma once
#include <vector>

#include "Card.h"
#include "SetList.h"

#define SIZE_DECK 30

class OPlayer
{
public:
    std::vector<Card>* _Deck;

    OPlayer(SetList set_list)
    {
        _Deck = new std::vector<Card>;
        GenerateDeck(set_list);
    }

    void GenerateDeck(SetList setlist)
    {
        for (int i=0; i<SIZE_DECK; i++)
        {
            int randID = rand() % setlist.size;
            
            Card card = setlist.AllCards[randID];

            while (ContainCard(card))
            {
                randID = rand() % setlist.size;
                card = setlist.AllCards[randID];
            }
            
            _Deck->push_back(card);
        }
    }

    bool ContainCard(Card card)
    {
        for(int i=0; i<_Deck->size(); i++)
        {
        if (card.ID == _Deck->at(i).ID)
                return true;
        }
        return false;
    }

    //Change One Card
    
};
