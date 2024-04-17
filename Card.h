#pragma once
#include <string>

class Card
{
public:
    int ID;
    
    int _cost;
    int _atk;
    int _def;
    
    Card(int atk, int def)
    {
        ID = 0;
        _atk = atk;
        _def = def;
        _cost = (atk + def) / 2;
    }

    std::string ToString() const
    {
        return "|   ID°"+ std::to_string(ID)+"       C:" + std::to_string(_cost) + "   ATK: " + std::to_string(_atk) + "   DEF: "+ std::to_string(_def) + " |";
    }
};
