#pragma once
#include <SFML\Graphics.hpp>

enum menu_options {UP_M, DOWN_M, GAME_START, GAME_EDITOR, QUIT};
class UI_Master
{
protected:
	sf::RectangleShape	Menu;
	sf::Texture			texture;
	sf::Vector2u		textureSize;
	int					iterator{ 0 };
	int					FrameCount{ 0 };
	void update();
public:
	sf::Clock			clock;
	UI_Master(std::string fileName, unsigned frames_x, unsigned frames_y);
	sf::RectangleShape& getMenu();
	void choice(menu_options options) { if (options == UP_M) { --iterator; } if (options == DOWN_M) { ++iterator; } update(); }
	int enter_choice() { return iterator; }
};

