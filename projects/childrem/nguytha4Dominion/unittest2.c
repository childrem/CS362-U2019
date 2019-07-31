#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void asserttrue(int actualValue, int expectedValue, char* valueName) {

	if (actualValue == expectedValue) {

		printf("\nPASS: Actual value of %s was %d and expected value was %d!\n",
			valueName, actualValue, expectedValue);
	}

	else {

		printf("\nFAIL: VALUES of %s NOT EQUAL! Actual value: %d, Expected value: %d\n",
			valueName, actualValue, expectedValue);
	}

}


int main() {
	int seed = 1000;
	int numPlayer = 2;
	//int maxBonus = 10;
	//int r;
	int k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState G, beforeFunction;
	int maxHandCount = 5;

	int choice1;
	int currentPlayer;		// 0 will be player 1 and 1 will be player 2
	//int retValue;		// return value for function being tested

	int handPos;		// The array position of the minion card



	printf("TESTING minionEffect():\n");
	printf("\nFirst test choice1 is set!\n\n");

	// TEST 1 -- Choice1 is set -- The number of coins should increase by 2

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 minion card and I'll make the rest
	// coppers arbitrarily. The last hand position will have the minion card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == maxHandCount - 1) {
				G.hand[c][handPosition] = minion;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test
	choice1 = 1;
	currentPlayer = 0;
	handPos = maxHandCount - 1;

	/*retValue = */minionEffect(choice1, &G, handPos, currentPlayer);


	// Assert that the action count increased by 1

	asserttrue(G.numActions, beforeFunction.numActions + 1, "Number of Actions");

	// Assert that number of coins has increased by 2

	asserttrue(G.coins, beforeFunction.coins + 2, "Coins");


	// Assert that minion card is no longer present in the hand

	int foundMinion = 0;		// Will use as a bool that gets set if minion found

	for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

		if (beforeFunction.hand[currentPlayer][handPosition] == minion) {
			foundMinion = 1;		// true, minion found
		}

	}

	asserttrue(foundMinion, 1, "Found Minion Before Function (Present = 1, Not Present = 0):");

	foundMinion = 0;		// Will use as a bool that gets set if minion found

	for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

		if (G.hand[currentPlayer][handPosition] == minion) {
			foundMinion = 1;		// true, minion found
		}

	}

	asserttrue(foundMinion, 0, "Found Minion After Function (Present = 1, Not Present = 0):");



	// TEST 2 -- Choice1 is NOT set -- The number of coins should stay the same, current player
	// and all other players with 5 or more cards in their current hands should have 4 new cards as their hands
	// Their discard count should increase by their previous hand count.

	printf("\n\nTest 2 Choice1 is NOT set!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 minion card and I'll make the rest
	// a unique blend of 5 cards. The first hand position will have the minion card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = minion;
			}

			else if (handPosition == 1) {
				G.hand[c][handPosition] = baron;
			}

			else if (handPosition == 2) {
				G.hand[c][handPosition] = ambassador;
			}

			else if (handPosition == 3) {
				G.hand[c][handPosition] = tribute;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	G.handCount[currentPlayer + 1] = 5;

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test
	choice1 = 0;
	currentPlayer = 0;
	handPos = 0;

	/*retValue = */minionEffect(choice1, &G, handPos, currentPlayer);


	// Assert that coins stayed the same

	asserttrue(G.coins, beforeFunction.coins, "Coins");

	// Assert that players now have 4 cards in their hands

	asserttrue(G.handCount[currentPlayer], 4, "Number of Cards in hand Current Player");

	asserttrue(G.handCount[currentPlayer + 1], 4, "Number of Cards in hand Other Player");


	// Make sure player actually has a new hand

	int sameHand;		// Will be used as a bool

	for (int playerNum = 0; playerNum < numPlayer; playerNum++) {

		sameHand = 1;

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

			if (G.hand[playerNum][handPosition] != beforeFunction.hand[playerNum][handPosition]) {	// Found difference
				sameHand = 0;
			}

		}

		if (playerNum == currentPlayer) {
			asserttrue(sameHand, 0, "Current Player Same Hand (Yes = 1, No = 0):");
		}

		else {
			asserttrue(sameHand, 0, "Other Player Same Hand (Yes = 1, No = 0):");
		}

	}


	// TEST 3 -- Choice1 is NOT set -- Same as before, but I'm going to set the starting hand counts to 4 to
	// make sure only other players with 5 or more cards are affected by the minion

	printf("\n\nTest 3 Choice1 is NOT set Hand Count = 4!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 minion card and I'll make the rest
	// a unique blend of 5 cards. The first hand position will have the minion card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = minion;
			}

			else if (handPosition == 1) {
				G.hand[c][handPosition] = baron;
			}

			else if (handPosition == 2) {
				G.hand[c][handPosition] = ambassador;
			}

			else if (handPosition == 3) {
				G.hand[c][handPosition] = tribute;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	// Remove the second player's 5th card
	G.hand[currentPlayer + 1][4] = -1;
	G.handCount[currentPlayer + 1] = 4;

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test
	choice1 = 0;
	currentPlayer = 0;
	handPos = 0;

	/*retValue = */minionEffect(choice1, &G, handPos, currentPlayer);


	// Assert that coins stayed the same

	asserttrue(G.coins, beforeFunction.coins, "Coins");

	// Assert that players now have 4 cards in their hands

	asserttrue(G.handCount[currentPlayer], 4, "Number of Cards in hand Current Player");

	asserttrue(G.handCount[currentPlayer + 1], 4, "Number of Cards in hand Other Player");


	// Make sure player actually has a new hand

	for (int playerNum = 0; playerNum < numPlayer; playerNum++) {

		sameHand = 1;

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

			if (G.hand[playerNum][handPosition] != beforeFunction.hand[playerNum][handPosition]) {	// Found difference
				sameHand = 0;
			}

		}

		if (playerNum == currentPlayer) {
			asserttrue(sameHand, 0, "Current Player Same Hand (Yes = 1, No = 0):");
		}

		else {
			// Should see the same hand here if other player was unaffected by minion
			asserttrue(sameHand, 1, "Other Player Same Hand (Yes = 1, No = 0):");
		}

	}



	printf("\n\nEnd of Unit Test!\n");

	return 0;
}