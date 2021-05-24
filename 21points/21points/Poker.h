#ifndef POKER_H
#define POKER_H
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

class Poker
{
private:
	int deck[52];//�P�� 
	int playerCard[5];//���a��P 
	int bankerCard[5];//���a��P 
	int money;//�� 
	int bet;//��` 
	int cardNum;//��P���P������ 
public:
	Poker();//�غc�l 

	int* getPlayerCard();
	void setPlayerCard(int, int);//(���]�w����,����諸��m) 
	int* getBankerCard();
	void setBankerCard(int, int);//(���]�w����,����諸��m) 
	int getMoney();
	void setMoney(int);
	int getBet();
	void setBet(int);
	int getCardNum();
	void setCardNum(int);

	void setSrand();//�]�w�üƺؤl 
	void setDefaultDeck();//��l�ƵP��

	void shuffle();//�~�P 
	void printPoint(int);//�L�X�I��(J,Q,K�� 
	void printSuit(int);//�L�X���(���ߡA����� 
	void printPlayerCard();//�L�X���a��P
	void printBankerCard();//�L�X���a��P 

	int getNumOfCard(int[]);//���o��P�i�� 
	int getPoint(int[]);//���o��P�o�I 
	void checkOver21(int[]);//�P�_�o�I�O�_�j��21 

	void playerAsk();//���a�n�P 
	void stopAsk();//���a����n�P 
	void bankerAsk();//���a�n�P 
	void BankerPointCheck();//�ˬd���a�o�I�O�_�j��17 

	void over21End();//���H�o�I�j��21���C�����G 
	void equal5End();//�L�������C�����G
	void notOver21End();//�S�H�o�I�j��21���C�����G 

	void choice();//��ܩ�Por�����Por���s�}�lor�����C�� 
	void newGame();//�}�ҷs�C�� 
};
#endif
