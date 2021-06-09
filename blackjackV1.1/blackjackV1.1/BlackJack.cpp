#include "BlackJack.h"

void BlackJack::peek() {//儲存之數字
	for (int index = 0; index < 6; index++)
		cout << dealer[index] << ' ';
	cout << endl;
	for (int num = 0; num < playerNum; num++) {
		for (int index = 0; index < 6; index++)
			cout << player[num].hand[index] << ' ';
		cout << endl;
	}
}
void BlackJack::peek2() {//轉換為得點
	for (int index = 0; index < 6; index++)
		cout <<setw(2)<< getPoint(dealer[index]) << ' ';
	cout <<getPoint(dealer)<< endl;
	for (int num = 0; num < playerNum; num++) {
		for (int index = 0; index < 6; index++)
			cout << setw(2)<< getPoint(player[num].hand[index]) << ' ';
		cout <<getPoint(player[num].hand)<< endl;
		if (player[num].isSplit) {
			cout << "split\n";
			for (int index = 0; index < 6; index++)
				cout << setw(2) << getPoint(player[num].split[index]) << ' ';
			cout << getPoint(player[num].split) << endl;
		}
	}
}
void BlackJack::peek3() {//特殊動作
	for (int num = 0; num < playerNum; num++) {
		cout << "player" << num<<": ";
		cout <<"21點"<< player[num].isBlackjack;
		cout <<"保險"<< player[num].isInsurance;
		cout <<"分牌"<< player[num].isSplit;
		cout <<"加注"<< player[num].isDouble;
		cout <<"投降"<< player[num].isSurrender;
		if (player[num].isSplit)
			cout << "分牌加注" << player[num].isSplitDouble;
		cout << endl;
	}
}
BlackJack::BlackJack() {
	cout << "\n[1]單人遊玩 [2]加入AI [3]結束遊戲";
	int choice = 3;
	while (choice == 3) {
		cin >> choice;
		switch (choice) {
		case 1:setPlayerNum(1); break;
		case 2:setPlayerNum(); break;
		case 3:exit(0); break;
		default:cout << "\n請重新輸入:"; choice = 3;
		}
	}
	if (playerNum == 1) {
		deck = new int[52];
		for (int i = 0; i < 52; i++)
			deck[i] = i;
	}
	else {
		deck = new int[52 * (playerNum / 2)];
		for (int i = 0; i < 52 * (playerNum / 2); i++)
			deck[i] = i;
	}
	player = new Gambler[playerNum];
	srand(time(0));

	//default
	askTimes = 0;
	int temp, r;
	if (playerNum == 1)
		for (int i = 0; i < 52; i++) {
			r = rand() % 52;
			temp = deck[i];
			deck[i] = deck[r];
			deck[r] = temp;
		}
	else
		for (int i = 0; i < 52 * (playerNum / 2); i++) {
			r = rand() % 52 * (playerNum / 2);
			temp = deck[i];
			deck[i] = deck[r];
			deck[r] = temp;
		}
	for (int i = 0; i < playerNum; i++)
		player[i].money = 200;

	//new
	for (int index = 0; index < 6; index++)
		dealer[index] = -1;
	dealerHandNum = 0;
	for (int num = 0; num < playerNum; num++) {
		player[num].handNum = 0;
		player[num].isBlackjack = false;
		player[num].isInsurance= false;
		player[num].isSplit= false;
		player[num].isDouble= false;
		player[num].isSurrender = false;
		player[num].isStand = false;

		for (int index = 0; index < 6; index++)
			player[num].hand[index] = -1;
	}
	dealer[dealerHandNum++] = 0;
	dealer[dealerHandNum++] = 6;

	for (int i = 0; i < 2; i++) {
		//askCard();
		for (int i = 0; i < playerNum; i++)
			askCard(i);
	}

	for (int i = 1; i < playerNum; i++) {
		player[i].bet = rand() % 41 + 10;
		player[i].isBlackjack = false;
	}
	peek();
	peek2();
	//printStatus();
	//AI行動

	for (int i = 1; i < playerNum; i++) {
		if (getPoint(player[i].hand) == 21)//21點
			player[i].isBlackjack = true;
		else {
			if (dealer[0] % 13 == 0 && rand()) {//保險
				if (rand() % 10 == 9) {
					player[i].isInsurance = true;
				}
			}
			if (getPoint(player[i].hand[0]) == getPoint(player[i].hand[1])) {//分牌
				if (rand() % 10 > 5) {
					player[i].isSplit = true;
				}
			}
			if (getPoint(player[i].hand) == 10 || getPoint(player[i].hand) == 11) {//加注
				if (rand() % 10 > 3) {
					player[i].isDouble = true;
				}
			}
			if (getPoint(player[i].hand) >= 12 && getPoint(player[i].hand) <= 16 && getPoint(dealer[0]) >= 7) {//投降
				if (rand() % 10 > 4) {
					player[i].isSurrender = true;
				}
			}
		}
	}
	for (int i = 1; i < playerNum; i++) {
		if (player[i].isSplit) {
			player[i].isDouble = false;
			player[i].isSplitDouble = false;
			player[i].split = new int[6];
			for (int index = 0; index < 6; index++) {
				player[i].split[index] = -1;
			}
			player[i].splitNum = 1;
			player[i].handNum = 1;
			player[i].split[0] = player[i].hand[0];
			askCard(i);
			player[i].split[player[i].splitNum++] = deck[askTimes++];
			if (getPoint(player[i].hand) == 10 || getPoint(player[i].hand) == 11) {//加注
				if (rand() % 10 > 3) {
					player[i].isDouble = true;
				}
			}
			if (getPoint(player[i].hand) == 10 || getPoint(player[i].hand) == 11) {//分牌加注
				if (rand() % 10 > 3) {
					player[i].isSplitDouble = true;
				}
			}
		}
	}
	peek3();
	peek2();
	for (int i = 1; i < playerNum; i++) {
		if (player[i].isSplit) {
			if (player[i].isInsurance) {
				if (getPoint(dealer) == 21) {
					cout << "\nplayer" << i << "保險 贏了" << player[i].bet;
					player[i].money += player[i].bet;
				}
				else {
					cout << "\nplayer" << i << "保險 輸了" << player[i].bet/2;
					player[i].money -= player[i].bet/2;
				}
			}
			if (player[i].isDouble) {
				cout << "\nplayer" << i << "加注";
				askCard(i);

				player[i].isStand = true;
			}
			if (player[i].isSplitDouble) {
				cout << "\nplayer" << i << "加注(分牌)";
				askCard(i);
				player[i].isStand = true;
			}
		}
		else {
			if (player[i].isInsurance) {
				if (getPoint(dealer) == 21) {
					cout << "player" << i << "保險 贏了" << player[i].bet;
					player[i].money += player[i].bet;
				}
				else {
					cout << "player" << i << "保險 輸了" << player[i].bet / 2;
					player[i].money -= player[i].bet / 2;
				}
			}
			if (player[i].isDouble)
				;
		}
	}

	cout <<endl<< getPoint(dealer) << endl;
	for (int i = 1; i < playerNum; i++) {
		cout << player[i].money << ' ' << player[i].bet << endl;
	}
}
void BlackJack::setPlayerNum() {
	cout << "\n要與幾個AI共同遊玩,最多7個:";
	int playerNum;
	cin >> playerNum;
	if (playerNum < 0)
		this->playerNum = 1;
	else if(playerNum>7)
		this->playerNum = 8;
	else
		this->playerNum = playerNum+1;

}
void BlackJack::setPlayerNum(int playerNum) {
	this->playerNum = playerNum;
}
int  BlackJack::getPoint(int hand[])//取得手牌得點
{
	//cout << "\nuse getPoint";

	int point = 0;
	bool A = false;
	for (int i = 0; hand[i] != -1; i++) {
		switch (hand[i] % 13) {
		case  0:point += 1; A = true; break;
		case 10:
		case 11:
		case 12:point += 10; break;
		default:point += (hand[i] % 13 + 1);
		}
	}
	if (A == true && point <= 11)
		return point + 10;
	else
		return point;
}
int  BlackJack::getPoint(int num)//取得指定牌的得點
{
	//cout << "\nuse getPoint";

	switch (num % 13) {
	case  0:return 1;
	case 10:
	case 11:
	case 12:return 10;
	default:return (num % 13 + 1);
	}
}
void BlackJack::askCard() {
	dealer[dealerHandNum++] = deck[askTimes++];
}
void BlackJack::askCard(int i) {
	player[i].hand[player[i].handNum++] = deck[askTimes++];
}