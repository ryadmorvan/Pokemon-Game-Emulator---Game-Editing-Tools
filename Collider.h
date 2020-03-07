#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
private:
	sf::RectangleShape& body;
	float				m_weight{ 0 };
public:
	Collider(sf::RectangleShape& body);
	~Collider();
	void Move(float dx, float dy) { body.move(dx, dy); }
	bool Check(Collider&& other);
	void setWeight(float weight) { m_weight = weight; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	sf::Vector2f GetSize() { return body.getSize(); }
};
