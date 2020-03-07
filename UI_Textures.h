#pragma once
#include <SFML\Graphics.hpp>


class UI_Textures
{
private:
	sf::RectangleShape  UI_Shape;
	int					FrameCount{ 0 };
	sf::Texture			UI_Texture;
	int					iterator{ 0 };
	sf::Vector2u		textureSize;
public:
	UI_Textures(std::string fileName, unsigned frames_x, unsigned frames_y);
	sf::RectangleShape& getMenu();
	void setPosition(float x, float y) { UI_Shape.setPosition(x, y); }
	void update(int x);
};
