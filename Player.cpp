#include "Player.h"

Player::Player(int _hpMax, int _xPow, int _yPos, int _attackPower): Body(_hpMax, _xPow, _yPos, _attackPower) {
	money = 10;
	for (int i = 0; i < 1000; i++)
		mapNew[i] = 0;
}

Player::~Player() {
}

void Player::PlayerMove(int _xInput, int _yInput, int *map) {
	if (map[(yPos + _yInput) * 40 + xPos + _xInput] == 0 && mapNew[(yPos + _yInput) * 40 + xPos + _xInput] == 0) {
		xPos += _xInput;
		yPos += _yInput;
	}
}

bool Player::Alive(int *map) {
	hpNow = hpMax;
	if (map[yPos * 40 + xPos] == 0) {
		map[yPos * 40 + xPos] = 2;
	} else {
		return false;
	}
	alive = true;
	return true;
}

void Player::GetMoney(int moneyNum) {
	money += moneyNum;
}

void Player::GetShop(int moneyNum) {
	money -= moneyNum;
}

