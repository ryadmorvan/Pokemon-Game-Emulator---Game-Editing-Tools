#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include <vector>


inline void Collison_Detect(Map map, NPC *player)
{
	for (auto& wall : map.map)
	{
		if (wall->getCollideAble()) 
		{
			wall->GetCollider().Check(player->GetCollider());
		}
	}
}