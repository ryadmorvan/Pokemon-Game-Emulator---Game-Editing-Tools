#include "Map.h"
#include <algorithm>
#include <thread>
#include <sstream>
#include <mutex>
#include <fstream>

//Tiles

Tile::Tile() : tile(sf::Vector2f(16.0f, 16.0f))
{
	tileTexture.loadFromFile("Map Sprites/Grass03.png"); tile.setTexture(&tileTexture);
	tile.setOrigin(8.0f, 8.0f);
	tile.setPosition(0, 0);
}


Tile::Tile(std::string fileName, float x, float y) : tile(sf::Vector2f(16.0f, 16.0f))
{
	tileTexture.loadFromFile(fileName); tile.setTexture(&tileTexture);
	tile.setOrigin(8.0f, 8.0f);
	tile.setPosition(x, y);
	TextureName = fileName;
}

void Tile::setPosition(float x, float y)
{
	tile.setPosition(x, y);
}

void Tile::setTexture(std::string fileName)
{
	TextureName = fileName; tileTexture.loadFromFile(fileName);
	tile.setTexture(&tileTexture);
}

void Tile::detectMouse(sf::Mouse& button, DrawInfo& draw, sf::RenderWindow &window)
{
	if (button.getPosition(window).x >= tile.getPosition().x && button.getPosition(window).x <= (tile.getPosition().x + tile.getSize().x))
	{
		if (button.getPosition(window).y >= tile.getPosition().y && button.getPosition(window).y <= (tile.getPosition().y + tile.getSize().y))
		{
			draw = *this;
		}
	}
}



//DrawInfo
////////////////////////////////////////////////////////////////////////////////////////
DrawInfo::DrawInfo(std::string fileName) :fileName{ fileName }
{
	tile = std::make_shared<Tile>(fileName, 0.0f, 0.0f);
}

void DrawInfo::update(const sf::RectangleShape& map)
{
	if (tile->tile.getPosition().x < 0) { tile->tile.setPosition(0.0f, tile->tile.getPosition().y); }
	if ((tile->tile.getPosition().x + tile->tile.getSize().x) > map.getSize().x) { tile->tile.setPosition(map.getSize().x - tile->tile.getSize().x, tile->tile.getPosition().y); }
	if (tile->tile.getPosition().y < 0) { tile->tile.setPosition(tile->tile.getPosition().x, 0.0f); }
	if ((tile->tile.getPosition().y + tile->tile.getSize().y) > map.getSize().y) { tile->tile.setPosition(tile->tile.getPosition().x, map.getSize().y - tile->tile.getSize().y); }
}

void DrawInfo::operator=(const Tile& other) { tile->setTexture(other.getTextureName()); fileName = other.getTextureName(); }


//Map
////////////////////////////////////////////////////////////////////////////////////////
void Map::insertTile(DrawInfo& draw)
{
	auto copy = std::make_shared<Tile>(draw.getName(), draw.tile->tile.getPosition().x, draw.tile->tile.getPosition().y);
	copy->setCollideAble(draw.tile->getCollideAble());
	bool successful = false;
	std::replace_if(map.begin(), map.end(), [this, &successful, &draw](std::shared_ptr<Tile> tile)
	{
		if ((draw.tile->tile.getPosition().x == tile->tile.getPosition().x) && (draw.tile->tile.getPosition().y == tile->tile.getPosition().y)) { successful = true; }
		return (draw.tile->tile.getPosition().x == tile->tile.getPosition().x) && (draw.tile->tile.getPosition().y == tile->tile.getPosition().y);
	}, copy);
	if (successful == false)
	{
		map.emplace_back(copy);
	}
}


void Map::Save()
{
	std::ofstream file("Map_Data/Map.txt");
	if (!map.empty())
	{
		for (auto& tile : map)
		{
			file << tile->getTextureName() << " " << tile->tile.getPosition().x << " " << tile->tile.getPosition().y << " " << tile->getCollideAble() << std::endl;
		}
	}
}

void Map::Load()
{
	std::string streamLine;

	std::string fileName;
	bool Collidable{ false };
	int x{ 0 }, y{ 0 };
	std::ifstream file("Map_Data/Map.txt");
	while (std::getline(file, streamLine))
	{
		std::stringstream stream{ streamLine };
		stream >> fileName >> x >> y >> Collidable;
		auto temp = std::make_shared<Tile>(fileName, x, y);
		temp->setCollideAble(Collidable);
		map.emplace_back(temp);
	}
}

void Map::draw(sf::RenderWindow& window)
{

	//for (auto& tile : map)
	//{
	//	window.draw(tile->getTile());
	//}
	std::mutex m;
	auto work = [&](unsigned range_start, unsigned range_stop) {
		for (; range_start < range_stop; ++range_start)
		{
			window.draw(map.at(range_start)->getTile());
		}
	};

	std::thread t1(work, 0, 71);
	std::thread t2(work, 72, 144);
	std::thread t3(work, 145, 217);
	std::thread t4(work, 218, 287);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();




}