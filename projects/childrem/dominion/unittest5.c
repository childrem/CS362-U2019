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


	int currentPlayer = 0;		// 0 will be player 1 and 1 will be player 2
	//int retValue;		// return value for function being tested


	int nextPlayer = currentPlayer + 1;

	int choice1, choice2, handPos;
	// choice1 = hand array position of card we are discarding (should be treasure card)
	// choice2 = enum of card we wanted to gain (should be treasure of value + 3 coins)
	// handPos = hand array position of the mine card itself



	printf("TESTING mineEffect():\n");
	printf("\nFirst test have a copper ask for a gold!\n\n");

	// TEST 1 -- Player has a copper and asks for a gold -- 
	// Should not affect gamestate

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 copper, 1 mine, and the rest arbitrary cards.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = copper;
			}

			else if (handPosition == 1) {
				G.hand[c][handPosition] = mine;
			}

			else {
				G.hand[c][handPosition] = ambassador;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	choice1 = 0;
	choice2 = gold;
	handPos = 1;



	/*retValue = */mineEffect(choice1, choice2, &G, handPos, currentPlayer);



	// Assert that player hand count is unchanged (nothing should have been played)

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");


	// Assert that supply count is unchanged

	asserttrue(G.supplyCount[copper],
		beforeFunction.supplyCount[copper],
		"Supply of card that was chosen to return");

	// Assert that other player discard count is unchanged

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");

	// Assert that current player discard count is unchanged (nothing should be played)

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer], 
		"Discard Count of Current Player");

	// Assert that treasure in hand is still a copper

	asserttrue(G.hand[currentPlayer][0], beforeFunction.hand[currentPlayer][0], 
		"Card is still a copper (should be enum 4)");

	

	// TEST 2 -- Player has a copper asks for an ambassador --
	// Should not affect game state

	printf("\n\nTest 2 Have a copper ask for an ambassador!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 1 copper, 1 mine, and the rest arbitrary cards.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0) {
				G.hand[c][handPosition] = copper;
			}

			else if (handPosition == 1) {
				G.hand[c][handPosition] = mine;
			}

			else {
				G.hand[c][handPosition] = ambassador;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	choice1 = 0;
	choice2 = ambassador;
	handPos = 1;



	/*retValue = */mineEffect(choice1, choice2, &G, handPos, currentPlayer);



	// Assert that player hand count is unchanged (nothing should have been played)

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");


	// Assert that supply count is unchanged

	asserttrue(G.supplyCount[copper],
		beforeFunction.supplyCount[copper],
		"Supply of card that was chosen to return");

	// Assert that other player discard count is unchanged

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");

	// Assert that current player discard count is unchanged (nothing should be played)

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer],
		"Discard Count of Current Player");

	// Assert that treasure in hand is still a copper

	asserttrue(G.hand[currentPlayer][0], beforeFunction.hand[currentPlayer][0],
		"Card is still a copper (should be enum 4)");



	// TEST 3 -- Player has 2 coppers, asks for a silver --
	// We should see a discard count of 1 (the actual mine card), 1 copper should be trashed with 1 copper 
	// still in hand, there should be 1 silver in hand and supply of silver should be 1 less.

	printf("\n\nTest 3 Have 2 coppers ask for a silver!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to create the hands that the player's have. It will need 2 coppers, 1 mine, and the rest arbitrary cards.

	for (int c = 0; c < numPlayer; c++) {

		for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {
			if (handPosition == 0 || handPosition == 2) {
				G.hand[c][handPosition] = copper;
			}

			else if (handPosition == 1) {
				G.hand[c][handPosition] = mine;
			}

			else {
				G.hand[c][handPosition] = ambassador;
			}
		}

	}

	G.handCount[nextPlayer] = 5;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	choice1 = 0;
	choice2 = silver;
	handPos = 1;



	/*retValue = */mineEffect(choice1, choice2, &G, handPos, currentPlayer);



	// Assert that player hand count is 4 (mine discarded, treasure balanced out = net loss of 1 card)

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer] - 1, "Hand Count of Current Player");


	// Assert that other player hand count is unchanged

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer], "Hand Count of Next Player");


	// Assert that supply count of copper is unchanged

	asserttrue(G.supplyCount[copper],
		beforeFunction.supplyCount[copper],
		"Supply of card that was chosen to return (copper)");

	// Assert that supply count of silver is -1

	asserttrue(G.supplyCount[silver],
		beforeFunction.supplyCount[silver] - 1,
		"Supply of card that was chosen to gain (silver)");

	// Assert that other player discard count is unchanged

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");

	// Assert that current player discard count is +1 (the played mine card)

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer] + 1,
		"Discard Count of Current Player");

	// Assert that player has 1 copper and 1 silver in hand

	int numberCopper = 0;
	int numberSilver = 0;

	for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

		if (G.hand[currentPlayer][handPosition] == copper) {
			numberCopper++;
		}

		else if (G.hand[currentPlayer][handPosition] == silver) {
			numberSilver++;
		}

	}

	asserttrue(numberCopper, 1, "Number of Coppers in Current Player's Hand");
	asserttrue(numberSilver, 1, "Number of Silvers in Current Player's Hand");



	printf("\n\nEnd of Unit Test!\n");

	return 0;
}