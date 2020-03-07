#include <SFML/Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <array>
#include <thread>
#include <memory>


#include "UI_Master.h"
#include "Menus.h"
#include "Player.h"
#include "Map.h"
#include "Motion_Collide.h"
#include "WorldEvents.h"
#include "Pokemon.h"


bool GAME_QUIT = false;
bool GAME_START_Q = false;

inline void check_event(sf::Window& window, sf::Event& evnt)
{
	switch (evnt.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 668), "Pokemon", sf::Style::Close | sf::Style::Titlebar);
	sf::RectangleShape map(sf::Vector2f(1600.0f, 668.0f)); sf::Texture mapTexture; mapTexture.loadFromFile("NPC Sprites/PalletTown.png"); map.setTexture(&mapTexture);
	sf::View view1;	view1.setSize(1100.0f, 733.0f);	view1.zoom(0.5f);
	Map map2;




	//it will start 
	sf::Clock clock;
	float deltaTime;
	const float multiplier = 30.0f;
	///////////////////////////////////////////////Game Frames

	while (window.isOpen())
	{
			window.setFramerateLimit(30);
			sf::Event evnt;
			sf::FloatRect visibleArea1(0, 0, 1600, 668);
			window.setSize(sf::Vector2u(1600, 668));
			window.setView(sf::View(visibleArea1));
			while (GAME_START_Q == false) { Menu(window, evnt, check_event, GAME_QUIT, GAME_START_Q); }
			if (GAME_QUIT == true) { break; }
			std::unique_ptr<Player> player = std::make_unique<Player>(16.0f, 20.0f, "NPC Sprites/Red-Walking.png");
			map2.Load();
			sf::FloatRect visibleArea2(0, 0, 1100, 733);
			window.setSize(sf::Vector2u(1100, 733));
			window.setView(sf::View(visibleArea2));



			while (GAME_QUIT != true)
			{
				window.setFramerateLimit(120);
				while (window.pollEvent(evnt)) { check_event(window, evnt); }
				deltaTime = clock.restart().asSeconds();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { player->movement(DOWN);  player->move(0.0f, player->getVelocity() * deltaTime * multiplier, map); }
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { player->movement(UP); player->move(0.0f, -(player->getVelocity()) * deltaTime * multiplier, map); }
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { player->movement(LEFT); player->move(-(player->getVelocity()) * deltaTime * multiplier, 0.0f, map); }
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { player->movement(RIGHT); player->move(player->getVelocity() * deltaTime * multiplier, 0.0f, map); }
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { GAME_START_Q = false; break;}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) { PokemonBattle(window, evnt, player.get(), check_event); }
				Collison_Detect(map2, player.get());


				view1.setCenter(player->GetPosition());

				//Collison



				window.clear();
				window.setView(view1);
				window.draw(map);
				map2.draw(window);
				window.draw(player->getAvatar());
				window.display();
			}
	}






	return 0;
}
