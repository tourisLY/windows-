#ifndef BODY_H
#define BODY_H
#include "Map.h"

class Body {
	public:
		int hpNow, hpMax;
		int xPos, yPos;
		int attackPower;
		bool alive;
		Body(int _hpMax, int _xPos, int _yPos, int _attackPower);
		~Body();
		virtual bool Damage(int _damageNum);
		virtual void Dead();
		int mapNew[1000];
		void MapNewChange(int _xPos, int _yPos);
	protected:
};

#endif