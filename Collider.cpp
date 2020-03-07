#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) : body(body)
{

}

bool Collider::Check(Collider&& other)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x; //Now we subtract the x with the other x to get the delta X
	float deltaY = otherPosition.y + 10 - thisPosition.y; //Now we subtract the y wiith the other y to get the delta Y

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y) + 7;

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		m_weight = std::min(std::max(m_weight, 0.0f), 1.0f); //Will convert the push from a value to interval 0.0f to 1.0f

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - m_weight), 0.0f);
				other.Move(-intersectX * m_weight, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - m_weight), 0.0f);
				other.Move(intersectX * m_weight, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - m_weight));
				other.Move(0.0f, -intersectY * m_weight + 2);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - m_weight));
				other.Move(0.0f, intersectY * m_weight);
			}
		}

		return true; //If it collides it will return true
	}

	return false;
}

Collider::~Collider() {}