// defintion for the character template class that will be a base class for all other character classes
#pragma once
#include "I_Print.h"
#include "StatusEffect.h"
#include "Item.h"
#include "Main.h"

class CharacterTemplate : public I_Print {
private:
	std::string Name = "Unnammed";
	int MaxHealth = 100;
	int CurrentHealth = MaxHealth;
	int MaxMana = 100;
	int CurrentMana = MaxMana;
	int Level = 1;
	std::map<std::string, int> StatValues {
		{"Strength", 0},
		{ "Dexterity", 0 },
		{ "Wisdom", 0 },
		{ "Charisma", 0 }
	};
	std::vector<StatusEffect> Afflictions;
public:
	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
	CharacterTemplate(); // default constructor
	CharacterTemplate(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level,
		std::map<std::string, int> statValues,
		std::vector<StatusEffect> afflictions);  // constructor with parameters
	virtual ~CharacterTemplate(); // destructor

// functions for all entity classes:
	virtual void heal(int health);
	int GetCurrentHealth() const { return CurrentHealth; };        
	int GetMaxHealth() const { return MaxHealth; };               
	void IncreaseMaxHealth(int health) { MaxHealth += health; };  
	void DecreaseMaxHealth(int health) { MaxHealth -= health; };
	virtual void TakeDamage(int damage);
	virtual bool IsDead();

	virtual void RestoreMana(int mana);
	virtual void UseMana(int mana);
	int GetCurrentMana() const { return CurrentMana; };  
	int GetMaxMana() const { return MaxMana; };           
	void IncreaseMaxMana(int mana) { MaxMana += mana; }; 
	void DecreaseMaxMana(int mana) { MaxMana -= mana; };

	virtual void ApplyEffect(StatusEffect effect);
	virtual void RemoveEffect(const std::string& effectName);
	virtual void UpdateEffects(StatusEffect& effect);

	virtual std::map<std::string, int> GetCharacterStats() const;
	virtual void SetCharacterStats(std::map<std::string, int> stats);
	virtual void AddStat(const std::string statName, int value);
	virtual void RemoveStat(const std::string statName, int value);


	virtual void SetName(std::string name) { Name = name; };
	virtual std::string GetName() const { return Name; };

};

