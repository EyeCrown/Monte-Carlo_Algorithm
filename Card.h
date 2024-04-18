#pragma once
#include <corecrt_startup.h>
#include <iostream>
#include <string>

class Card
{
public:
    int ID;
    
    int _atk;
    int _def;

    int _cost;

    
    Card()
    {
        ID = -999;
        _atk = -999;
        _def = -999;
        _cost = -999;
    }
    
    Card(int atk, int def)
    {
        ID      = 0;
        _atk    = atk;
        _def    = def;
        _cost   = ceilf((atk + def) / 2);
        if (_cost == 0)
            _cost = 1;
    }

    std::string ToString() const
    {
        return "|   ID°"+ std::to_string(ID)+"       C:" + std::to_string(_cost) + "   ATK: " + std::to_string(_atk) + "   DEF: "+ std::to_string(_def) + " |";
    }

    friend bool operator==(const Card& lhs, const Card& rhs)
    {
        return lhs.ID == rhs.ID;
    }

    friend bool operator!=(const Card& lhs, const Card& rhs)
    {
        return !(lhs == rhs);
    }
};

static Card CardWithHigherCost(const Card& lhs, const Card& rhs)
{
    return lhs._cost >= rhs._cost ? lhs : rhs;
}
