#pragma once

#include "CharacterTemplate.h"
#include "Effect.h"


class Enemy : public CharacterTemplate
{
private:
	std::shared_ptr<Combat> combatInstance; // pointer to the combat instance
public:
	bool skillUsed = false; // bool to check if the enemy has used a skill
	void Print(std::ostream& os) const override; // override the print function from the I_Print class
	Enemy(); // default constructor
	Enemy(std::string name, int maxhealth, int currenthealth, int maxmana,
		int currentmana, int level, int speed, int attackPwr, int defensePwr,
		bool isDefending, std::map<std::string, int> statValues, AttackType baseAttackType,
		std::vector<Skill> skills, std::vector<EffectPtr> afflictions);  // constructor with parameters
	Enemy(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level, AttackType baseAttackType);
	~Enemy(); // destructor

	virtual void PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) override;
	virtual void Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) override;
	virtual void UseSkill(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants) override;
};

