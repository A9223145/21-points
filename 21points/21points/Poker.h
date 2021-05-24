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
	int deck[52];//牌堆 
	int playerCard[5];//玩家手牌 
	int bankerCard[5];//莊家手牌 
	int money;//錢 
	int bet;//賭注 
	int cardNum;//於牌堆抽牌的次數 
public:
	Poker();//建構子 

	int* getPlayerCard();
	void setPlayerCard(int, int);//(欲設定的值,欲更改的位置) 
	int* getBankerCard();
	void setBankerCard(int, int);//(欲設定的值,欲更改的位置) 
	int getMoney();
	void setMoney(int);
	int getBet();
	void setBet(int);
	int getCardNum();
	void setCardNum(int);

	void setSrand();//設定亂數種子 
	void setDefaultDeck();//初始化牌組

	void shuffle();//洗牌 
	void printPoint(int);//印出點數(J,Q,K等 
	void printSuit(int);//印出花色(紅心，方塊等 
	void printPlayerCard();//印出玩家手牌
	void printBankerCard();//印出莊家手牌 

	int getNumOfCard(int[]);//取得手牌張數 
	int getPoint(int[]);//取得手牌得點 
	void checkOver21(int[]);//判斷得點是否大於21 

	void playerAsk();//玩家要牌 
	void stopAsk();//玩家停止要牌 
	void bankerAsk();//莊家要牌 
	void BankerPointCheck();//檢查莊家得點是否大於17 

	void over21End();//有人得點大於21的遊戲結果 
	void equal5End();//過五關的遊戲結果
	void notOver21End();//沒人得點大於21的遊戲結果 

	void choice();//選擇抽牌or停止抽牌or重新開始or結束遊戲 
	void newGame();//開啟新遊戲 
};
#endif
