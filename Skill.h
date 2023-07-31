#pragma once
#include "Effect.h"
#include "Main.h"
#include "AttackType.h"


class CharacterTemplate;


// Enum to represent the target type of the skill
enum class TargetType
{
    Enemy,
    Ally
};

enum class SkillType
{
	Attack,
    Healing,
	Buff,
	Debuff
};

class Skill : public Effect
{
private:
    std::string Name;
    std::string Description;
    AttackType attackType;
    int Damage;
    int ManaCost;
    TargetType targetType;
    int Duration;
    SkillType skillType;
    std::function<void(CharacterTemplate& character)> AddEffect; // function to add the status effect to the player character
    std::function<void(CharacterTemplate& character)> UndoEffect; // function to remove the status effect from the player character

public:
    Skill(const std::string& name, std::string& description, AttackType attackType, int damage, int manacost, TargetType targettype, int duration, SkillType skillType)
        : Name(name),Description(description), attackType(attackType), Damage(damage), ManaCost(manacost), targetType(targettype), Duration(duration), skillType(skillType) {}

    // Getters for skill properties
    std::string GetName() const override { return Name; }
    std::string SetName(std::string name) { Name = name; }
    std::string GetDescription() const { return Description; }
    std::string SetDescription(std::string description) { Description = description; }
    AttackType GetAttackType() const { return attackType; }
    int GetDamage() const { return Damage; }
    int GetManaCost() const { return ManaCost; }
    TargetType GetTargetType() const { return targetType; }
    SkillType GetSkillType() const { return skillType; }

    int CalculateSkillDamage(std::shared_ptr<CharacterTemplate> caster, std::shared_ptr<CharacterTemplate> target);
    
    std::function<void(CharacterTemplate& character)> GetAddEffect() const { return AddEffect; }; // returns the add effect of the status effect
    std::function<void(CharacterTemplate& character)> GetRemoveEffect() const { return UndoEffect; }; // returns the remove effect of the status effect

    virtual void RemoveEffect(CharacterTemplate& character) override;
    virtual void ApplyEffect(CharacterTemplate& character) override;
};

// call skill like this:
// skills.push_back(Skill("Fireball", AttackType::Magic, 10));
//skill name
//skill type
//skill base damage