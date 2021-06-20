#include "BlackJack.h"

void BlackJack::peek() {//�x�s���Ʀr
	cout << " dealer ";
	for (int index = 0; index < 6; index++)
		cout << dealer[index] << ' ';
	cout << endl;
	for (int num = 0; num < playerNum; num++) {
		cout << "player" << num << ' ';
		for (int index = 0; index < 6; index++)
			cout << player[num].hand[index] << ' ';
		cout << endl;
	}
}
void BlackJack::peek2() {//�ഫ���o�I
	cout << " dealer ";
	for (int index = 0; index < 6; index++)
		cout << setw(2) << getPoint(dealer[index]) << ' ';
	cout << getPoint(dealer) << endl;
	for (int num = 0; num < playerNum; num++) {
		cout << "player" << num << ' ';
		for (int index = 0; index < 6; index++)
			cout << setw(2) << getPoint(player[num].hand[index]) << ' ';
		cout << getPoint(player[num].hand) << endl;
		if (player[num].isSplit) {
			cout << "split\n";
			for (int index = 0; index < 6; index++)
				cout << setw(2) << getPoint(player[num].split[index]) << ' ';
			cout << getPoint(player[num].split) << endl;
		}
	}
}
void BlackJack::peek3() {//�S��ʧ@
	for (int num = 0; num < playerNum; num++) {
		cout << "player" << num << ": ";
		cout << "21�I" << player[num].isBlackjack;
		cout << "�O�I" << player[num].isInsurance;
		cout << "���P" << player[num].isSplit;
		cout << "�[�`" << player[num].isDouble;
		cout << "�뭰" << player[num].isSurrender;
		if (player[num].isSplit)
			cout << "���P�[�`" << player[num].isSplitDouble;
		cout << endl;
	}
}
BlackJack::BlackJack() {
	cout << R"(
88888888ba  88                       88               88                       88         
88      "8b 88                       88               88                       88         
88      ,8P 88                       88               88                       88         
88aaaaaa8P' 88 ,adPPYYba,  ,adPPYba, 88   ,d8         88 ,adPPYYba,  ,adPPYba, 88   ,d8   
88""""""8b, 88 ""     `Y8 a8"     "" 88 ,a8"          88 ""     `Y8 a8"     "" 88 ,a8"    
88      `8b 88 ,adPPPPP88 8b         8888[            88 ,adPPPPP88 8b         8888[      
88      a8P 88 88,    ,88 "8a,   ,aa 88`"Yba, 88,   ,d88 88,    ,88 "8a,   ,aa 88`"Yba,   
88888888P"  88 `"8bbdP"Y8  `"Ybbd8"' 88   `Y8a "Y8888P"  `"8bbdP"Y8  `"Ybbd8"' 88   `Y8a  
)";

	cout << "\n[1]��H�C�� [2]�[�JAI [3]�����C�� ";
	int choice = 3;
	while (choice == 3) {
		cin >> choice;
		switch (choice) {
		case 1:setPlayerNum(1); break;
		case 2:setPlayerNum(); break;
		case 3:exit(0); break;
		default:cout << "\n�Э��s��J:"; choice = 3;
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
	std::srand(time(0));

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
	process();
	while (1) {
		if (player[0].money < 10) {
			cout << "\n�S�����F\n[1]���ܬ�200��U�@�� [2]���� ";
			player[0].money = 200;
		}
		else {
			cout << "\n[1]�U�@�� [2]���� ";
		}
		cin >> choice;
		switch (choice) {
		case 1:process(); break;
		case 2:exit(0); break;
		default:cout << "\n�Э��s��J:"; choice = 1;
		}
	}
}
void BlackJack::setPlayerNum() {
	cout << "\n�n�P�X��AI�@�P�C��,�̦h7��:";
	int playerNum;
	cin >> playerNum;
	this->playerNum = (playerNum < 0) ? 1 : (playerNum > 7) ? 8 : playerNum + 1;
}
void BlackJack::setPlayerNum(int playerNum) {
	this->playerNum = playerNum;
}
int  BlackJack::getPoint(int hand[])//���o��P�o�I
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
	return(A == true && point <= 11) ? point + 10 : point;
}
int  BlackJack::getPoint(int num)//���o���w�P���o�I
{
	//cout << "\nuse getPoint";

	switch (num % 13) {
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
void BlackJack::splitAsk(int i) {
	player[i].split[player[i].splitNum++] = deck[askTimes++];
}
void BlackJack::printDealer() {
	cout << "\n\n���a��P:";
	for (int i = 0; i < 1; i++) {
		printSuit(dealer[i]);
		printPoint(dealer[i]);
		cout << "  ";
	}
	for (int i = 0; i < playerNum; i++) {
		printStatus(i);
	}
	cout << endl;
}
void BlackJack::printStatus() {
	cout << endl;
	printStatus(dealer);
	for (int i = 0; i < playerNum; i++) {
		printStatus(i);
	}
	cout << endl;
}
void BlackJack::printStatus(int num[]) {
	cout << "\n���a��P:";
	for (int i = 0; i < dealerHandNum; i++) {
		printSuit(dealer[i]);
		printPoint(dealer[i]);
		cout << "  ";
	}
}
void BlackJack::printStatus(int num) {
	if (num == 0) {
		cout << "\n�A����P:";
	}
	else {
		cout << "\nplayer" << num << "��P:";
	}
	for (int i = 0; i < player[num].handNum; i++) {
		printSuit(player[num].hand[i]);
		printPoint(player[num].hand[i]);
		cout << "  ";
	}
	if (player[num].isSplit) {
		printSplitStatus(num);
	}
}
void BlackJack::printSplitStatus(int num) {
	if (num == 0) {
		cout << "\n���P:";
	}
	else {
		cout << "\nplayer" << num << "���P:";
	}
	for (int i = 0; i < player[num].splitNum; i++) {
		printSuit(player[num].split[i]);
		printPoint(player[num].split[i]);
		cout << "  ";
	}
}
void BlackJack::printSuit(int num)//�L�X���(���ߡA����� 
{
	switch (num % 52 / 13) {
	case 0:cout << "�®�"; break;
	case 1:cout << "�R��"; break;
	case 2:cout << "���"; break;
	case 3:cout << "����";
	}
}
void BlackJack::printPoint(int num)//�L�X�I��(J,Q,K�� 
{
	switch (num % 13) {
	case  0:cout << setw(2) << 'A'; break;
	case 10:cout << setw(2) << 'J'; break;
	case 11:cout << setw(2) << 'Q'; break;
	case 12:cout << setw(2) << 'K'; break;
	default:cout << setw(2) << num % 13 + 1;
	}
}
void BlackJack::process() {
	int choice;
	for (int index = 0; index < 6; index++)
		dealer[index] = -1;
	dealerHandNum = 0;
	for (int num = 0; num < playerNum; num++) {
		player[num].handNum = 0;
		player[num].isBlackjack = false;
		player[num].isInsurance = false;
		player[num].isSplit = false;
		player[num].isDouble = false;
		player[num].isSurrender = false;
		player[num].isStand = false;

		for (int index = 0; index < 6; index++)
			player[num].hand[index] = -1;
	}
	//dealer[dealerHandNum++] = 0;
	//dealer[dealerHandNum++] = 6;

	for (int i = 0; i < 2; i++) {
		askCard();
		for (int i = 0; i < playerNum; i++)
			askCard(i);
	}
	for (int i = 1; i < playerNum; i++) {
		if (player[i].money > 50) {
			player[i].bet = rand() % 41 + 10;
			player[i].bet = 200;
		}
		else if (player[i].money < 10) {
			cout << "\nplayer" << i << "�S���F,�ӤF�s�����a";
			player[i].money = 200;
			player[i].bet = rand() % 41 + 10;
		}
		else {
			player[i].bet = rand() % (player[i].money - 9) + 10;
		}
	}

	int bet;
	cout << "\n��:"<<player[0].money<<"\n�ФU�`,�̤�10��:";
	cin >> bet;
	player[0].bet = (bet < 10) ? 10 : (bet > player[0].money) ? player[0].money : bet;

	cout << "\n�n�B�~�U�`��l��";
	cout << "\n[-1]���n [0]�ۤv ";
	for (int i = 1; i < playerNum; i++) {
		cout << '[' << i << ']' << "player" << i << ' ';
	}
	cin >> choice;
	while (choice != -1) {
		if (!(choice >= 0 && choice < playerNum)) {
			cout << "\n���a���s�b,�Э��s��J:";
			choice = 1;
		}
		else break;
		cin >> choice;
	}

	if (choice != -1) {
		cout << "\n���B,�̤�10��:";
		cin >> bet;
		bet = (bet < 10) ? 10 : (bet > player[0].money - player[0].bet) ? player[0].money - player[0].bet : bet;
	}

	printDealer();
	//peek();
	//peek2();
	if (choice != -1) {
		if (player[choice].hand[0] % 13 == player[choice].hand[1] % 13) {
			cout << "\nĹ�F" << bet * 11;
			player[0].money += bet * 11;
		}
		else {
			cout << "\n��F" << bet;
			player[0].money -= bet;
		}
	}
	for (int i = 1; i < playerNum; i++) {
		if (rand() % 11 == 10 && player[i].money - player[i].bet > 50) {
			int target = rand() % playerNum;
			int bet = rand() % 41 + 10;
			if (player[target].hand[0] % 13 == player[target].hand[1] % 13) {
				player[i].money += bet * 11;
				cout << "\nplayer" << i << "�U�`��l(player" << target << "),Ĺ�F" << bet * 11;
			}
			else {
				player[i].money -= bet;
				cout << "\nplayer" << i << "�U�`��l(player" << target << "),��F" << bet;
			}
		}
	}
	cout << '\n';
	//���a���


	if (getPoint(player[0].hand) == 21) {//21�I
		player[0].isBlackjack = true;
		player[0].isStand = true;
	}
	else {
		choice = 0;
		while (choice != 6) {
			cout << "\n[1]�n�P [2]���P ";
			cout << ((dealer[0] % 13 == 0 && player[0].money - player[0].bet >= player[0].bet / 2) ? ((!player[0].isInsurance) ? "[3]�O�I " : "[o]�O�I") : "[x]�O�I "); //�O�I
			cout << ((getPoint(player[0].hand[0]) == getPoint(player[0].hand[1]) && player[0].money - player[0].bet >= player[0].bet) ? "[4]���P " : "[x]���P "); //���P
			cout << ((player[0].money - player[0].bet >= player[0].bet) ? "[5]�[�` " : "[x]�[�` ");//�[�`
			cout << "[6]�뭰 ";
			cin >> choice;

			switch (choice) {
			case 1:askCard(0); choice = 6; printStatus(0); break;
			case 2:player[0].isStand = true; choice = 6; break;
			case 3:
				if (dealer[0] % 13 == 0 && player[0].money - player[0].bet >= player[0].bet / 2) {
					player[0].isInsurance = (!player[0].isInsurance) ? true : false;
				}
				else {
					cout << "\n�{�b����O�I";
				}
				break;
			case 4:
				if (getPoint(player[0].hand[0]) == getPoint(player[0].hand[1]) && player[0].money - player[0].bet >= player[0].bet) {
					player[0].isSplit = true;
					choice = 6;
				}
				else {
					cout << "\n�{�b������P";
				}
				break;
			case 5:
				if (player[0].money - player[0].bet >= player[0].bet) {
					player[0].isDouble = true;
					askCard(0); printStatus(0);
					player[0].bet *= 2;
					player[0].isStand = true;
					choice = 6;
				}
				else {
					cout << "\n�{�b����[�`";
				}
				break;
			case 6:player[0].isSurrender = true; player[0].isStand = true; choice = 6; player[0].money -= player[0].bet / 2; break;
			default:cout << "\n�Э��s��J:";
			}
		}
	}
	if (player[0].isInsurance) {
		if (getPoint(dealer) == 21) {
			cout << "\n�O�I Ĺ�F" << player[0].bet;
			player[0].money += player[0].bet;
		}
		else {
			cout << "\n�O�I ��F" << player[0].bet / 2;
			player[0].money -= player[0].bet / 2;
		}
	}
	if (player[0].isSplit) {
		player[0].isDouble = false;
		player[0].isSplitDouble = false;
		player[0].isSplitStand = false;
		player[0].splitBet = player[0].bet;
		player[0].split = new int[6];
		for (int index = 0; index < 6; index++) {
			player[0].split[index] = -1;
		}
		player[0].splitNum = 1;
		player[0].handNum = 1;
		player[0].split[0] = player[0].hand[0];
		askCard(0); printStatus(0);
		splitAsk(0); printSplitStatus(0);
	}
	if (player[0].isStand);
	else if (player[0].isSplit) {
		while (!player[0].isStand && getPoint(player[0].hand) < 21 && player[0].handNum < 5) {
			cout << "\n[1]�n�P [2]���P ";
			cout << ((player[0].handNum > 2) ? "" : ((player[0].money - player[0].bet >= player[0].bet) ? "[3]�[�` " : "[x]�[�` "));//�[�`
			cin >> choice;
			switch (choice) {
			case 1:askCard(0); printStatus(0); break;
			case 2:player[0].isStand = true; break;
			case 3:
				if (player[0].handNum > 2) {
					cout << "\n�Э��s��J:";
				}
				else if (player[0].money - player[0].bet >= player[0].bet) {
					player[0].isDouble = true;
					askCard(0); printStatus(0);
					player[0].bet *= 2;
					player[0].isStand = true;
				}
				else {
					cout << "\n�{�b����[�`";
				}
				break;
			default:cout << "\n�Э��s��J:";
			}
		}
		while (!player[0].isSplitStand && getPoint(player[0].split) < 21 && player[0].splitNum < 5) {
			cout << "\n[1]���P�n�P [2]���P���P ";
			cout << ((player[0].splitNum > 2) ? "" : ((player[0].money - player[0].bet >= player[0].bet) ? "[3]���P�[�` " : "[x]���P�[�` "));//�[�`
			cin >> choice;
			switch (choice) {
			case 1:splitAsk(0); printSplitStatus(0); break;
			case 2:player[0].isSplitStand = true; break;
			case 3:
				if (player[0].splitNum > 2) {
					cout << "\n�Э��s��J:";
				}
				else if (player[0].money - player[0].bet >= player[0].bet) {
					player[0].isSplitDouble = true;
					askCard(0); printStatus(0);
					player[0].splitBet *= 2;
					player[0].isSplitStand = true;
				}
				else {
					cout << "\n�{�b����[�`";
				}
				break;
			default:cout << "\n�Э��s��J:";
			}
		}
	}
	else {
		while (!player[0].isStand && getPoint(player[0].hand) < 21 && player[0].handNum < 5) {
			cout << "\n[1]�n�P [2]���P ";
			cin >> choice;
			switch (choice) {
			case 1:askCard(0); printStatus(0); break;
			case 2:player[0].isStand = true; break;
			default:cout << "\n�Э��s��J:";
			}
		}
	}

	//AI���
	for (int i = 1; i < playerNum; i++) {
		if (getPoint(player[i].hand) == 21) {//21�I
			player[i].isBlackjack = true;
			player[i].isStand = true;
		}
		else {
			if (dealer[0] % 13 == 0 && player[i].money - player[i].bet >= player[i].bet / 2) {//�O�I
				if (rand() % 10 == 9) {
					player[i].isInsurance = true;
				}
			}
			if (getPoint(player[i].hand[0]) == getPoint(player[i].hand[1]) && player[i].money - player[i].bet >= player[i].bet) {//���P
				if (rand() % 10 > 5) {
					player[i].isSplit = true;
				}
			}
			if (getPoint(player[i].hand) == 10 || getPoint(player[i].hand) == 11 && player[i].money - player[i].bet >= player[i].bet) {//�[�`
				if (rand() % 10 > 3) {
					player[i].isDouble = true;
				}
			}
			if (getPoint(player[i].hand) >= 12 && getPoint(player[i].hand) <= 16 && getPoint(dealer[0]) >= 7) {//�뭰
				if (rand() % 10 > 6 && player[i].isDouble + player[i].isSplit + player[i].isInsurance == 0) {
					player[i].isSurrender = true;
				}
			}
		}
	}
	for (int i = 1; i < playerNum; i++) {//���P
		if (player[i].isSplit) {
			player[i].isDouble = false;
			player[i].isSplitDouble = false;
			player[i].isSplitStand = false;
			player[i].splitBet = player[i].bet;
			player[i].split = new int[6];
			for (int index = 0; index < 6; index++) {
				player[i].split[index] = -1;
			}
			player[i].splitNum = 1;
			player[i].handNum = 1;
			player[i].split[0] = player[i].hand[0];
			askCard(i);
			splitAsk(i);
			if (getPoint(player[i].hand) == 10 || getPoint(player[i].hand) == 11 && player[i].money - player[i].bet >= player[i].bet) {//�[�`
				if (rand() % 10 > 3) {
					player[i].isDouble = true;
				}
			}
			if (getPoint(player[i].hand) == 10 || getPoint(player[i].hand) == 11 && player[i].money - player[i].bet >= player[i].bet) {//���P�[�`
				if (rand() % 10 > 3) {
					player[i].isSplitDouble = true;
				}
			}
		}
	}
	//peek3();
	//peek2();
	for (int i = 1; i < playerNum; i++) {
		if (player[i].isSplit) {
			cout << "\nplayer" << i << "���P";
			if (player[i].isInsurance) {
				if (getPoint(dealer) == 21) {
					cout << "\nplayer" << i << "�O�I Ĺ�F" << player[i].bet;
					player[i].money += player[i].bet;
				}
				else {
					cout << "\nplayer" << i << "�O�I ��F" << player[i].bet / 2;
					player[i].money -= player[i].bet / 2;
				}
			}
			if (player[i].isDouble) {
				cout << "\nplayer" << i << "�[�`";
				askCard(i);
				player[i].bet *= 2;
				player[i].isStand = true;
			}
			if (player[i].isSplitDouble) {
				cout << "\nplayer" << i << "�[�`(���P)";
				splitAsk(i);
				player[i].splitBet *= 2;
				player[i].isSplitStand = true;
			}
		}
		else {
			if (player[i].isInsurance) {
				if (getPoint(dealer) == 21) {
					cout << "\nplayer" << i << "�O�I Ĺ�F" << player[i].bet;
					player[i].money += player[i].bet;
				}
				else {
					cout << "\nplayer" << i << "�O�I ��F" << player[i].bet / 2;
					player[i].money -= player[i].bet / 2;
				}
			}
			if (player[i].isDouble) {
				cout << "\nplayer" << i << "�[�`";
				askCard(i);
				player[i].bet *= 2;
				player[i].isStand = true;
			}
			if (player[i].isSurrender) {
				cout << "\nplayer" << i << "�뭰";
				player[i].money -= player[i].bet / 2;
				player[i].isStand = true;
			}
		}
	}
	while (getPoint(dealer) < 17) {
		askCard();
	}

	for (int i = 1; i < playerNum; i++) {//��P
		if (player[i].isSplit) {
			while (!player[i].isStand) {
				if (getPoint(player[i].hand) >= 20) {
					player[i].isStand = true;
				}
				else if (getPoint(player[i].hand) == 12 && getPoint(dealer[0]) == 2 || getPoint(dealer[0]) == 3) {
					askCard(i);
				}
				else if (getPoint(player[i].hand) <= 11) {
					askCard(i);
				}
				else if (getPoint(player[i].hand) >= 17 && getPoint(dealer[0]) <= 7) {
					player[i].isStand = true;
				}
				else if (getPoint(player[i].hand) >= 17) {
					if (rand() % 10 > 4) {
						player[i].isStand = true;
					}
				}
				else {
					if (dealer[0] == 6 || dealer[0] == 5) {
						player[i].isStand = true;
					}
					else {
						askCard(i);
					}
				}
			}
			while (!player[i].isSplitStand) {
				if (getPoint(player[i].split) >= 20) {
					player[i].isSplitStand = true;
				}
				else if (getPoint(player[i].split) == 12 && getPoint(dealer[0]) == 2 || getPoint(dealer[0]) == 3) {
					splitAsk(i);
				}
				else if (getPoint(player[i].split) <= 11) {
					splitAsk(i);
				}
				else if (getPoint(player[i].split) >= 17 && getPoint(dealer[0]) <= 7) {
					player[i].isSplitStand = true;
				}
				else if (getPoint(player[i].split) >= 17) {
					if (rand() % 10 > 4) {
						player[i].isSplitStand = true;
					}
				}
				else {
					if (dealer[0] == 6 || dealer[0] == 5) {
						player[i].isSplitStand = true;
					}
					else {
						splitAsk(i);
					}
				}
			}
		}
		else {
			while (!player[i].isStand) {
				if (player[i].handNum == 5) {
					player[i].isStand = true;
				}
				else if (getPoint(player[i].hand) >= 20) {
					player[i].isStand = true;
				}
				else if (getPoint(player[i].hand) == 12 && getPoint(dealer[0]) == 2 || getPoint(dealer[0]) == 3) {
					askCard(i);
				}
				else if (getPoint(player[i].hand) <= 11) {
					askCard(i);
				}
				else if (getPoint(player[i].hand) >= 17 && getPoint(dealer[0]) <= 7) {
					player[i].isStand = true;
				}
				else if (getPoint(player[i].hand) >= 17) {
					if (rand() % 10 > 4) {
						player[i].isStand = true;
					}
				}
				else {
					if (dealer[0] == 6 || dealer[0] == 5) {
						player[i].isStand = true;
					}
					else {
						askCard(i);
					}
				}
			}
		}
	}
	//�p�⵲�G
	printStatus();
	if (getPoint(dealer) >= 21) {
		if (getPoint(dealer) > 21) {//���a�z�P
			if (player[0].isSurrender) {
				cout << "\n�뭰 ��F" << player[0].bet / 2;
			}
			else if (player[0].isSplit) {
				if (getPoint(player[0].hand) <= 21) {
					cout << "\nĹ�F" << player[0].bet;
					player[0].money += player[0].bet;
				}
				else {
					cout << "\n��";
				}
				if (getPoint(player[0].split) <= 21) {
					cout << "\n���PĹ�F" << player[0].splitBet;
					player[0].money += player[0].splitBet;
				}
				else {
					cout << "\n���P��";
				}
			}
			else {
				if (getPoint(player[0].hand) < 21) {
					if (player[0].handNum == 5) {
						cout << "\n���s Ĺ�F" << player[0].bet * 3;
						player[0].money += player[0].bet * 3;
					}
					else {
						cout << "\nĹ�F" << player[0].bet;
						player[0].money += player[0].bet;
					}
				}
				else if (getPoint(player[0].hand) == 21) {
					if (player[0].isBlackjack) {
						cout << "\nblackjack Ĺ�F" << player[0].bet * 3 / 2;
						player[0].money += player[0].bet * 3 / 2;
					}
					else if (player[0].handNum == 5) {
						cout << "\n���s Ĺ�F" << player[0].bet * 3;
						player[0].money += player[0].bet * 3;
					}
					else if (player[0].handNum == 3) {
						sort(player[0].hand, player[0].hand + 3);
						if (player[0].hand[0] % 13 == player[0].hand[1] % 13 && player[0].hand[1] % 13 == player[0].hand[2] % 13) {
							cout << "\n�T���C Ĺ�F" << player[0].bet * 3;
							player[0].money += player[0].bet * 3;
						}
						else if (getPoint(player[0].hand[0]) == 6 && getPoint(player[0].hand[1]) == 7 && getPoint(player[0].hand[2]) == 8) {
							cout << "\n�� Ĺ�F" << player[0].bet * 3;
							player[0].money += player[0].bet * 3;
						}
						else {
							cout << "\nĹ�F" << player[0].bet;
							player[0].money += player[0].bet;
						}
					}
					else {
						cout << "\nĹ�F" << player[0].bet;
						player[0].money += player[0].bet;
					}
				}
				else {
					cout << "\n��";
				}
			}
		}
		else {
			if (dealerHandNum == 2) {//���ablackjack
				if (player[0].isSurrender) {
					cout << "\n�뭰 ��F" << player[0].bet / 2;
				}
				else if (player[0].isSplit) {
					if (getPoint(player[0].hand) == 21) {
						cout << "\n��";
					}
					else {
						cout << "\n��F" << player[0].bet;
						player[0].money -= player[0].bet;
					}
					if (getPoint(player[0].split) == 21) {
						cout << "\n���P��";
					}
					else {
						cout << "\n���P��F" << player[0].splitBet;
						player[0].money -= player[0].splitBet;
					}
				}
				else {
					if (getPoint(player[0].hand) < 21) {
						if (player[0].handNum == 5) {
							cout << "\n���s Ĺ�F" << player[0].bet * 3;
							player[0].money += player[0].bet * 3;
						}
						else {
							cout << "\n��F" << player[0].bet;
							player[0].money -= player[0].bet;
						}
					}
					else if (getPoint(player[0].hand) == 21) {
						if (player[0].isBlackjack) {
							cout << "\nblackjack ��";
						}
						else if (player[0].handNum == 5) {
							cout << "\n���s Ĺ�F" << player[0].bet * 3;
							player[0].money += player[0].bet * 3;
						}
						else if (player[0].handNum == 3) {
							sort(player[0].hand, player[0].hand + 3);
							if (player[0].hand[0] % 13 == player[0].hand[1] % 13 && player[0].hand[1] % 13 == player[0].hand[2] % 13) {
								cout << "\n�T���C Ĺ�F" << player[0].bet * 3;
								player[0].money += player[0].bet * 3;
							}
							else if (getPoint(player[0].hand[0]) == 6 && getPoint(player[0].hand[1]) == 7 && getPoint(player[0].hand[2]) == 8) {
								cout << "\n�� Ĺ�F" << player[0].bet * 3;
								player[0].money += player[0].bet * 3;
							}
							else {
								cout << "\n��";
							}
						}
						else {
							cout << "\n��";
						}
					}
					else {
						cout << "\n��F" << player[0].bet;
						player[0].money -= player[0].bet;
					}
				}
			}
			else {//���a21�I(�Dblackjack)
				if (player[0].isSurrender) {
					cout << "\n�뭰 ��F" << player[0].bet / 2;
				}
				else if (player[0].isSplit) {
					if (getPoint(player[0].hand) == 21) {
						cout << "\n��";
					}
					else {
						cout << "\n��F" << player[0].bet;
						player[0].money -= player[0].bet;
					}
					if (getPoint(player[0].split) == 21) {
						cout << "\n���P��";
					}
					else {
						cout << "\n���P��F" << player[0].splitBet;
						player[0].money -= player[0].splitBet;
					}
				}
				else {
					if (getPoint(player[0].hand) < 21) {
						if (player[0].handNum == 5) {
							cout << "\n���s Ĺ�F" << player[0].bet * 3;
							player[0].money += player[0].bet * 3;
						}
						else {
							cout << "\n��F" << player[0].bet;
							player[0].money -= player[0].bet;
						}
					}
					else if (getPoint(player[0].hand) == 21) {
						if (player[0].isBlackjack) {
							cout << "\nblackjack Ĺ�F" << player[0].bet * 3 / 2;
							player[0].money += player[0].bet * 3 / 2;
						}
						else if (player[0].handNum == 5) {
							cout << "\n���s Ĺ�F" << player[0].bet * 3;
							player[0].money += player[0].bet * 3;
						}
						else if (player[0].handNum == 3) {
							sort(player[0].hand, player[0].hand + 3);
							if (player[0].hand[0] % 13 == player[0].hand[1] % 13 && player[0].hand[1] % 13 == player[0].hand[2] % 13) {
								cout << "\n�T���C Ĺ�F" << player[0].bet * 3;
								player[0].money += player[0].bet * 3;
							}
							else if (getPoint(player[0].hand[0]) == 6 && getPoint(player[0].hand[1]) == 7 && getPoint(player[0].hand[2]) == 8) {
								cout << "\n�� Ĺ�F" << player[0].bet * 3;
								player[0].money += player[0].bet * 3;
							}
							else {
								cout << "\n��";
							}
						}
						else {
							cout << "\n��";
						}
					}
					else {
						cout << "\n��F" << player[0].bet;
						player[0].money -= player[0].bet;
					}
				}
			}
		}
	}
	else {//���a����21�I
		if (player[0].isSurrender) {
			cout << "\n�뭰 ��F" << player[0].bet / 2;
		}
		else if (player[0].isSplit) {
			if (getPoint(player[0].hand) > getPoint(dealer)) {
				cout << "\nĹ�F" << player[0].bet;
				player[0].money += player[0].bet;
			}
			else if (getPoint(player[0].hand) == getPoint(dealer)) {
				cout << "\n��";
			}
			else {
				cout << "\n��F" << player[0].bet;
				player[0].money -= player[0].bet;
			}
			if (getPoint(player[0].split) > getPoint(dealer)) {
				cout << "\n���PĹ�F" << player[0].splitBet;
				player[0].money += player[0].splitBet;
			}
			else if (getPoint(player[0].split) == getPoint(dealer)) {
				cout << "\n���P��";
			}
			else {
				cout << "\n���P��F" << player[0].splitBet;
				player[0].money -= player[0].splitBet;
			}
		}
		else {
			if (getPoint(player[0].hand) < 21) {
				if (player[0].handNum == 5) {
					cout << "\n���s Ĺ�F" << player[0].bet * 3;
					player[0].money += player[0].bet * 3;
				}
				else if (getPoint(player[0].hand) > getPoint(dealer)) {
					cout << "\nĹ�F" << player[0].bet;
					player[0].money += player[0].bet;
				}
				else if (getPoint(player[0].hand) == getPoint(dealer)) {
					cout << "\n��";
				}
				else {
					cout << "\n��F" << player[0].bet;
					player[0].money -= player[0].bet;
				}
			}
			else if (getPoint(player[0].hand) == 21) {
				if (player[0].isBlackjack) {
					cout << "\nblackjack Ĺ�F" << player[0].bet * 3 / 2;
					player[0].money += player[0].bet * 3 / 2;
				}
				else if (player[0].handNum == 5) {
					cout << "\n���s Ĺ�F" << player[0].bet * 3;
					player[0].money += player[0].bet * 3;
				}
				else if (player[0].handNum == 3) {
					sort(player[0].hand, player[0].hand + 3);
					if (player[0].hand[0] % 13 == player[0].hand[1] % 13 && player[0].hand[1] % 13 == player[0].hand[2] % 13) {
						cout << "\n�T���C Ĺ�F" << player[0].bet * 3;
						player[0].money += player[0].bet * 3;
					}
					else if (getPoint(player[0].hand[0]) == 6 && getPoint(player[0].hand[1]) == 7 && getPoint(player[0].hand[2]) == 8) {
						cout << "\n�� Ĺ�F" << player[0].bet * 3;
						player[0].money += player[0].bet * 3;
					}
					else {
						cout << "\nĹ�F" << player[0].bet;
						player[0].money += player[0].bet;
					}
				}
				else {
					cout << "\nĹ�F" << player[0].bet;
					player[0].money += player[0].bet;
				}
			}
			else {
				cout << "\n��F" << player[0].bet;
				player[0].money -= player[0].bet;
			}
		}
	}


	if (getPoint(dealer) >= 21) {
		if (getPoint(dealer) > 21) {//���a�z�P
			for (int i = 1; i < playerNum; i++) {
				if (player[i].isSurrender) {
					cout << "\nplayer" << i << "�뭰 ��F" << player[i].bet / 2;
				}
				else if (player[i].isSplit) {
					if (getPoint(player[i].hand) <= 21) {
						cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
						player[i].money += player[i].bet;
					}
					else {
						cout << "\nplayer" << i << "��";
					}
					if (getPoint(player[i].split) <= 21) {
						cout << "\nplayer" << i << "���PĹ�F" << player[i].splitBet;
						player[i].money += player[i].splitBet;
					}
					else {
						cout << "\nplayer" << i << "���P��";
					}
				}
				else {
					if (getPoint(player[i].hand) < 21) {
						if (player[i].handNum == 5) {
							cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
							player[i].money += player[i].bet * 3;
						}
						else {
							cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
							player[i].money += player[i].bet;
						}
					}
					else if (getPoint(player[i].hand) == 21) {
						if (player[i].isBlackjack) {
							cout << "\nplayer" << i << "blackjack Ĺ�F" << player[i].bet * 3 / 2;
							player[i].money += player[i].bet * 3 / 2;
						}
						else if (player[i].handNum == 5) {
							cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
							player[i].money += player[i].bet * 3;
						}
						else if (player[i].handNum == 3) {
							sort(player[i].hand, player[i].hand + 3);
							if (player[i].hand[0] % 13 == player[i].hand[1] % 13 && player[i].hand[1] % 13 == player[i].hand[2] % 13) {
								cout << "\nplayer" << i << "�T���C Ĺ�F" << player[i].bet * 3;
								player[i].money += player[i].bet * 3;
							}
							else if (getPoint(player[i].hand[0]) == 6 && getPoint(player[i].hand[1]) == 7 && getPoint(player[i].hand[2]) == 8) {
								cout << "\nplayer" << i << "�� Ĺ�F" << player[i].bet * 3;
								player[i].money += player[i].bet * 3;
							}
							else {
								cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
								player[i].money += player[i].bet;
							}
						}
						else {
							cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
							player[i].money += player[i].bet;
						}
					}
					else {
						cout << "\nplayer" << i << "��";
					}
				}
			}
		}
		else {
			if (dealerHandNum == 2) {//���ablackjack
				for (int i = 1; i < playerNum; i++) {
					if (player[i].isSurrender) {
						cout << "\nplayer" << i << "�뭰 ��F" << player[i].bet / 2;
					}
					else if (player[i].isSplit) {
						if (getPoint(player[i].hand) == 21) {
							cout << "\nplayer" << i << "��";
						}
						else {
							cout << "\nplayer" << i << "��F" << player[i].bet;
							player[i].money -= player[i].bet;
						}
						if (getPoint(player[i].split) == 21) {
							cout << "\nplayer" << i << "���P��";
						}
						else {
							cout << "\nplayer" << i << "���P��F" << player[i].splitBet;
							player[i].money -= player[i].splitBet;
						}
					}
					else {
						if (getPoint(player[i].hand) < 21) {
							if (player[i].handNum == 5) {
								cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
								player[i].money += player[i].bet * 3;
							}
							else {
								cout << "\nplayer" << i << "��F" << player[i].bet;
								player[i].money -= player[i].bet;
							}
						}
						else if (getPoint(player[i].hand) == 21) {
							if (player[i].isBlackjack) {
								cout << "\nplayer" << i << "blackjack ��";
							}
							else if (player[i].handNum == 5) {
								cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
								player[i].money += player[i].bet * 3;
							}
							else if (player[i].handNum == 3) {
								sort(player[i].hand, player[i].hand + 3);
								if (player[i].hand[0] % 13 == player[i].hand[1] % 13 && player[i].hand[1] % 13 == player[i].hand[2] % 13) {
									cout << "\nplayer" << i << "�T���C Ĺ�F" << player[i].bet * 3;
									player[i].money += player[i].bet * 3;
								}
								else if (getPoint(player[i].hand[0]) == 6 && getPoint(player[i].hand[1]) == 7 && getPoint(player[i].hand[2]) == 8) {
									cout << "\nplayer" << i << "�� Ĺ�F" << player[i].bet * 3;
									player[i].money += player[i].bet * 3;
								}
								else {
									cout << "\nplayer" << i << "��";
								}
							}
							else {
								cout << "\nplayer" << i << "��";
							}
						}
						else {
							cout << "\nplayer" << i << "��F" << player[i].bet;
							player[i].money -= player[i].bet;
						}
					}
				}
			}
			else {//���a21�I(�Dblackjack)
				for (int i = 1; i < playerNum; i++) {
					if (player[i].isSurrender) {
						cout << "\nplayer" << i << "�뭰 ��F" << player[i].bet / 2;
					}
					else if (player[i].isSplit) {
						if (getPoint(player[i].hand) == 21) {
							cout << "\nplayer" << i << "��";
						}
						else {
							cout << "\nplayer" << i << "��F" << player[i].bet;
							player[i].money -= player[i].bet;
						}
						if (getPoint(player[i].split) == 21) {
							cout << "\nplayer" << i << "���P��";
						}
						else {
							cout << "\nplayer" << i << "���P��F" << player[i].splitBet;
							player[i].money -= player[i].splitBet;
						}
					}
					else {
						if (getPoint(player[i].hand) < 21) {
							if (player[i].handNum == 5) {
								cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
								player[i].money += player[i].bet * 3;
							}
							else {
								cout << "\nplayer" << i << "��F" << player[i].bet;
								player[i].money -= player[i].bet;
							}
						}
						else if (getPoint(player[i].hand) == 21) {
							if (player[i].isBlackjack) {
								cout << "\nplayer" << i << "blackjack Ĺ�F" << player[i].bet * 3 / 2;
								player[i].money += player[i].bet * 3 / 2;
							}
							else if (player[i].handNum == 5) {
								cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
								player[i].money += player[i].bet * 3;
							}
							else if (player[i].handNum == 3) {
								sort(player[i].hand, player[i].hand + 3);
								if (player[i].hand[0] % 13 == player[i].hand[1] % 13 && player[i].hand[1] % 13 == player[i].hand[2] % 13) {
									cout << "\nplayer" << i << "�T���C Ĺ�F" << player[i].bet * 3;
									player[i].money += player[i].bet * 3;
								}
								else if (getPoint(player[i].hand[0]) == 6 && getPoint(player[i].hand[1]) == 7 && getPoint(player[i].hand[2]) == 8) {
									cout << "\nplayer" << i << "�� Ĺ�F" << player[i].bet * 3;
									player[i].money += player[i].bet * 3;
								}
								else {
									cout << "\nplayer" << i << "��";
								}
							}
							else {
								cout << "\nplayer" << i << "��";
							}
						}
						else {
							cout << "\nplayer" << i << "��F" << player[i].bet;
							player[i].money -= player[i].bet;
						}
					}
				}
			}
		}
	}
	else {//���a����21�I
		for (int i = 1; i < playerNum; i++) {
			if (player[i].isSurrender) {
				cout << "\nplayer" << i << "�뭰 ��F" << player[i].bet / 2;
			}
			else if (player[i].isSplit) {
				if (getPoint(player[i].hand) > getPoint(dealer)) {
					cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
					player[i].money += player[i].bet;
				}
				else if (getPoint(player[i].hand) == getPoint(dealer)) {
					cout << "\nplayer" << i << "��";
				}
				else {
					cout << "\nplayer" << i << "��F" << player[i].bet;
					player[i].money -= player[i].bet;
				}
				if (getPoint(player[i].split) > getPoint(dealer)) {
					cout << "\nplayer" << i << "���PĹ�F" << player[i].splitBet;
					player[i].money += player[i].splitBet;
				}
				else if (getPoint(player[i].split) == getPoint(dealer)) {
					cout << "\nplayer" << i << "���P��";
				}
				else {
					cout << "\nplayer" << i << "���P��F" << player[i].splitBet;
					player[i].money -= player[i].splitBet;
				}
			}
			else {
				if (getPoint(player[i].hand) < 21) {
					if (player[i].handNum == 5) {
						cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
						player[i].money += player[i].bet * 3;
					}
					else if (getPoint(player[i].hand) > getPoint(dealer)) {
						cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
						player[i].money += player[i].bet;
					}
					else if (getPoint(player[i].hand) == getPoint(dealer)) {
						cout << "\nplayer" << i << "��";
					}
					else {
						cout << "\nplayer" << i << "��F" << player[i].bet;
						player[i].money -= player[i].bet;
					}
				}
				else if (getPoint(player[i].hand) == 21) {
					if (player[i].isBlackjack) {
						cout << "\nplayer" << i << "blackjack Ĺ�F" << player[i].bet * 3 / 2;
						player[i].money += player[i].bet * 3 / 2;
					}
					else if (player[i].handNum == 5) {
						cout << "\nplayer" << i << "���s Ĺ�F" << player[i].bet * 3;
						player[i].money += player[i].bet * 3;
					}
					else if (player[i].handNum == 3) {
						sort(player[i].hand, player[i].hand + 3);
						if (player[i].hand[0] % 13 == player[i].hand[1] % 13 && player[i].hand[1] % 13 == player[i].hand[2] % 13) {
							cout << "\nplayer" << i << "�T���C Ĺ�F" << player[i].bet * 3;
							player[i].money += player[i].bet * 3;
						}
						else if (getPoint(player[i].hand[0]) == 6 && getPoint(player[i].hand[1]) == 7 && getPoint(player[i].hand[2]) == 8) {
							cout << "\nplayer" << i << "�� Ĺ�F" << player[i].bet * 3;
							player[i].money += player[i].bet * 3;
						}
						else {
							cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
							player[i].money += player[i].bet;
						}
					}
					else {
						cout << "\nplayer" << i << "Ĺ�F" << player[i].bet;
						player[i].money += player[i].bet;
					}
				}
				else {
					cout << "\nplayer" << i << "��F" << player[i].bet;
					player[i].money -= player[i].bet;
				}
			}
		}
	}
	cout << endl;
	//peek2();

	for (int i = 0; i < playerNum; i++) {

		(i == 0) ? cout << "\n���a" : cout << "\nplayer" << i;
		cout << "��:" << player[i].money << " ��`:" << player[i].bet;
	}
}