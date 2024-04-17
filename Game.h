#pragma once
#include "Player.h"

class Game
{
public:
    Player* p1;
    Player* p2;

    bool p1Turn;

    int baseHp = 20;
    int baseMana = 0;
    
    int _nbGames;
    bool endGame;

    Game(Player* fst, Player* snd)
    {
        p1 = fst;
        p2 = snd;
    }
    
    void InitGame(bool p1Begin)
    {
        
        p1->Initilaze(baseHp, baseMana);
        p2->Initilaze(baseHp, baseMana);
        
        p1Turn = p1Begin;

        endGame = false;
    }


    Player* MakeGame(bool p1Begin)
    {
        InitGame(p1Begin);
        //std::cout << "A game begin." << std::endl;

        while (!endGame)
        {
            //std::cout << "Game status:  P1 HP:"+ std::to_string(p1->_hp) + "    P2 HP: " + std::to_string(p2->_hp) << std::endl;
            DoGame();
        }
        //std::cout << "A game ended." << std::endl;

        return GetWinner();
    }


    void DoGame()
    {
        if (p1Turn)
        {
            Turn(p1, p2);
        }
        else
        {
            Turn(p2, p1);
        }
    }

    void Turn(Player* active, Player* passive)
    {
        if (active->IsAlive())
        {
            active->_mana++;
            
            active->DrawCard();
    
            while (active->CanPlay())
            {
                active->PlayCard();
            }

            int damage = active->GetAllDamage();
            //std::cout << "Player "+ std::to_string(active->_id) + " deals " + std::to_string(damage) + " to Player " + std::to_string(passive->_id) << std::endl;
            passive->_hp -= active->GetAllDamage();

            p1Turn = !p1Turn;
        }
        else
        {
            // active player is dead, passive win
            endGame = true;
        }
    }
    
    
    
    Player* GetWinner()
    {
        if (p1->_hp > 0)
            return p1;

        if (p2->_hp > 0)
            return p2;
    }
    
};
