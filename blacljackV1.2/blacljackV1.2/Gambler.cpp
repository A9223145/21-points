#include "Gambler.h"

Gambler::Gambler() {
	for (int i = 0; i < 6; i++) {
		hand[i] = NULL;
	}
	handNum = NULL;
	split = NULL;
	splitNum = NULL;
	money = NULL;
	bet = NULL;
	splitBet = NULL;
	isBlackjack = NULL;
	isInsurance = NULL;
	isSplit = NULL;
	isDouble = NULL;
	isSplitDouble = NULL;
	isSurrender = NULL;
	isStand = NULL;
	isSplitStand = NULL;
}