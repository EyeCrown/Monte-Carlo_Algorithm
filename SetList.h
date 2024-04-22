#pragma once
#include <iostream>
#include <list>
#include <vector>

#include "Card.h"

class SetList
{
public:
    std::vector<Card> AllCards;
    int size;

    SetList()
    {
        size = 0;
        GenerateSetList(1, 8);
        WriteSetList();
    }
    
    void GenerateSetList(int minCost, int maxCost)
    {
        int id = 0;
        
        for (int atk=minCost-1; atk < maxCost*2; atk++)
        {
            for (int def=minCost; def <= maxCost*2; def++)
            {
                
                if( ceilf((atk+def)/2) <= maxCost )    // No options
                    GenerateCard(atk, def, 0, 0, 0, 0, id);

                // if( (atk+def)/2 + 1.5f <= maxCost ) // Just taunt
                //     GenerateCard(atk, def, 1, 0, 0, 0, id);

                /*if( (atk+def)/2 + 1 <= maxCost ) // One carac
                {
                    GenerateCard(atk, def, 0, 1, 0, 0, id);
                    GenerateCard(atk, def, 0, 0, 1, 0, id);
                    GenerateCard(atk, def, 0, 0, 0, 1, id);
                }

                if( (atk+def)/2 + 1 + 1.5f <= maxCost ) // One carac + taunt
                {
                    GenerateCard(atk, def, 1, 1, 0, 0, id);
                    GenerateCard(atk, def, 1, 0, 1, 0, id);
                    GenerateCard(atk, def, 1, 0, 0, 1, id);
                }

                if( (atk+def)/2 + 2 <= maxCost ) // Two carac
                {
                    GenerateCard(atk, def, 0, 1, 1, 0, id);
                    GenerateCard(atk, def, 0, 1, 0, 1, id);
                    GenerateCard(atk, def, 0, 0, 1, 1, id);
                }

                if( (atk+def)/2 + 2 + 1.5f <= maxCost ) // Two carac + taunt
                {
                    GenerateCard(atk, def, 1, 1, 1, 0, id);
                    GenerateCard(atk, def, 1, 1, 0, 1, id);
                    GenerateCard(atk, def, 1, 0, 1, 1, id);
                }

                if( (atk+def)/2 + 3 <= maxCost ) // Two carac
                {
                    GenerateCard(atk, def, 0, 1, 1, 1, id);
                }

                if( (atk+def)/2 + 3 + 1.5f <= maxCost ) // Two carac + taunt
                {
                    GenerateCard(atk, def, 1, 1, 1, 1, id);
                }*/
            }
        }
        size = id;
    }

    void GenerateCard(int atk, int def, bool taunt, bool trample, bool distortion, bool firstStrike, int& id)
    {
        Card card(atk, def, 1, 0, 0, 0, id++);
        AllCards.push_back(card);
    }
    
    std::string ToString()
    {
        std::string text = "==== SetList =============\n";
        for (auto card : AllCards)
        {
            text += card.ToString() + "\n";
        }
        text += "   SetList size: " + std::to_string(size) + "\n";
        text += "=======================\n";

        return text;
    }

    void WriteSetList()
    {
        csvfile csv("SetListData.csv");
        csv << "Cost" << "Attack" << "Defense" << "Taunt" << "Trample" << "Distortion" << "First Strike" << endrow;
        std::sort(AllCards.begin(), AllCards.end(), [](Card a, Card b) { return a._cost < b._cost; });
        for (int i = 0; i < AllCards.size(); i++)
        {
            csv << AllCards[i]._cost << AllCards[i]._atk << AllCards[i]._def << AllCards[i]._hasTaunt << AllCards[i]._hasTrample << AllCards[i]._hasDistortion << AllCards[i]._hasFirstStrike  << endrow;
        }
    }
};
