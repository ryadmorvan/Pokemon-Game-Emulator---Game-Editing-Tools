#pragma once
#include <SFML\Graphics.hpp>


namespace GUI
{
	class MenuOption
	{
	private:
		std::string m_fileName;
	private:
		sf::RectangleShape Menu;
		sf::Texture MenuTexture;
	public:
		MenuOption() = default;
		MenuOption(std::string fileName);
		void operator=(const MenuOption &&option);
		sf::RectangleShape& GetOption() { sf::RectangleShape* temp = &Menu; return *temp; }
	};

	enum options {LEFT, RIGHT, UP, DOWN};
	class BattleMenu
	{
	private:
		MenuOption OptionList[2][2];
		int x{ 0 }, y{ 0 };
		MenuOption *OptionPointer;
	public:
		bool Update(bool &stillBattle);
		BattleMenu();
		~BattleMenu();
		void move(const options &option);
		sf::RectangleShape& GetOption();
		void draw(sf::RenderWindow& window);
	};


}