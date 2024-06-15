#include "Enemy_one.h"

Enemy_one::Enemy_one(): Body(hpMax, xPos, yPos, attackPower) {
	value = 1;
	hpMax = 10;
	hpNow = hpMax;
	xPos = 1;
	yPos = 1;
	attackPower = 5;
	for (int i = 0; i < 1000; i++)
		mapNew[i] = 0;
}


Enemy_one::~Enemy_one() {
	;
}

void Enemy_one::Alive(int xPosStart, int yPosStart, int *map) {
	alive = true;
	hpNow = hpMax;
	xPos = xPosStart;
	yPos = yPosStart;
}

bool Enemy_one::Damage(int _damageNum) {
	hpNow -= _damageNum;
	isHurt = true;
	if (hpNow <= 0) {
		Dead();
		return true;
	}
	return false;
}

bool Enemy_one::EnemyMove(int xPlayerPos, int yPlayerPos, int *map, int moveNum) {
	if (abs(xPos - xPlayerPos) + abs(yPos - yPlayerPos ) <= 1) {
		return true;
	}
	int xfont, yfont;
	xfont = (xPlayerPos - xPos > 0) ? 1 : -1;
	yfont = (yPlayerPos - yPos > 0) ? 1 : -1;
	if (abs(xPos - xPlayerPos) >= 1 && abs(yPos - yPlayerPos ) >= 1) {
		if (moveNum == 0 && map[yPos * 40 + xPos + xfont] == 0&& mapNew[yPos * 40 + xPos + xfont] == 0) {
			xPos += xfont;
		} else if (moveNum == 1 && map[(yPos + yfont) * 40 + xPos] == 0 && mapNew[(yPos + yfont) * 40 + xPos] == 0) {
			yPos += yfont;
		}
	} else if (abs(xPos - xPlayerPos) >= 1 && map[yPos * 40 + xPos + xfont] == 0 && mapNew[yPos * 40 + xPos + xfont] == 0) {
		xPos += xfont;
	} else if (map[(yPos + yfont) * 40 + xPos] == 0 && mapNew[(yPos + yfont) * 40 + xPos] == 0) {
		yPos += yfont;
	}
	return false;
}

void Enemy_one::RedCancle() {
	isHurt = false;
}

