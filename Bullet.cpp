#include "Bullet.h"

Bullet::Bullet() {
	alive = false;
	for (int i = 0; i < 1000; i++)
		mapNew[i] = 0;
}

Bullet::~Bullet() {
}

void Bullet::Alive(int _xPos, int _yPos, int _xFont, int _yFont, int _damage) {
	xPos = _xPos + _xFont;
	yPos = _yPos + _yFont;
	xFont = _xFont;
	yFont = _yFont;
	damage = _damage;
	alive = true;
}

int Bullet::Move(int *mapIndex, int *popMap) {
	xPos += xFont;
	yPos += yFont;
	if (mapIndex[yPos * 40 + xPos] == 1 || mapNew[yPos * 40 + xPos]==1) {
		Dead();
		return 0;
	}
	if (popMap[yPos * 40 + xPos] != 0 && popMap[yPos * 40 + xPos] != 99) {
		Dead();
		return popMap[yPos * 40 + xPos];
	}
	if(xPos>40||xPos<0||yPos>24||yPos<0)Dead();
	return 0;
}

void Bullet::Dead() {
	alive = false;
}
void Bullet::MapNewChange(int _xPos, int _yPos) {
	mapNew[_yPos * 40 + _xPos] = 1;
}