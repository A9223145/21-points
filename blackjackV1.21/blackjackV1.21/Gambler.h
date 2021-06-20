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
	int hand[6];//��P
	int handNum;//��P�i��
	int* split;//��P(���P)
	int splitNum;//��P�i��(���P)
	int money;//������
	int bet;//��`
	int splitBet;//��`(���P)
	bool isBlackjack;//21�I
	bool isInsurance;//�O�I
	bool isSplit;//���P
	bool isDouble;//�[�`
	bool isSplitDouble;//�[�`(���P)
	bool isSurrender;//�뭰
	bool isStand;//���P
	bool isSplitStand;//���P(���P)
public:
	Gambler();

	friend class BlackJack;
};
#endif