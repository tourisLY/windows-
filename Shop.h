#ifndef SHOP_H
#define SHOP_H
#include <math.h>
#include <iostream>
using namespace std;

class Shop {
	public:
		bool shopFlag;//�ж��Ƿ��һ�ν����̵�ˢ��
		int shopNum;
		int shopNo[3];
		bool goodExit[3];
		int shopRefreshSpend;
		Shop();
		~Shop();
		struct shopGoods {
			int value;
			int num;
			string name;
			int nameLen;
			string describe;
			int describeLen;
			int attackPower, hpMax;

		} goods[10];
		void goodsAlive();
		void ShopSale(int goodNumber);
		void RefreshSpend(int reset);
	protected:
};


#endif