#pragma once
#include "NPC.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "Pokemon.h"
#include <vector>

class Player : public NPC
{
private:
	int		m_Health{ 20 };
	int		m_Mana{ 10 };
public:
	std::vector<std::shared_ptr<Pokemon>> pokemons;
public:
	Player(float x, float y, std::string fileName);
	virtual void setName(std::string name) override;
	void Push_Pokemon(std::shared_ptr<Pokemon> &Pokemon) { pokemons.emplace_back(Pokemon); }
	virtual ~Player();
};