#include "Player.h"

Player::Player(float x, float y, std::string fileName) : NPC(x, y, fileName) {}

void Player::setName(std::string Name) { m_name = Name; }


Player::~Player() {}