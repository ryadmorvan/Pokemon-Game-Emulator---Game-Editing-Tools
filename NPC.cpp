#include "NPC.h"
#include <iostream>

#define Animation(animation_ver,options, animation, movement) \
	animation_ver = movement; options++; if (options > 2) { options = 0; } animation = options;

//Collison class
//NPC Classes
void NPC::getSize()
{
	textureSize = NPCTexture.getSize();
	textureSize.x /= 3; textureSize.y /= 4;
	avatar.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
}


NPC::NPC(float x, float y, std::string fileName) : avatar(sf::Vector2f(x, y))
{
	NPCTexture.loadFromFile(fileName); avatar.setTexture(&NPCTexture);
	getSize();
	avatar.setOrigin(x / 2, y / 2);

}

void NPC::update(const sf::RectangleShape& map)
{
	if (avatar.getPosition().x < 0) { avatar.setPosition(0.0f, avatar.getPosition().y); }
	if (avatar.getPosition().x > map.getSize().x) { avatar.setPosition(map.getSize().x, avatar.getPosition().y); }
	if (avatar.getPosition().y < 0) { avatar.setPosition(avatar.getPosition().x, 0.f); }
	if (avatar.getPosition().y > map.getSize().y) { avatar.setPosition(avatar.getPosition().x, map.getSize().y); }
}



void NPC::movement(enum move option)
{
	float deltaTime2;
	if ((deltaTime2 = static_cast<float>(clock.getElapsedTime().asMilliseconds())) >= 96)
	{
		clock.restart();
		int animation_ver{ 0 };
		static int left{ 0 }, right{ 0 }, up{ 0 }, down{ 0 };
		static int animation;
		if (option == DOWN) { Animation(animation_ver, down, animation, 0); }
		if (option == UP) { Animation(animation_ver, up, animation, 1); }
		if (option == LEFT) { Animation(animation_ver, left, animation, 2); }
		if (option == RIGHT) { Animation(animation_ver, right, animation, 3); }
		avatar.setTextureRect(sf::IntRect(textureSize.x * animation, textureSize.y * animation_ver, textureSize.x, textureSize.y));
	}

}

void NPC::setPosition(float x, float y)
{
	avatar.setPosition(x, y);
}


sf::Vector2f NPC::GetPosition() const
{
	return avatar.getPosition();
}

NPC::~NPC()
{

}