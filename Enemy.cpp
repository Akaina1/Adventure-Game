#include "Enemy.h"
#include "AttackType.h"
#include "Enemy.h"
#include "Combat.h"

enum {
	MANA_THRESHOLD = 20, // 20%
	LOW_HEALTH_THRESHOLD = 20, // 20%
	HEAL_THRESHOLD = 30, // 30%
};

void Enemy::Print(std::ostream& os) const     // override the print function from the I_Print class
{
	std::cout << std::boolalpha;
	os << "Enemy: " << std::endl;
	//os << "Location: "<< CurrentLocation << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Name: " <<  Name << std::endl;
	os << "Level: " << Level << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Health: " << CurrentHealth << "/" << MaxHealth << std::endl;
	os << "Mana: " << CurrentMana << "/" << MaxMana << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Stats: " << std::endl;
	for (auto stat : StatValues)
	{
		os << stat.first << ": " << stat.second << std::endl;
	}
	os << "-------------------------------------------" << std::endl;
	os << "Status Effects: " << std::endl;
	for (auto& effect : Afflictions)
	{
		os << effect->GetName() << ": " << effect->GetDuration() << " turns left" << std::endl;
	}
}

Enemy::Enemy() // default constructor
{
}

Enemy::Enemy(std::string name, int maxhealth, int currenthealth, int maxmana,
	int currentmana, int level, int speed, int attackPwr, int defensePwr,
	bool isDefending,std::map<std::string, int> statValues, AttackType baseAttackType,
	std::vector<Skill> skills, std::vector<EffectPtr> afflictions)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, speed, attackPwr, defensePwr,
      isDefending, statValues, baseAttackType, skills, afflictions)
{
}

Enemy::~Enemy() // destructor
{
}

Enemy::Enemy(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level, AttackType baseAttackType)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, baseAttackType)
{
}

void Enemy::PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	// Note: Enemy class are considered "Allies", NPC and PlayerCharacter class are considered "Enemies"
	// Enemy AI will perform actions based on the following specifications:
	// 1. The AI will always prioritize UseSkill() over Attack() if the AI has (CurrentMana > (MaxMana * 0.2))
	// 2. The AI will always prioritize healing allies over attacking enemies if an ally is below 30% health
		// 2.b. The AI will always prioritize healing the ally with the lowest health if multiple allies are below 30% health
	// 3. The AI will always prioritize attacking enemies over healing allies if all allies are above 50% health
		//3.a. The AI will always prioritize attacking the enemy with the lowest health
		//3.b. The AI will always prioritize a (class)PlayerCharacter type enemy over an (class)NPC type enemy
		//3.c. The AI will use Attack() if the AI has (CurrentMana < (MaxMana * 0.2))
	// 4. The AI will defend if the AI has (CurrentHealth < (MaxHealth * 0.2))
	// 
	//check mana levels first
	if (CurrentMana > (MaxMana * MANA_THRESHOLD / 100))
	{
		UseSkill(Combatants);
	}

	// if AI health is below 20%, defend
	if (!skillUsed && CurrentHealth < (MaxHealth * LOW_HEALTH_THRESHOLD / 100))
	{
		Defend();
		return;
	}

	// if mana is less than 20%, attack
	if (!skillUsed || CurrentMana < (MANA_THRESHOLD / 100))
	{
		Attack(Combatants);
		return;
	}

	else
	{
		std::cout << GetName() << " is unable to perform an action!" << std::endl;
	}
}
void Enemy::Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	// Find the target enemy
	std::shared_ptr<CharacterTemplate> player = combatInstance->GetPlayer(Combatants);
	std::shared_ptr<CharacterTemplate> lowestHealthEnemy = combatInstance->GetLowestHealthAlly(Combatants);
	std::shared_ptr<CharacterTemplate> targetEnemy = player ? player : lowestHealthEnemy;

	// Ensure the target enemy is valid and not dead.
	if (targetEnemy && targetEnemy->GetCurrentHealth() > 0)
	{
		// Use the NPC's base attack type
		AttackType attackType = BaseAttackType;

		// Calculate the base damage
		int damage = CalculateBaseDamage(attackType, targetEnemy);

		// Apply the damage to the enemy
		targetEnemy->TakeDamage(damage);

		std::cout << GetName() << " attacks " << targetEnemy->GetName() << " for " << damage << " damage!" << std::endl;
	}
	else
	{
		std::cout << "Attack failed! Target enemy is invalid or already defeated." << std::endl;
	}
}
void Enemy::UseSkill(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	skillUsed = false;
	std::shared_ptr<CharacterTemplate> lowestHealthAlly = combatInstance->GetLowestHealthEnemy(Combatants);

	// if ally has health below 30% try to heal
	if (lowestHealthAlly && lowestHealthAlly->GetCurrentHealth() < (lowestHealthAlly->GetMaxHealth() * 0.3))
	{
		for (auto& skill : Skills)
		{
			if (skill.GetSkillType() == SkillType::Healing && CurrentMana >= skill.GetManaCost())
			{
				int healingAmount = skill.CalculateSkillDamage(shared_from_this(), lowestHealthAlly);
				lowestHealthAlly->heal(healingAmount);

				UseMana(skill.GetManaCost());

				std::cout << this->GetName() << " used " << skill.GetName() << " on " << lowestHealthAlly->GetName() << " for " << healingAmount << " health!" << std::endl;
				skillUsed = true;
				return;
			}
		}
	}

	// if no ally has health below 50% or no healing skills available, try attack skills
	std::shared_ptr<CharacterTemplate> player = combatInstance->GetPlayer(Combatants);
	std::shared_ptr<CharacterTemplate> lowestHealthEnemy = combatInstance->GetLowestHealthAlly(Combatants);

	std::shared_ptr<CharacterTemplate> targetEnemy = player ? player : lowestHealthEnemy;

	if (targetEnemy)
	{
		for (auto& skill : Skills)
		{
			if (skill.GetSkillType() == SkillType::Attack && CurrentMana >= skill.GetManaCost())
			{
				int damage = skill.CalculateSkillDamage(shared_from_this(), targetEnemy);
				targetEnemy->TakeDamage(damage);

				UseMana(skill.GetManaCost());

				std::cout << this->GetName() << " used " << skill.GetName() << " on " << targetEnemy->GetName() << " for " << damage << " health!" << std::endl;
				skillUsed = true;
				return;
			}
		}
	}

	// if no attack skills, or not enough mana, try to buff self
	for (auto& skill : Skills)
	{
		if (skill.GetSkillType() == SkillType::Buff && CurrentMana >= skill.GetManaCost())
		{
			skill.GetAddEffect()(*shared_from_this());

			UseMana(skill.GetManaCost());

			std::cout << this->GetName() << " used " << skill.GetName() << " and got a buff!" << std::endl;
			skillUsed = true;
			return;
		}
	}

	// if no buff skills, or not enough mana, return to PerformAction()
	std::cout << this->GetName() << " Has no Usable Skills!" << std::endl;
	return;
}