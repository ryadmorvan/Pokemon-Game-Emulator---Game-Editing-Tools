#include "UI_Textures.h"


UI_Textures::UI_Textures(std::string fileName, unsigned frames_x, unsigned frames_y)
{
	UI_Texture.loadFromFile(fileName); float x = UI_Texture.getSize().x / frames_x; float y = UI_Texture.getSize().y / frames_y;
	UI_Shape.setSize(sf::Vector2f(x, y));
	UI_Shape.setTexture(&UI_Texture);
	textureSize.x = UI_Texture.getSize().x / frames_x;
	textureSize.y = UI_Texture.getSize().y / frames_y;
	UI_Shape.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
	FrameCount = frames_x * frames_y;
}

sf::RectangleShape& UI_Textures::getMenu()
{
	sf::RectangleShape* temp = &UI_Shape;
	return *temp;
}

void UI_Textures::update(int x)
{
	iterator = x;
	UI_Shape.setTextureRect(sf::IntRect(textureSize.x * iterator, textureSize.y * 0, textureSize.x, textureSize.y));
}