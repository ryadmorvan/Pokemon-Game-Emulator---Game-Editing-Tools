#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class PokemonAnimation
{
private:
	sf::Clock			clock;
	sf::RectangleShape	Animation_Front;
	sf::RectangleShape	Animation_Back;
	sf::Texture			Texture_Front;
	sf::Texture			Texture_Back;
	sf::Vector2u		FrontSize;
	sf::Vector2u		BackSize;
	int				FrontFrame_x;
	int				FrontFrame_y;
	int				BackFrame_x;
	int				BackFrame_y;
public:
	PokemonAnimation(std::string fileName, int x1, int y1, int x2, int y2);
	void UpdateFront();
	void UpdateBack();
	sf::RectangleShape& GetFront() { sf::RectangleShape* temp = &Animation_Front; return *temp; }
	sf::RectangleShape& GetBack() { sf::RectangleShape* temp = &Animation_Back; return *temp; }
};
