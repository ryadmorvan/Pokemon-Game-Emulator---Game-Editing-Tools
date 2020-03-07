#include "UI_Master.h"


UI_Master::UI_Master(std::string fileName, unsigned frames_x, unsigned frames_y)
{
	texture.loadFromFile(fileName); float x = texture.getSize().x/frames_x; float y = texture.getSize().y/frames_y;
	Menu.setSize(sf::Vector2f(x, y));
	Menu.setTexture(&texture);
	textureSize.x = texture.getSize().x/frames_x;
	textureSize.y = texture.getSize().y / frames_y;
	Menu.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
	FrameCount = frames_x * frames_y;
}

sf::RectangleShape& UI_Master::getMenu() 
{
	sf::RectangleShape* temp = &Menu;
	return *temp;
}


void UI_Master::update()
{
	if (iterator > 2) { iterator = 0; }
	if (iterator < 0) { iterator = 2; }
	Menu.setTextureRect(sf::IntRect(textureSize.x * iterator, textureSize.y * 0, textureSize.x, textureSize.y));
}