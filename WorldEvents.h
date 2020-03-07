#pragma once
#include "Animation.h"
#include "Pokemon.h"
#include "BattleMenuGUI.h"
#include <memory>

void PokemonBattle(sf::RenderWindow &window, sf::Event &evnt, Player *player, void (*checkEvent)(sf::Window &window, sf::Event &evnt))
{
	bool stillBattle = true;
	std::shared_ptr<Pokemon> pokemon = std::make_shared<Pokemon>("002", 10, 11, 10, 11);
	std::shared_ptr<Pokemon> pokemon2 = std::make_shared<Pokemon>("005", 8, 11, 9, 9);
	player->Push_Pokemon(pokemon);
	//Window Properties///////////////////////////////////////////////////////////////////////////////////////////////
	sf::FloatRect visibleArea(-500, -350, 1100, 733);
	sf::View view(visibleArea);
	window.setView(view);
	sf::RectangleShape landScape(sf::Vector2f(1128, 738)); sf::Texture land; land.loadFromFile("Land.png"); landScape.setTexture(&land); landScape.setPosition(-500, -350);
	window.setFramerateLimit(120);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GUI::BattleMenu Menu;
	while (window.isOpen() && (stillBattle != false))
	{
		while (window.pollEvent(evnt)) { checkEvent(window, evnt);
		if (evnt.type == sf::Event::KeyPressed) { if (evnt.key.code == sf::Keyboard::Up) Menu.move(GUI::UP); }
		if (evnt.type == sf::Event::KeyPressed) { if (evnt.key.code == sf::Keyboard::Down) Menu.move(GUI::DOWN); }
		if (evnt.type == sf::Event::KeyPressed) { if (evnt.key.code == sf::Keyboard::Left) Menu.move(GUI::LEFT); }
		if (evnt.type == sf::Event::KeyPressed) { if (evnt.key.code == sf::Keyboard::Right) Menu.move(GUI::RIGHT); }
		if (evnt.type == sf::Event::KeyPressed) { if (evnt.key.code == sf::Keyboard::Return) Menu.Update(stillBattle); }
		}
		pokemon2->UpdateFront();
		player->pokemons.at(0)->UpdateBack();
		//Testing







		window.clear();
		window.draw(landScape);
		window.draw(pokemon2->getAvatar_front());
		window.draw(player->pokemons.at(0)->getAvatar_back());
		player->pokemons.at(0)->PokemonGUI.draw_back(window);
		pokemon2->PokemonGUI.draw_front(window);
		Menu.draw(window);
		window.display();
	}
}

