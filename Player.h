#pragma once
#include <vector>

#include "Card.h"
#include "csvfile.h"
#include "SetList.h"

#define SIZE_DECK 30

class Player
{
public:
    int ID;
    
    std::vector<Card*>* _Deck;
    SetList* _setList;

    Card* cardRemoved;
    int indexCardRemoved;

    Player(SetList* set_list, int id)
    {
        ID = id;
        _Deck = new std::vector<Card*>;
        _setList = set_list;
        GenerateDeck();

        cardRemoved = _Deck->at(0);
        indexCardRemoved = 0;
    }

    void GenerateDeck()
    {
        for (int i=0; i<SIZE_DECK; i++)
        {
            //int randID;// = rand() % _setList->size;
            
            Card* card;// = &(_setList->AllCards[randID]);

            do
            {
                //randID = rand() % _setList->size;
                card = &(_setList->AllCards[rand() % _setList->AllCards.size()]);
            } while (contain_card(card));
            
            _Deck->push_back(card);
        }
    }

    bool contain_card(Card* card) const
    {
        for(int i=0; i<_Deck->size(); i++)
        {
            if (card == _Deck->at(i))
                return true;
        }
        return false;
    }

    int numberCardinDeck(Card* card)
    {
        int nb = 0;
        for(int i=0; i<_Deck->size(); i++)
        {
            if (card == _Deck->at(i))
                nb++;
        }
        return nb;
    }
    
    //Change One Card
    void ChangeOneCard()
    {
        indexCardRemoved = rand() % _Deck->size();
        cardRemoved = _Deck->at(indexCardRemoved);
        Card* newCard;
        do
        {
            newCard = &(_setList->AllCards[rand() % _setList->AllCards.size()]);
        } while (numberCardinDeck(newCard) >= 2);

        //std::cout << "\n\nPlayer change " + cardRemoved->ToString() + " at " + std::to_string(indexCardRemoved) + " by "+ newCard->ToString() +".\n";
        _Deck->at(indexCardRemoved) = newCard;
    }

    void UndoChangeOneCard()
    {
        //std::cout << "Player put " + cardRemoved->ToString() + " at " + std::to_string(indexCardRemoved) + " again.\n\n";
        _Deck->at(indexCardRemoved) = cardRemoved;
    }

    // CVS
    void WriteAmountOfCardsPerCostHistogram(std::string filename) {
        csvfile csv(filename);
        csv << "Cost" << "Amount of cards" << endrow;
        std::vector<int> costForEachCard = std::vector<int>();
        for (int i = 0; i < _Deck->size(); i++) {
            costForEachCard.push_back(_Deck->at(i)->_cost);
        }
        int max_value = *max_element(costForEachCard.begin(), costForEachCard.end());
        std::vector<int> amountOfCards = std::vector<int>();
        for (int i = max_value; i >= 0; --i)
        {
            amountOfCards.push_back(std::count(costForEachCard.begin(), costForEachCard.end(), i));
        }
        std::reverse(amountOfCards.begin(), amountOfCards.end());
        for (int i = max_value; i >= 0; --i)
        {
            csv << i << amountOfCards[i] << endrow;
        }
    }

    void WriteDeck(std::string filename)
    {
        csvfile csv(filename);
        csv << "ID°" << "Cost" << "Attack" << "Defense" << "Taunt" << "Trample" << "Distortion" << "First Strike" << endrow;
        //std::sort(AllCards.begin(), AllCards.end(), [](Card a, Card b) { return a._cost < b._cost; });
        for (int i = 0; i < _Deck->size(); i++)
        {
            csv << _Deck->at(i)->ID << _Deck->at(i)->_cost << _Deck->at(i)->_atk << _Deck->at(i)->_def << _Deck->at(i)->_hasTaunt << _Deck->at(i)->_hasTrample << _Deck->at(i)->_hasDistortion << _Deck->at(i)->_hasFirstStrike  << endrow;
        }


    }
};
