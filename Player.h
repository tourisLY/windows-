#ifndef PLAYER_H
#define PLAYER_H
#include "Body.h"

class Player : public Body {
	public:
		int money;
		Player(int _hpMax, int _xPow, int _yPos, int _attackPower);
		~Player();
		void PlayerMove(int _xInput, int _yInput, int *map);
		bool Alive(int *map);
		void GetMoney(int moneyNum);
		void GetShop(int moneyNum);
	protected:
};

#endif