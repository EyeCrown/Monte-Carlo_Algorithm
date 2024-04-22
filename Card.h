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

    bool _hasTaunt;
    bool _hasTrample;
    bool _hasDistortion;
    bool _hasFirstStrike;
    
    Card()
    {
        ID = -999;
        _atk = -999;
        _def = -999;
        _cost = -999;
        _hasTaunt = false;
        _hasTrample = false;
        _hasDistortion = false;
        _hasFirstStrike = false;
    }
    
    Card(int atk, int def, bool taunt, bool trample, bool distortion, bool firstStrike, int id)
    {
        ID      = id;
        _atk    = atk;
        _def    = def;
        
        _hasTaunt = taunt;
        _hasTrample = trample;
        _hasDistortion = distortion;
        _hasFirstStrike = firstStrike;

        _cost = ceilf((float)(atk + def) / (float)2 + _hasTaunt * 1.5f + _hasTrample + _hasDistortion + _hasFirstStrike);
        /*if (_cost == 0)
            _cost = 1;*/
    }

    std::string ToString() const
    {
        return  "\n | ID°"            + std::to_string(ID) +
                " | C:"             + std::to_string(_cost) +
                " | ATK: "          + std::to_string(_atk) +
                " | DEF: "          + std::to_string(_def) +
                " | TAUNT: "        + std::to_string(_hasTaunt) +
                " | TRAMPLE: "      + std::to_string(_hasTrample) +
                " | DISTORTION: "   + std::to_string(_hasDistortion) +
                " | FST STRIKE: "   + std::to_string(_hasFirstStrike) + "\n";
        
    }

    friend bool operator==(const Card& lhs, const Card& rhs)
    {
        return lhs.ID == rhs.ID;
    }

    friend bool operator!=(const Card& lhs, const Card& rhs)
    {
        return !(lhs == rhs);
    }
    friend bool operator<(const Card& lhs, const Card& rhs)
    {
        return lhs.ID < rhs.ID;
    }
    friend bool operator<=(const Card& lhs, const Card& rhs)
    {
        return !(rhs < lhs);
    }
    friend bool operator>(const Card& lhs, const Card& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator>=(const Card& lhs, const Card& rhs)
    {
        return !(lhs < rhs);
    }
};

static Card CardWithHigherCost(const Card& lhs, const Card& rhs)
{
    return lhs._cost >= rhs._cost ? lhs : rhs;
}

static int GetCost(int atk, int def, bool hasTaunt, bool hasTrample, bool hasDistortion, bool hasFirstStrike)
{
    return ceilf((float)(atk + def) / (float)2 + hasTaunt * 1.5f + hasTrample + hasDistortion + hasFirstStrike);
}
