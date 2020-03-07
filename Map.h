#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Collider.h"


class DrawInfo;


class Tile
{
private:
	std::string				TextureName;
	sf::Texture				tileTexture;
	float					m_weight{ 1.0f };
	float x{ tile.getPosition().x }, y{ tile.getPosition().y };
	bool					CollideAble{ false };
public:
	sf::RectangleShape		tile;
	Tile();
	Tile(std::string fileName, float x, float y);
	Collider GetCollider() { Collider temp = Collider(tile); temp.setWeight(m_weight); return temp; }
	void setWeight(float weight) { m_weight = weight; }
	void setCollideAble(bool option) { CollideAble = option; }
	void setPosition(float x, float y);
	void setTexture(std::string fileName);
	void detectMouse(sf::Mouse& button, DrawInfo &draw, sf::RenderWindow &window);
	void move(float x, float y) { tile.move(x, y); }
	bool getCollideAble() const { return CollideAble; }
	std::string getTextureName() const { return TextureName; }
	sf::RectangleShape& getTile()
	{
		sf::RectangleShape* temp;
		temp = &tile;
		return *temp;
	}
	void load(std::string name) { tileTexture.loadFromFile(name); tile.setTexture(&tileTexture); }

};


class DrawInfo
{
private:
	std::string				fileName;
public:
	std::shared_ptr<Tile>	tile;
public:
	DrawInfo(std::string fileNam);
	void operator=(const Tile& other);
	void setCollideable(bool option) { tile->setCollideAble(option);}
	void move(float x, float y, const sf::RectangleShape& map) { tile->tile.move(sf::Vector2f(x, y)); update(map); }
	void set(std::string name) { fileName = name; tile->load(fileName); }
	std::string getName() const { return fileName; }
	//std::shared_ptr<Tile> getTile() { return tile; }
	void update(const sf::RectangleShape &map);
};




class Map
{
public:
	std::vector<std::shared_ptr<Tile>> map;
	Map() = default;
	void insertTile(DrawInfo &draw);
	void Save();
	void Load();
	void draw(sf::RenderWindow& window);
};