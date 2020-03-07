#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"
#include "UI_Textures.h"
#include <fstream>
#include <string>
#include <cstdint>



void load_sprites(std::vector<std::shared_ptr<Tile>> &Sprites)
{
	std::string fileLoad;
	int count{ 0 };
	float x{ 1616 }, y{ 60 };
	std::ifstream file; file.open("UI Sprites/SpritesList.txt", std::ios::in);
	while (file>>fileLoad)
	{
		if (count > 7) { y += 16; count = 0; x = 1616; }
		Sprites.emplace_back(std::make_shared<Tile>(fileLoad, x, y));
		x += 16;
		count++;
	}
}









void GameEditorLoop(sf::RenderWindow& Window, sf::Event& evnt, void(&CheckEvent)(sf::Window& window, sf::Event& evnt))
{
	//Window properties
	float VisableX{ 1742 }, VisableY{ 668 };
	sf::FloatRect visibleArea(0, 0, VisableX, VisableY);
	Window.setSize(sf::Vector2u(VisableX, VisableY));
	Window.setView(sf::View(visibleArea));
	Window.setFramerateLimit(125);
	////////////////////////////////////////////////////////////////////////////
	//Drawing mechanic
	DrawInfo draw("MapSprites/Grass.png");
	///////////////////////////////////////////////////////////////////////
	//UI
	sf::RectangleShape UI(sf::Vector2f(1742.0f, 668.0f)); sf::Texture UI_texture; UI_texture.loadFromFile("GameEditor/GameEditorPlatform.png");
	UI.setTexture(&UI_texture);
	UI_Textures UI_Collider("UI Sprites/UI_Static_Object.png", 2, 1);
	UI_Collider.setPosition(1631.0f, 325.0f);
	////////////////////////////////////////////////////////////////////////////////
	//Surface and color
	sf::RectangleShape drawingSurface(sf::Vector2f(1600.0f, 668.0f));
	drawingSurface.setFillColor(sf::Color::Transparent);
	///////////////////////////////////////////////////////////
	//Map loading and unloading
	Map map;
	map.Load();
	////////////////////////////////////////////////////////////
	//Sprites Loading
	std::vector<std::shared_ptr<Tile>> sprites;
	load_sprites(sprites);
	sf::Clock clock;

	while (true)
	{
		while (Window.pollEvent(evnt))
		{
			CheckEvent(Window, evnt);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Mouse mouse;
				for (auto& tile : sprites) { tile->detectMouse(mouse, draw, Window); }
			}
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::F)
				{
					if (draw.tile->getCollideAble() == false) { draw.setCollideable(true);}
					else { draw.setCollideable(false);}
				}
			}
		}
		if (clock.getElapsedTime().asMilliseconds() >= 70)
		{
			clock.restart();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { draw.move(0.0f, -16.0f, drawingSurface); }
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { draw.move(0.0f, 16.0f, drawingSurface); }
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { draw.move(16.0f, 0.0f, drawingSurface); }
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { draw.move(-16.0f, 0.0f, drawingSurface); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { map.insertTile(draw); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { map.Save(); break; }
		}




		UI_Collider.update(draw.tile->getCollideAble());
		Window.clear();
		Window.draw(drawingSurface);
		Window.draw(UI);
		Window.draw(UI_Collider.getMenu());
		map.draw(Window);
		for (auto& tile : sprites)
		{
			Window.draw(tile->getTile());
		}
		Window.draw(draw.tile->getTile());
		Window.display();
	}
	sf::FloatRect visibleArea2(0, 0, 1600, 668);
	Window.setSize(sf::Vector2u(1600, 668));
	Window.setView(sf::View(visibleArea2));
}
