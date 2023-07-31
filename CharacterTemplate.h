// defintion for the character template class that will be a base class for all other character classes
#pragma once

enum class AttackType;
class StatusEffect; // forward declaration of the status effect class
class Effect; // forward declaration of the effect class

#include "I_Print.h"
#include "Main.h"
#include "Skill.h"

using EffectPtr = std::shared_ptr<Effect>; // create a type alias for the shared pointer to the effect class

class CharacterTemplate : public I_Print, public std::enable_shared_from_this<CharacterTemplate> {
protected:
	std::string Name = "Unnammed";
	int MaxHealth = 100;
	int CurrentHealth = MaxHealth;
	int MaxMana = 100;
	int CurrentMana = MaxMana;
	int Level = 1;
	int Speed = 1;
	int AttackPwr = 1;
	int DefensePwr = 1;
	bool IsDefending = false;
	std::map<std::string, int> StatValues {
		{"Strength", 1},
		{ "Dexterity", 1 },
		{ "Wisdom", 1 },
		{ "Charisma", 1 }
	};
	std::vector<std::shared_ptr<Effect>> Afflictions;
	AttackType baseAttackType;
	std::vector<Skill> Skills;

public:
	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
	CharacterTemplate(); // default constructor
	CharacterTemplate(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level);
	CharacterTemplate(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level, int speed, int attack, int defence,
		bool isDefending ,std::map<std::string, int> statValues, AttackType baseAttackType, 
		std::vector<Skill> skills, std::vector<EffectPtr> afflictions);  // constructor with parameters
	virtual ~CharacterTemplate(); // destructor

// functions for all entity classes:

	virtual void heal(int health);
	int GetCurrentHealth() const { return CurrentHealth; };        
	int GetMaxHealth() const { return MaxHealth; };               
	void IncreaseMaxHealth(int health) { MaxHealth += health; };  
	void DecreaseMaxHealth(int health) { MaxHealth -= health; };
	virtual void TakeDamage(int damage);
	virtual void Perish() { CurrentHealth = 0; };
	virtual bool IsDead();

	virtual void RestoreMana(int mana);
	virtual void UseMana(int mana);
	int GetCurrentMana() const { return CurrentMana; };  
	int GetMaxMana() const { return MaxMana; };           
	void IncreaseMaxMana(int mana) { MaxMana += mana; }; 
	void DecreaseMaxMana(int mana) { MaxMana -= mana; };

	virtual void ApplyEffect(EffectPtr effect);
	virtual void RemoveEffect(const std::string& effectName);
	
	virtual std::map<std::string, int> GetCharacterStats() const;
	virtual void SetCharacterStats(std::map<std::string, int> stats);
	virtual void AddStat(const std::string statName, int value);
	virtual void RemoveStat(const std::string statName, int value);


	virtual void SetName(std::string name) { Name = name; };
	virtual std::string GetName() const { return Name; };

	virtual int GetCharacterLevel() const { return Level; };
	virtual void SetCharacterLevel(int level) { Level = level; };

	virtual int GetSpeed() const { return Speed; };
	virtual void SetSpeed(int speed) { Speed = speed; };

	virtual void PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) { };

	virtual int CalculateBaseDamage(AttackType attackType, std::shared_ptr<CharacterTemplate> target);

	virtual void Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) {};
	virtual void Defend() {};

	virtual int GetAttackPwr() const { return AttackPwr; };
	virtual void SetAttackPwr(int attack) { AttackPwr = attack; };
	virtual void IncreaseAttackPwr(int attack) { AttackPwr += attack; };
	virtual void DecreaseAttackPwr(int attack) { AttackPwr -= attack; };

	virtual int GetDefensePwr() const { return DefensePwr; };
	virtual void SetDefensePwr(int defense) { DefensePwr = defense; };
	virtual void IncreaseDefensePwr(int defense) { DefensePwr += defense; };
	virtual void DecreaseDefensePwr(int defense) { DefensePwr -= defense; };

	virtual bool CanUseSkills() const;
	virtual void UseSkill(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) { };
	virtual void AddSkill(const Skill& skill) {Skills.push_back(skill);}

	std::vector<std::shared_ptr<Effect>>& GetAfflictions() { return Afflictions; };
};

