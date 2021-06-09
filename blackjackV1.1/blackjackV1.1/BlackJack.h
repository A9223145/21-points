#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Gambler.h"
#include<iostream>
using namespace std;

class BlackJack
{
private:
	int* deck;//牌堆
	int askTimes;//要牌次數
	int playerNum;//遊戲人數
	Gambler* player;//玩家(0號以外為AI)
	int dealer[6];//莊家手牌
	int dealerHandNum;//莊家手牌張數
public:
	void peek();
	void peek2();
	void peek3();
	BlackJack();
	void setPlayerNum();
	void setPlayerNum(int);
	int getPoint(int[]);
	int getPoint(int);
	void askCard();
	void askCard(int);

};
#endif