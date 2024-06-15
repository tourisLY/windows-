#include "Shop.h"

Shop::Shop() {
	shopNum = 3;
	shopFlag = false;//判断是否第一次进入商店刷新
}

Shop::~Shop() {
}



//Shop::shopGoods goods[10];
void Shop::ShopSale(int goodNumber) {
	goodExit[goodNumber]  = false;
}

void Shop::RefreshSpend(int reset) {
	if (reset == 0) {
		shopRefreshSpend = 5;
	} else {
		shopRefreshSpend ++;
	}
}

void Shop::goodsAlive() {
	//good0
	goods[0].num = 0;
	goods[0].value = 5;
	goods[0].name = "力量1";
	goods[0].nameLen = 5;
	goods[0].describe = "攻击力+5";
	goods[0].describeLen = 8;
	goods[0].attackPower = 5;
	goods[0].hpMax = 0;

	//good1
	goods[1].num = 1;
	goods[1].value = 5;
	goods[1].name = "活力1";
	goods[1].nameLen = 5;
	goods[1].describe = "最大生命值+20";
	goods[1].describeLen = 13;
	goods[1].attackPower = 0;
	goods[1].hpMax = 20;

	//good2
	goods[2].num = 2;
	goods[2].value = 6;
	goods[2].name = "残忍";
	goods[2].nameLen = 4;
	goods[2].describe = "攻击力+10,最大生命值-20";
	goods[2].describeLen = 23;
	goods[2].attackPower = 10;
	goods[2].hpMax = -20;
}


