#include "GameManager.h"

std::shared_ptr<Item> GameManager::GetItem(int id)
{
	if (items.count(id) > 0)
	{
		return items[id];
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<Enemy> GameManager::GetEnemy(const std::string& name)
{
	if (enemies.count(name) > 0)
	{
		return enemies[name];
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<NPC> GameManager::GetNPC(const std::string& name)
{
	if (npcs.count(name) > 0)
	{
		return npcs[name];
	}
	else
	{
		return nullptr;
	}
}