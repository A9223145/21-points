#ifndef GAMBLER_H
#define GAMBLER_H
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

class Gambler
{
private:
	int hand[6];//手牌
	int handNum;//手牌張數
	int* split;//手牌(分牌)
	int splitNum;//手牌張數(分牌)
	int money;//持有金
	int bet;//賭注
	int splitBet;//賭注(分牌)
	bool isBlackjack;//21點
	bool isInsurance;//保險
	bool isSplit;//分牌
	bool isDouble;//加注
	bool isSplitDouble;//加注(分牌)
	bool isSurrender;//投降
	bool isStand;//停牌
	bool isSplitStand;//停牌(分牌)
public:
	Gambler();

	friend class BlackJack;
};
#endif