#pragma once

#include "CharacterTemplate.h"
#include "Effect.h"

//class CharacterTemplate;

class NPC : public CharacterTemplate
{
public:
	void Print(std::ostream& os) const override; // override the print function from the I_Print class
	NPC(); // default constructor
	NPC(std::string name, int maxhealth, int currenthealth, int maxmana,
		int currentmana, int level, int speed, int attack, int defense,
		bool isDefending, std::map<std::string, int> statValues, AttackType baseAttackType,
		std::vector<Skill> skills, std::vector<EffectPtr> afflictions);  // constructor with parameters
	NPC(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level);
	~NPC(); // destructor

	virtual void PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) override;
	virtual void Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) override;
	virtual void Defend() override;
};