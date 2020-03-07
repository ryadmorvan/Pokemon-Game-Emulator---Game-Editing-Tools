#include "BattleMenuGUI.h"

GUI::MenuOption::MenuOption(std::string fileName) : m_fileName{ fileName }
{
	MenuTexture.loadFromFile(m_fileName);
	float x = MenuTexture.getSize().x;
	float y = MenuTexture.getSize().y;
	Menu.setSize(sf::Vector2f(x, y));
	Menu.setTexture(&MenuTexture);
	Menu.setPosition(-50.0f, 270.0f);
}

void GUI::MenuOption::operator=(const MenuOption&& option)
{
	this->m_fileName = option.m_fileName;
	this->Menu = option.Menu;
	this->MenuTexture = option.MenuTexture;
	this->Menu.setTexture(&MenuTexture);
}






bool GUI::BattleMenu::Update(bool &stillBattle)
{
	if (x == 1 && y == 1) {stillBattle = false;}
	return true;
}

//BattleMenu
GUI::BattleMenu::BattleMenu()
{
	OptionList[0][0] = MenuOption("BattleMenu/BattleMenu01.png");
	OptionList[0][1] = MenuOption("BattleMenu/BattleMenu02.png");
	OptionList[1][0] = MenuOption("BattleMenu/BattleMenu03.png");
	OptionList[1][1] = MenuOption("BattleMenu/BattleMenu04.png");
	OptionPointer = &OptionList[x][y];
}
GUI::BattleMenu::~BattleMenu()
{
}
void GUI::BattleMenu::move(const GUI::options& option)
{
	if (option == LEFT) { --x; }
	if (option == RIGHT) { ++x; }
	if (option == DOWN) { ++y; }
	if (option == UP) { --y; }
	if (x < 0) { x = 1; }; if (x > 1) { x = 0; };
	if (y < 0) { y = 1; }; if (y > 1) { y = 0; };

}
sf::RectangleShape& GUI::BattleMenu::GetOption()
{
	OptionPointer = &OptionList[y][x];
	return OptionPointer->GetOption();
}

void GUI::BattleMenu::draw(sf::RenderWindow& window)
{
	window.draw(GetOption());
}
