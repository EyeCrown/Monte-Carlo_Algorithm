#pragma once
#include <iostream>
#include <list>
#include <vector>

#include "Card.h"

class SetList
{
public:
    std::vector<Card*> AllCards;
    int size;

    SetList()
    {
        size = 0;
        GenerateSetList();
    }
    
    void GenerateSetList()
    {
        int maxAtk = 12;
        int maxDef = 12;
        int id = 0;
        
        for (int atk=0; atk<maxAtk; atk++)
        {
            for (int def=1; def <= maxDef; def++)
            {
                Card* card = new Card(atk, def);
                card->ID = id++;
                AllCards.push_back(card);
                //AllCards[id] = card;
            }
            --maxDef;
        }
        size = id;
        
    }

    std::string ToString()
    {
        std::string text = "==== SetList =============\n";
        for (auto card : AllCards)
        {
            text += card->ToString() + "\n";
        }
        text += "   SetList size: " + std::to_string(size) + "\n";
        text += "=======================\n";

        return text;
    }
    
};
