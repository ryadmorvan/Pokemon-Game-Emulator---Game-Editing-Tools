#include "Animation.h"


PokemonAnimation::PokemonAnimation(std::string fileName, int x1, int y1, int x2, int y2) : FrontFrame_x{ x1 }, FrontFrame_y{ y1 }, BackFrame_x{ x2 }, BackFrame_y{ y2 }
{
	std::string TextureBack{ "Pokemon Sprites/" };
	std::string TextureFront{ "Pokemon Sprites/" };
	TextureBack += fileName + "-Back.png";
	TextureFront += fileName + "-Front.png";
	Texture_Front.loadFromFile(TextureFront);
	Texture_Back.loadFromFile(TextureBack);
	FrontSize = Texture_Front.getSize();
	BackSize = Texture_Back.getSize();
	FrontSize.x /= x1; FrontSize.y /= y1;
	BackSize.x /= x2; BackSize.y /= y2;
	Animation_Front.setSize(sf::Vector2f(FrontSize.x, FrontSize.y));
	Animation_Back.setSize(sf::Vector2f(BackSize.x, BackSize.y));
	Animation_Front.setTexture(&Texture_Front);
	Animation_Back.setTexture(&Texture_Back);
	Animation_Front.setOrigin((float)x1 / 2, (float)y1 / 2);
	Animation_Back.setOrigin((float)x2 / 2, (float)y2 / 2);
	Animation_Front.setPosition(280, -200);
	Animation_Back.setPosition(-300, 170);
	Animation_Back.scale(2., 2);
	Animation_Front.scale(2, 2);
}

void PokemonAnimation::UpdateFront()
{
	float DeltaTime;
	if ((DeltaTime = static_cast<float>(clock.getElapsedTime().asMilliseconds())) >= 33)
	{
	clock.restart();
	static int y{ 0 };
	static int x{ 0 };
	if (y >= FrontFrame_y) { y = 0; }
	if (x >= FrontFrame_x) { x = 0; }
	Animation_Front.setTextureRect(sf::IntRect(FrontSize.x* x, FrontSize.y* y, FrontSize.x, FrontSize.y));
	++x;
	if (x >= FrontFrame_x) { ++y; }
	}
}

void PokemonAnimation::UpdateBack()
{
	float DeltaTime;
	if ((DeltaTime = static_cast<float>(clock.getElapsedTime().asMilliseconds())) >= 33)
	{
		clock.restart();
		static int y{ 0 };
		static int x{ 0 };
		if (y >= BackFrame_y) { y = 0; }
		if (x >= BackFrame_x) { x = 0; }
		Animation_Back.setTextureRect(sf::IntRect(BackSize.x * x, BackSize.y * y, BackSize.x, BackSize.y));
		++x;
		if (x >= BackFrame_x) { ++y; }
	}
}