#pragma once
#include <cstdint>
#include <string>
#include <SFML\Graphics.hpp>
#include <tuple>
#include "Animation.h"
#define MAX_BAR_SIZE 130.0f

namespace GUI
{
	class PkmGUI
	{
	private:		
		//Fonts
		sf::Font font;
		sf::Text Healthbar;
		sf::Text Level;
		sf::Text Name;
	private:
		//////////////////////////////
		sf::RectangleShape black_bar;
		sf::RectangleShape m_HealthBar;
		sf::RectangleShape black_bar2;
		sf::RectangleShape m_ExpBar;
		std::string m_name;
		//Name, level, health, max_health, exp, max_exp respectively
		std::tuple<std::string, unsigned, int32_t, int32_t, unsigned, unsigned> _stats;
	public:
		PkmGUI();
		void getStats(const std::tuple<std::string, unsigned, int32_t, int32_t, unsigned, unsigned>&& stats);
		void statsUpdate();
		void draw_back(sf::RenderWindow &window);
		void draw_front(sf::RenderWindow& window);
		const sf::RectangleShape& getHealthBar() { sf::RectangleShape* temp = &m_HealthBar; return *temp; }
		const sf::RectangleShape& getExpBar() { sf::RectangleShape* temp = &m_ExpBar; return *temp; }
	};

}


class Pokemon
{
private:
	std::string			m_name{ "None" };
	PokemonAnimation	animation;
	uint32_t			m_level{ 1 };
	uint32_t			m_exp{ 0 };
	uint32_t			max_next_exp{ 10 };
private:
	//Pokemon stats
	int32_t				m_health{ 10 };
	int32_t				max_health{ 10 };
	int32_t				m_attack{ 1 };
	int32_t				m_defense{ 1 };
	int32_t				m_SpecialAttack{ 1 };
	int32_t				m_SpecialDefense{ 1 };
	int32_t				m_Speed{ 1 };
public:
	GUI::PkmGUI			PokemonGUI;
public:
	Pokemon(std::string name, int x1, int y1, int x2, int y2);
	void Update();
	void UpdateFront() { animation.UpdateFront(); }
	void UpdateBack() { animation.UpdateBack(); }
	void setLevel(unsigned x) { m_level = x; Update(); }
	void setHealth(int x) { m_health = x; Update(); }
	void setExp(unsigned x) { m_exp = x; Update(); }
	void Damaged(int x) { m_health -= x; Update(); }
	void increaseExp(int x) { m_exp += x; Update(); }
	void Healed(int x) { m_health += x; Update();}
	std::string getName() { return m_name; }
	int32_t getLevel() { return m_level; }
	int32_t getHealth() { return m_health; }
	int32_t getExp() { return m_exp; }
	int32_t getMaxHealth() { return max_health; }
	unsigned gettMaxExp() { return max_next_exp; }
	sf::RectangleShape& getAvatar_back() { return animation.GetBack(); }
	sf::RectangleShape& getAvatar_front() { return animation.GetFront(); }
	std::tuple<std::string, unsigned, int32_t, int32_t, unsigned, unsigned> getStats();
};

