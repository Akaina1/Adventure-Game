#pragma once
#include "Main.h"
class CharacterTemplate; // Forward declaration of CharacterTemplate class

class Effect
{
protected:
    std::string Name; // name of the effect
    int duration; // duration of the effect
public:
    

    virtual std::string GetName() const { return ""; };
    virtual int GetDuration() const { return duration; };
    virtual void IncreaseDuration(int increase) {};
    virtual void DecreaseDuration(int decrease) {};

    virtual void ApplyEffect(CharacterTemplate& character) = 0;
    virtual void RemoveEffect(CharacterTemplate& character) = 0;
};