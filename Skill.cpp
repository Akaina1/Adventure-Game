#include "Skill.h"
#include "CharacterTemplate.h"
#include "Effect.h"

int Skill::CalculateSkillDamage(std::shared_ptr<CharacterTemplate> caster, std::shared_ptr<CharacterTemplate> target)
{
	int calculatedDamage = 0;

    // Custom logic for calculating skill damage based on skill properties, caster stats, target stats, etc.
    // Here, you can access caster and target stats (e.g., Strength, Wisdom) from their respective CharacterTemplate objects
    // to calculate the skill damage based on the Skill's unique properties.

    if (Name == "Fireball")
    {
        // Example: Calculate Fireball damage based on caster's Wisdom stat and additional factors
        int wisdomStat = caster->GetCharacterStats()["Wisdom"];
        int attackPower = caster->GetAttackPwr();
        // Additional calculations based on Fireball properties...
        calculatedDamage = wisdomStat * 2 + attackPower * 1; // Adjust the coefficients as needed
    }
    else if (Name == "Cleave")
    {
        // Example: Calculate Cleave damage based on caster's Strength stat and additional factors
        int strengthStat = caster->GetCharacterStats()["Strength"];
        // Additional calculations based on Cleave properties...
        calculatedDamage = strengthStat * 2; // Replace this with your actual calculation
    }
    else
    {
        // Handle damage calculation for other skills here...
    }

    // If the calculated damage is less than 0, set it to 0
    if (calculatedDamage < 0) {
        calculatedDamage = 0;
    }

    return calculatedDamage;
}

void Skill::ApplyEffect(CharacterTemplate& character) 
{
    this->AddEffect(character);
}
void Skill::RemoveEffect(CharacterTemplate& character) 
{
    this->UndoEffect(character);
}