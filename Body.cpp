#include "Body.h"

Body::Body(int _hpMax, int _xPos, int _yPos, int _attackPower) {
	Body::hpMax = _hpMax;
	Body::xPos = _xPos;
	Body::yPos = _yPos;
	Body::attackPower = _attackPower;
	Body::alive = false;
}

Body::~Body() {
}

bool Body::Damage(int _damageNum) {
	Body::hpNow -= _damageNum;
	if (Body::hpNow <= 0) {
		Body::Dead();
		return true;
	}
	return false;
}

void Body::Dead() {
	Body::alive = false;
}

void Body::MapNewChange(int _xPos, int _yPos) {
	mapNew[_yPos * 40 + _xPos] = 1;
}