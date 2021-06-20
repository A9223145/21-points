#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Gambler.h"
#include<iostream>
using namespace std;

class BlackJack
{
private:
	int* deck;//�P��
	int askTimes;//�n�P����
	int playerNum;//�C���H��
	Gambler* player;//���a
	int dealer[6];//���a��P
	int dealerHandNum;//���a��P�i��
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
	void splitAsk(int);
	void printDealer();
	void printStatus();
	void printStatus(int[]);
	void printStatus(int);
	void printSplitStatus(int);
	void printSuit(int);//�L�X���(���ߡA����� 
	void printPoint(int);//�L�X�I��(J,Q,K�� 
	void process();

};
#endif