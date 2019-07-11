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
	int maxBonus = 10;
	int r;
	int k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState G, beforeFunction;
	int maxHandCount = 5;


	int currentPlayer = 0;		// 0 will be player 1 and 1 will be player 2
	int retValue;		// return value for function being tested


	int nextPlayer = currentPlayer + 1;

	int choice1, choice2, handPos;
	// choice1 = hand array position of card asking to return to supply
	// choice2 = number of copies asking to return
	// handPos = hand array position of the ambassador itself



	printf("TESTING ambassadorEffect():\n");
	printf("\nFirst test have 0 copies asking to remove 2!\n\n");

	// TEST 1 -- Player has 1 copy of card they want to send to supply but ask to send back 2 -- 
	// Should not affect gamestate

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 tribute card, 1 ambassador, and I'll make the rest
	// coppers arbitrarily. The first hand position will have the tribute card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = tribute;
			}

			else if (handPosition == maxHandCount - 1) {
				G.hand[c][handPosition] = ambassador;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	choice1 = 0;
	choice2 = 2;
	handPos = maxHandCount - 1;


	retValue = ambassadorEffect(choice1, choice2, &G, handPos, currentPlayer);


	// Assert that player hand count is unchanged

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");


	// Assert that supply count is unchanged

	asserttrue(G.supplyCount[G.hand[currentPlayer][choice1]], 
		beforeFunction.supplyCount[beforeFunction.hand[currentPlayer][choice1]], 
		"Supply of card that was chosen to return");

	// Assert that other player discard count is unchanged

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");
	


	// TEST 2 -- Player has 1 copy of card they want to return to supply, but choose to send back 3 --
	// Code should catch invalid value for choice2 and return without changing the state of the game

	printf("\n\nTest 2 Have 1 copy asking to return 3!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 tribute card, 1 ambassador, and I'll make the rest
	// coppers arbitrarily. The first hand position will have the tribute card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = tribute;
			}

			else if (handPosition == maxHandCount - 1) {
				G.hand[c][handPosition] = ambassador;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	choice1 = 0;
	choice2 = 3;
	handPos = maxHandCount - 1;


	retValue = ambassadorEffect(choice1, choice2, &G, handPos, currentPlayer);


	// Assert that player hand count is unchanged

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");


	// Assert that supply count is unchanged

	asserttrue(G.supplyCount[G.hand[currentPlayer][choice1]],
		beforeFunction.supplyCount[beforeFunction.hand[currentPlayer][choice1]],
		"Supply of card that was chosen to return");

	// Assert that other player discard count is unchanged

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");



	// TEST 3 -- Player has 1 copy of card, and asks to return 1 copy, but asks to return the ambassador card itself --
	// Current game state should be unchanged

	printf("\n\nTest 3 Have 1 copy asking to return 1, but ambassador itself!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 tribute card, 1 ambassador, and I'll make the rest
	// coppers arbitrarily. The first hand position will have the tribute card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = tribute;
			}

			else if (handPosition == maxHandCount - 1) {
				G.hand[c][handPosition] = ambassador;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	choice2 = 1;
	handPos = maxHandCount - 1;
	choice1 = handPos;


	retValue = ambassadorEffect(choice1, choice2, &G, handPos, currentPlayer);


	// Assert that player hand count is unchanged

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");


	// Assert that supply count is unchanged

	asserttrue(G.supplyCount[G.hand[currentPlayer][choice1]],
		beforeFunction.supplyCount[beforeFunction.hand[currentPlayer][choice1]],
		"Supply of card that was chosen to return");

	// Assert that other player discard count is unchanged

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");



	// TEST 4 -- Player has 2 copies of card and chooses to return 2 copies to the supply --
	// We should see the player’s hand count decrease by 3 (the ambassador card leaves as well as the returned tributes), 
	// the supply count should increase by 1 (2 returned – 1 received by other player) and other player’s discard count 
	// should increase by 1 (this card should be a tribute).

	printf("\n\nTest 4 Have 2 copies asking to return 2!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 tribute card, 1 ambassador, and I'll make the rest
	// coppers arbitrarily. The first hand position will have the tribute card.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0 || handPosition == 1) {
				G.hand[c][handPosition] = tribute;
			}

			else if (handPosition == maxHandCount - 1) {
				G.hand[c][handPosition] = ambassador;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// run function to test

	choice2 = 2;
	handPos = maxHandCount - 1;
	choice1 = 0;


	retValue = ambassadorEffect(choice1, choice2, &G, handPos, currentPlayer);


	// Assert that player hand count is 3 less

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer] - 3, "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");

	// Make sure no tributes remain

	int tributeFound = 0;

	for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
		if (G.hand[currentPlayer][handPosition] == tribute) {
			tributeFound = 1;
		}
	}

	asserttrue(tributeFound, 0, "Tribute Card Found in Current Player Hand (Yes = 1, No = 0):");


	// Assert that supply count is + 1

	asserttrue(G.supplyCount[tribute],
		beforeFunction.supplyCount[tribute] + 1,
		"Supply of card that was chosen to return");

	// Assert that other player discard count is + 1

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer] + 1, "Discard Count of Next Player");

	// Assert that gained card was a tribute

	asserttrue(G.discard[nextPlayer][G.discardCount[nextPlayer] - 1], tribute, "Gained card should be tribute (19)");

	// Assert that current player discard count is + 1 (the ambassador card)

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer], "Discard Count of Current Player");



	printf("\n\nEnd of Unit Test!\n");

	return 0;
}