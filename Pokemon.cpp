#include "Pokemon.h"
#include <iostream>
#include <sstream>

Pokemon::Pokemon(std::string name, int x1, int y1, int x2, int y2) : animation{ PokemonAnimation(name, x1, y1, x2, y2) }
{
	PokemonGUI.getStats(this->getStats());
}

void Pokemon::Update()
{
	PokemonGUI.getStats(this->getStats());
}

std::tuple<std::string, unsigned, int32_t, int32_t, unsigned, unsigned> Pokemon::getStats()
{
	unsigned level = this->getLevel();
	int32_t health = this->getHealth();
	int32_t Max_Health = this->getMaxHealth();
	std::string name = this->getName();
	unsigned exp = this->getExp();
	unsigned max_exp = this->gettMaxExp();

	return std::make_tuple(name, level, health, Max_Health, exp, max_exp);
}




//Pokemon GUI;


GUI::PkmGUI::PkmGUI()
{
	if (!font.loadFromFile("Font/ObelixProB-cyr.ttf"))
	{
		std::cout << "COuldn't load" << std::endl;
	}
	Healthbar.setFont(font);
	Level.setFont(font);
	Name.setFont(font);
	m_HealthBar.setSize(sf::Vector2f(MAX_BAR_SIZE, 13.0f));
	black_bar.setSize(sf::Vector2f(MAX_BAR_SIZE, 15.0f));
	m_ExpBar.setSize(sf::Vector2f(MAX_BAR_SIZE, 5.0f));
	black_bar2.setSize(sf::Vector2f(MAX_BAR_SIZE, 7.0f));
	m_HealthBar.setFillColor(sf::Color::Green);
	m_ExpBar.setFillColor(sf::Color::Blue);
	black_bar.setFillColor(sf::Color::Black);
	black_bar2.setFillColor(sf::Color::Black);
}

void GUI::PkmGUI::getStats(const std::tuple<std::string, unsigned, int32_t, int32_t, unsigned, unsigned>&& stats)
{
	_stats = stats;
}

void GUI::PkmGUI::statsUpdate()
{
	m_HealthBar.setSize(sf::Vector2f(MAX_BAR_SIZE * ( static_cast<float> (std::get<2>(_stats)) / std::get<3>(_stats)), 13.0f));
	m_ExpBar.setSize(sf::Vector2f(MAX_BAR_SIZE * (static_cast<float>(std::get<4>(_stats)) / std::get<5>(_stats)), 5.0f));
}

void GUI::PkmGUI::draw_back(sf::RenderWindow& window)
{
	statsUpdate();
	std::stringstream stat; stat << std::get<2>(_stats) << "/" << std::get<3>(_stats); 	Healthbar.setString(stat.str());
	std::stringstream stat2; stat2 << std::get<1>(_stats); Level.setString(stat2.str());
	std::stringstream stat3; stat3 << std::get<0>(_stats); Name.setString(stat3.str());
	Level.setCharacterSize(15); Level.setFillColor(sf::Color(50, 45, 23)); Level.setPosition(475.0f, 177.f);
	Healthbar.setCharacterSize(8); Healthbar.setFillColor(sf::Color(50, 33, 42)); Healthbar.setPosition(465.0f, 202.0f);
	Name.setCharacterSize(13); Name.setFillColor(sf::Color(43, 88, 43)); Name.setPosition(475.0f, 155.f);
	black_bar.setPosition(465.0f, 200.0f);
	m_HealthBar.setPosition(465.0f, 200.0f);
	black_bar2.setPosition(465.0f, 225.0f);
	m_ExpBar.setPosition(465.0f, 225.0f);
	window.draw(black_bar);
	window.draw(m_HealthBar);
	window.draw(black_bar2);
	window.draw(m_ExpBar);
	window.draw(Level);
	window.draw(Name);
	window.draw(Healthbar);
}

void GUI::PkmGUI::draw_front(sf::RenderWindow& window)
{
	statsUpdate();
	std::stringstream stat2; stat2 << std::get<1>(_stats); Level.setString(stat2.str());
	std::stringstream stat3; stat3 << std::get<0>(_stats); Name.setString(stat3.str());
	Name.setCharacterSize(13); Name.setFillColor(sf::Color(43, 88, 43)); Name.setPosition(-445.0f, -285.0f);
	Level.setCharacterSize(15); Level.setFillColor(sf::Color(50, 45, 23)); Level.setPosition(-455.0f, -263.f);
	black_bar.setPosition(-455.0f,-242.0f);
	m_HealthBar.setPosition(-455.0f,-242.0f);
	window.draw(black_bar);
	window.draw(m_HealthBar);
	window.draw(Name);
	window.draw(Level);
}
