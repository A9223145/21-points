#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Gambler.h"
#include<iostream>
using namespace std;

class BlackJack
{
private:
	int* deck;//礟帮
	int askTimes;//璶礟Ω计
	int playerNum;//笴栏计
	Gambler* player;//產
	int dealer[6];//缠產も礟
	int dealerHandNum;//缠產も礟眎计
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
	void printSuit(int);//︹(みよ遏单 
	void printPoint(int);//翴计(J,Q,K单 
	void process();

};
#endif