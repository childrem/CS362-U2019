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

	int choice1;
	int currentPlayer;		// 0 will be player 1 and 1 will be player 2
	int retValue;		// return value for function being tested

	int numEstates;		// Will count number of estates in a player's hand
	#define numEstatesBefore 1;	// Number of estates that will appear in each player's hand
	int tempNumEstatesBefore;	// Used in the for loop to make unit test more robust

	

	printf("TESTING baronEffect():\n");
	printf("\nFirst test has choice1 set\n\n");

	// TEST 1 -- choice1 is set -- we should be discarding an estate and adding 4 coins to currentPlayer

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);
	G.coins = 0;			// Start at 0 in test cases for easy 


	// We need to make sure that each player has at least 1 estate card in their first hand for testing
	// Set other hand positions to copper for better control
	// Last hand position needs to be open so we can gain an estate card if necessary

	for (int c = 0; c < numPlayer; c++) {
		tempNumEstatesBefore = numEstatesBefore;

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (tempNumEstatesBefore > 0) {
				G.hand[c][handPosition] = estate;
				tempNumEstatesBefore--;
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
	
	retValue = baronEffect(choice1, &G, currentPlayer);


	// compare number of coins expected vs actual

	asserttrue(G.coins, beforeFunction.coins + 4, "COINS");


	// compare the number of estate cards in the current player's hand (should have decreased by 1)

	tempNumEstatesBefore = numEstatesBefore;

	for (int c = 0; c < numPlayer; c++) {

		numEstates = 0;

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

			if (G.hand[c][handPosition] == estate) {
				numEstates++;
			}
		}

		if (c == 0) {		// the current player
			asserttrue(numEstates, tempNumEstatesBefore - 1, "Current Player Num Estates In Hand:");
		}

		else {
			asserttrue(numEstates, tempNumEstatesBefore, "Other Player Num Estates In Hand:");
		}

	}


	// Check to see if the discard count increased by 1 and if the last position of the discard array is an estate
	// If this passes then an estate was GAINED (so test FAILED)

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer] + 1, "Current Player Discard Count");

	asserttrue(G.discard[currentPlayer][G.discardCount[currentPlayer]-1], estate, 
		"Newest discard card (Would be 1 for estate):");


	// Make sure the other player's discard pile stayed the same

	asserttrue(G.discardCount[currentPlayer + 1], beforeFunction.discardCount[currentPlayer + 1], 
		"Other Player Discard Count");



	// TEST 2 -- choice1 is NOT set -- currentPlayer should be gaining an estate (coins should remain the same)

	printf("\n\nNow testing with choice1 NOT set!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);
	G.coins = 0;			// Start at 0 in test cases for easy 


	// We need to make sure that each player has at least 1 estate card in their first hand for testing
	// Set other hand positions to copper for better control

	for (int c = 0; c < numPlayer; c++) {
		tempNumEstatesBefore = numEstatesBefore;

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (tempNumEstatesBefore > 0) {
				G.hand[c][handPosition] = estate;
				tempNumEstatesBefore--;
			}

			else {
				G.hand[c][handPosition] = copper;
			}
		}

	}

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test - this time don't set choice1
	choice1 = 0;
	currentPlayer = 0;

	retValue = baronEffect(choice1, &G, currentPlayer);


	// compare number of coins expected vs actual

	asserttrue(G.coins, beforeFunction.coins, "COINS");


	// compare the number of estate cards in the current player's hand (should be the same)

	tempNumEstatesBefore = numEstatesBefore;

	for (int c = 0; c < numPlayer; c++) {

		numEstates = 0;

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

			if (G.hand[c][handPosition] == estate) {
				numEstates++;
			}
		}

		if (c == 0) {		// the current player
			asserttrue(numEstates, tempNumEstatesBefore, "Current Player Num Estates In Hand");
		}

		else {
			asserttrue(numEstates, tempNumEstatesBefore, "Other Player Num Estates In Hand");
		}

	}

	// Check to make sure the discard count increased by 1 and that the last position of the discard array is an estate

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer] + 1, "Current Player Discard Count");

	asserttrue(G.discard[currentPlayer][G.discardCount[currentPlayer] - 1], estate,
		"Newest discard card (Should be 1 for estate)");


	// Make sure the other player's discard pile stayed the same

	asserttrue(G.discardCount[currentPlayer + 1], beforeFunction.discardCount[currentPlayer + 1],
		"Other Player Discard Count");


	

	printf("\nEnd of Unit Test!\n");

	return 0;
}