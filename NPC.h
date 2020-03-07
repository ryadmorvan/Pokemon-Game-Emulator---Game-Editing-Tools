#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Collider.h"
#include "Pokemon.h"

enum move { UP, DOWN, LEFT, RIGHT };


class NPC
{
protected:
	std::string			m_name;
	sf::RectangleShape	avatar;
	sf::Clock			clock;
	sf::Texture			NPCTexture;
	sf::Vector2u		textureSize;
	float				x{ avatar.getPosition().x },	y{ avatar.getPosition().y };
	float				velocity{ 2 };
	float				weight{ 1.0f };
	bool CollideAble{ false };
	void getSize();
public:
	NPC(float x, float y, std::string fileName);
	virtual		void update(const sf::RectangleShape& map);
	virtual		void movement(enum move);
	virtual		void setPosition(float x, float y);
	virtual		void setCollideAble(bool option) { CollideAble = option; }
	virtual		void setSpeed(float speed) { velocity = speed; }
	virtual		void setWeight(float m_weight) { weight = m_weight; }
	virtual		float getVelocity() const { return velocity; }
	virtual		void setName(std::string Name) = 0;
	virtual		sf::Vector2f GetPosition() const;
	virtual		void move(float x, float y, const sf::RectangleShape& map) { avatar.move(x, y); update(map); }
	virtual		Collider GetCollider() { Collider temp = Collider(avatar); temp.setWeight(weight); return temp; }
	virtual		sf::RectangleShape &getAvatar() {
		sf::RectangleShape* temp;
		temp = &avatar;
		return *temp;
	}
	virtual ~NPC();
};

