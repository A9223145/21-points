#include "Poker.h"

Poker::Poker()//建構子 
{
	//cout << "\nuse Poker";

	cout << "\n88          88                       88        88                       88";
	cout << "\n88          88                       88        \"\"                       88";
	cout << "\n88          88                       88                                 88";
	cout << "\n88,dPPYba,  88 ,adPPYYba,  ,adPPYba, 88   ,d8  88 ,adPPYYba,  ,adPPYba, 88   ,d8";
	cout << "\n88P'    \"8a 88 \"\"     `Y8 a8\"     \"\" 88 ,a8\"   88 \"\"     `Y8 a8\"     \"\" 88 ,a8\"";
	cout << "\n88       d8 88 ,adPPPPP88 8b         8888[     88 ,adPPPPP88 8b         8888[";
	cout << "\n88b,   ,a8\" 88 88,    ,88 \"8a,   ,aa 88`\"Yba,  88 88,    ,88 \"8a,   ,aa 88`\"Yba,";
	cout << "\n8Y\"Ybbd8\"'  88 `\"8bbdP\"Y8  `\"Ybbd8\"' 88   `Y8a 88 `\"8bbdP\"Y8  `\"Ybbd8\"' 88   `Y8a";
	cout << "\n" << setw(49) << ",88";
	cout << "\n" << setw(49) << "888P\"";



	setDefaultDeck();
	setMoney(200);
	setSrand();
	newGame();
	choice();
}



int* Poker::getPlayerCard()
{
	//cout << "\nuse getPlayerCard";

	return playerCard;
}

void Poker::setPlayerCard(int num, int index)//(欲設定的值,欲更改的位置) 
{
	//cout << "\nuse setPlayerCard";

	this->playerCard[index] = num;
}

int* Poker::getBankerCard()
{
	//cout << "\nuse getBankerCard";

	return bankerCard;
}

void Poker::setBankerCard(int num, int index)//(欲設定的值,欲更改的位置) 
{
	//cout << "\nuse setBankerCard";

	this->bankerCard[index] = num;
}

int Poker::getMoney()
{
	//cout << "\nuse getMoney";

	return money;
}

void Poker::setMoney(int money)
{
	//cout << "\nuse setMoney";

	this->money = money;
}

int Poker::getBet()
{
	//cout << "\nuse getBet";

	return bet;
}

void Poker::setBet(int bet)
{
	//cout << "\nuse setBet";
	if (bet <= money && bet > 0)
		this->bet = bet;
	else if (bet < 1)
		this->bet = 1;
	else if (bet > money)
		this->bet = money;

}

int Poker::getCardNum()
{
	//cout << "\nuse getCardNum";

	return cardNum;
}

void Poker::setCardNum(int cardNum)
{
	//cout << "\nuse setCardNum";

	this->cardNum = cardNum;
}



void Poker::setSrand()//設定亂數種子 
{
	//cout << "\nuse setSrand";

	srand(time(0));
}

void Poker::setDefaultDeck()//初始化牌組 
{
	//cout << "\nuse setDefaultDeck";

	for (int i = 0; i < 52; i++) {
		deck[i] = i;
	}
}



void Poker::shuffle()//洗牌 
{
	//cout << "\nuse shuffle";

	setCardNum(0);

	int temp, r;

	for (int i = 0; i < 52; i++) {
		r = (rand() % 52);
		temp = deck[i];
		deck[i] = deck[r];
		deck[r] = temp;
	}
}

void Poker::printPoint(int num)//印出點數(J,Q,K等 
{
	//cout << "\nuse printPoint";

	switch (num % 13) {
	case  0:cout << setw(2) << 'A'; break;
	case 10:cout << setw(2) << 'J'; break;
	case 11:cout << setw(2) << 'Q'; break;
	case 12:cout << setw(2) << 'K'; break;
	default:cout << setw(2) << num % 13 + 1;
	}
}

void Poker::printSuit(int num)//印出花色(紅心，方塊等 
{
	//cout << "\nuse printSuit";

	switch (num / 13) {
	case 0:cout << "黑桃"; break;
	case 1:cout << "愛心"; break;
	case 2:cout << "方塊"; break;
	case 3:cout << "梅花";
	}
}

void Poker::printPlayerCard()//印出玩家手牌 
{
	//cout << "\nuse printPlayerCard \n";

	cout << "\n玩家手牌: \n";
	int i = 0;
	while (playerCard[i] != -1) {
		printSuit(playerCard[i]);
		printPoint(playerCard[i]);
		cout << "  ";
		i++;
	}
}

void Poker::printBankerCard()//印出莊家手牌 
{
	//cout << "\nuse printBankerCard \n";

	cout << "\n莊家手牌: \n";
	int i = 0;
	while (bankerCard[i] != -1) {
		printSuit(bankerCard[i]);
		printPoint(bankerCard[i]);
		cout << "  ";
		i++;
	}
}


int Poker::getNumOfCard(int list[])//取得手牌張數 
{
	//cout << "\nuse getNumOfCard";

	int i = 0;
	while (list[i] != -1)
		i++;
	return i;
}

void Poker::checkFiveCardCharlie()//判斷玩家手牌數是否為5 
{
	//cout << "\nuse fiveCardCharlie";

	if (getNumOfCard(playerCard) == 5) {
		cout << "\nfive card Charlie!!!3xBonus\nYou win " << bet * 3 << "\nNow your money is " << (money += bet * 3);
		newGame();
	}
	
}

int Poker::getPoint(int list[])//取得手牌得點 
{
	//cout << "\nuse getPoint";

	int point = 0, times = getNumOfCard(list);
	bool A = false;
	for (int i = 0; i < times; i++) {
		switch (list[i] % 13) {
		case  0:point += 1; A = true; break;
		case 10:
		case 11:
		case 12:point += 10; break;
		default:point += (list[i] % 13 + 1);
		}
	}
	if (A == true && point <= 11)
		return point + 10;
	else
		return point;
}

void Poker::checkBust()//判斷玩家得點是否超過21 
{
	//cout << "\nuse checkBust :" << getPoint(playerCard);
	//printPlayerCard();

	if (getPoint(playerCard) >= 21)
		stopAsk();
}



void Poker::playerAsk()//玩家要牌 
{
	//cout << "\nuse playerAsk";

	setPlayerCard(deck[cardNum++], getNumOfCard(playerCard));
	checkBust();
	checkFiveCardCharlie();
}

void Poker::stopAsk()//玩家停止要牌 
{
	//cout << "\nuse stopAsk";

	bankerAsk();

	if (getPoint(playerCard) >= 21 || getPoint(bankerCard) >= 21) {
		if (getPoint(playerCard) > 21) {
			printPlayerCard();
			cout << "\nyour point: " << getPoint(playerCard);
		}
		else {
			printPlayerCard();
			cout << "\nyour point: " << getPoint(playerCard);
			printBankerCard();
		}

		bustEnd();
	}
	else {
		printPlayerCard();
		cout << "\nyour point: " << getPoint(playerCard);
		printBankerCard();

		notBustEnd();
	}
}

void Poker::bankerAsk()//莊家要牌 
{
	//cout << "\nuse bankerAsk";

	setBankerCard(deck[cardNum++], getNumOfCard(bankerCard));
	BankerPointCheck();
}

void Poker::BankerPointCheck()//檢查莊家點數是否大於17 
{
	//cout << "\nuse BankerPointCheck :" << getPoint(bankerCard);
	//printBankerCard();

	if (getPoint(bankerCard) < 17)
		bankerAsk();
}


void Poker::bustEnd()//有人得點大於21的遊戲結果 
{
	//cout << "\nuse bustEnd";

	int pp = getPoint(playerCard);
	int bp = getPoint(bankerCard);

	if (pp ==21&& bp== 21) {
		cout << "\nDraw\nNow your money is " << money;
	}
	else if (pp == 21) {
		if (getNumOfCard(playerCard) == 2)
			cout << "\nBlack Jack!!!1.5xBonus\nYou win " << bet * 3 / 2 << "\nNow your money is " << (money += bet * 3 / 2);
		else
			cout << "\nWin\nYou win " << bet << "\nNow your money is " << (money += bet);
	}
	else if (bp > 21 && pp < 21) {
		cout << "\nWin\nyou win " << bet << "\nNow your money is " << (money += bet);
	}
	else {
		cout << "\nLose\nYou lose " << bet << "\nNow your money is " << (money -= bet);
	}

	newGame();
}

void Poker::notBustEnd()//沒人得點大於21的遊戲結果 
{
	//cout << "\nuse notBustEnd";

	int pp = getPoint(playerCard);
	int bp = getPoint(bankerCard);

	if (pp > bp) {
		cout << "\nWin\nYou win " << bet << "\nNow your money is " << (money += bet);
	}
	else if (pp == bp) {
		cout << "\nDraw\nNow your money is " << money;
	}
	else {
		cout << "\nLose\nYou lose " << bet << "\nNow your money is " << (money -= bet);
	}
	newGame();
}



void Poker::choice()//選擇抽牌or停止抽牌or重新開始or結束遊戲 
{
	//cout << "\nuse choice";

	int choice = 1;

	while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5) {
		
		if (choice != 5) {
			cout << "\nMoney:" << getMoney() << "\tBet:" << getBet();
			printPlayerCard();
			cout << "\nYour point: " << getPoint(playerCard);
			printBankerCard();
		}
		cout << "\n請輸入1 以抽牌 ,2 以停止抽牌 ,3 以重新開始 ,4 以結束遊戲\n";
		cin >> choice;

		switch (choice) {
		case 1:playerAsk(); break;
		case 2:stopAsk(); break;
		case 3:newGame(); break;
		case 4:exit(0); break;
		default:cout << "\n請重新輸入"; choice = 5;
		}
	}
}

void Poker::newGame()//開啟新遊戲 
{
	//cout << "\nuse newGame";

	if (money <= 0) {
		cout << "\nYou don't have money";
		exit(0);
	}

	shuffle();
	
	cout << "\nMoney:" << getMoney() << "\nSet your bet\n";
	int b;
	cin >> b;
	setBet(b);

	for (int i = 0; i < 6; i++) {
		setPlayerCard(-1, i);
		setBankerCard(-1, i);
	}
	setPlayerCard(deck[cardNum++], 0);
	setPlayerCard(deck[cardNum++], 1);
	setBankerCard(deck[cardNum++], 0);

	checkBust();
}