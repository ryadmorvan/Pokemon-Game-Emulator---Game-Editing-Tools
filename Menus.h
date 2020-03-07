#pragma once
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include "GameEditorLoop.h"




bool Menu(sf::RenderWindow& window, sf::Event& evnt, void(&check)(sf::Window &window, sf::Event &evnt), bool &GAME_QUIT, bool &GAME_START)
{
	window.setKeyRepeatEnabled(false);
	UI_Master UI("UI Sprites/Menu/UI-0.png", 3, 1);
	UI.clock.restart();
	while (true)
	{
		while (window.pollEvent(evnt)) { check(window, evnt); }
		if (UI.clock.getElapsedTime().asMilliseconds() >= 70)
		{
		UI.clock.restart();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { break; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (UI.enter_choice() == 0) { GAME_START = true; break; }; if (UI.enter_choice() == 2) { GAME_QUIT = true; GAME_START = true; break; } if (UI.enter_choice() == 1) { GameEditorLoop(window, evnt, check); }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { UI.choice(UP_M); }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { UI.choice(DOWN_M); }
		}
		window.clear();
		window.draw(UI.getMenu());
		window.display();
	}
	window.setKeyRepeatEnabled(true);
	return true;
}