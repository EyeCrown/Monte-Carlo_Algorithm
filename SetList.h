#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#include "Card.h"

static const int MIN_CARD_COST = 1;
static const int MAX_CARD_COST = 8;

class SetList
{
public:
    std::vector<Card> AllCards;

    SetList()
    {
        CreateAllCards();
        SortCards();
        WriteSetList();
        //std::cout << ToString() << std::endl;
    }
    
    void GenerateSetList()
    {
        int id = 0;

        for (int atk=0; atk < MAX_CARD_COST*2; atk++)
        {
            for (int def=1; def <= MAX_CARD_COST*2; def++)
            {
                if( ceilf((float)(atk + def) / (float)2) <= MAX_CARD_COST )    // No options
                    GenerateCard(atk, def, 0, 0, 0, 0, id);
            }
        }
    }

    void CreateAllCards()
    {
        int id = 0;

        for(int special = 0 ; special < 2; special++)
        {
            for (int attack = 0; attack <= MAX_CARD_COST*2-1; attack++)
            {
                for (int defence = 1; defence <= MAX_CARD_COST*2; defence++)
                {
                    bool hasTaunt = (special & 1) != 0;
                    bool hasDistortion = 0;//(special & 2) != 0;
                    bool hasTrample = 0;//(special & 4) != 0;
                    bool hasFirstStrike = 0;//(special & 8) != 0;

                    if (GetCost(attack,defence, hasTaunt, hasTrample, hasDistortion, hasFirstStrike) <= MAX_CARD_COST)
                    {
                        Card card(attack, defence, hasTaunt, hasTrample, hasDistortion, hasFirstStrike, id);
                        AllCards.push_back(card);
                        id++;
                    }
                }
            }
        }

        //Console.WriteLine("Set list: nb cards:" + cards.Count);
    }

    void SortCards()
    {
        std::sort(this->AllCards.begin(), this->AllCards.end());
    }

    void GenerateCard(int atk, int def, bool taunt, bool trample, bool distortion, bool firstStrike, int& id)
    {
        Card card(atk, def, taunt, trample, distortion, firstStrike, id++);
        AllCards.push_back(card);
    }
    
    std::string ToString()
    {
        std::string text = "==== SetList =======================================\n";
        for (auto card : AllCards)
        {
            text += card.ToString() + "\n";
        }
        text += "   SetList size: " + std::to_string(AllCards.size()) + "\n";
        text += "=================================================\n";

        return text;
    }

    void WriteSetList()
    {
        csvfile csv("SetListData.csv");
        csv << "ID°" << "Cost" << "Attack" << "Defense" << "Taunt" << "Trample" << "Distortion" << "First Strike" << endrow;
        //std::sort(AllCards.begin(), AllCards.end(), [](Card a, Card b) { return a._cost < b._cost; });
        for (int i = 0; i < AllCards.size(); i++)
        {
            csv << AllCards[i].ID << AllCards[i]._cost << AllCards[i]._atk << AllCards[i]._def << AllCards[i]._hasTaunt << AllCards[i]._hasTrample << AllCards[i]._hasDistortion << AllCards[i]._hasFirstStrike  << endrow;
        }
    }
};
