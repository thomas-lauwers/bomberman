#include "../../../include/logic/factory/Player.h"

Player::Player() = default;

EntityType Player::getEntityType() const { return Player_E; }

BomberType Player::getBomberType() const { return BomberType::Player; }
