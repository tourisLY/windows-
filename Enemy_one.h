#ifndef ENEMY_ONE_H
#define ENEMY_ONE_H

#include "Body.h"
#include <cstdlib>
#include <math.h>

class Enemy_one : public Body {
	public:
		bool isHurt;
		int value;
		Enemy_one(int _hpMax, int _xPow, int _yPos, int _attackPower);
		Enemy_one();
		~Enemy_one();
		void Alive(int _xPosStart, int xPosStart, int *map);
		bool EnemyMove(int xPlayerPos, int yPlayerPos, int *map, int moveNum);
		bool Damage(int _damageNum);
		void RedCancle();
	protected:
};

#endif