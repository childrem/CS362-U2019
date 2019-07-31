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
	//int r;			// return value of function being tested
	int k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState G, beforeFunction;
	int maxHandCount = 5;


	int currentPlayer = 0;		// 0 will be player 1 and 1 will be player 2


	int nextPlayer = currentPlayer + 1;


	//int retValue;		// returned value from function being tested


	printf("TESTING getWinners():\n");
	printf("\nFirst Player 1 wins!\n\n");

	// TEST 1 -- Player 1 wins -- 

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// Make Player 1 the winner

	// Clear the deck

	G.deckCount[currentPlayer] = 0;
	G.deckCount[nextPlayer] = 0;

	// Clear the discard pile

	G.discardCount[currentPlayer] = 0;
	G.discardCount[nextPlayer] = 0;

	// Clear the hand

	for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

		G.hand[currentPlayer][handPosition] = -1;
	}

	G.hand[currentPlayer][0] = province;

	

	// run function to test

	int scoreList1[4];

	/*retValue = */getWinners(scoreList1, &G);



	// Assert Player 1 won (has a 1 in scoreList1 array)

	asserttrue(scoreList1[currentPlayer], 1, "Player 1 won (Yes = 1, No = 0)");


	// Assert Player 2 lost (has a 0 in scoreList1 array)

	asserttrue(scoreList1[nextPlayer], 0, "Player 2 won (Yes = 1, No = 0)");




	// TEST 2 -- Game is a tie (but Player 2 wins because fewer turns) --

	printf("\n\nTest 2 Game is a tie (but Player 2 wins because fewer turns)!\n\n");

	G.hand[nextPlayer][0] = province;
	G.handCount[nextPlayer] = 1;
	

	// run function to test

	int scoreList2[4];

	/*retValue = */getWinners(scoreList2, &G);



	// Assert Player 1 lost (has a 0 in scoreList2 array)

	asserttrue(scoreList2[currentPlayer], 0, "Player 1 won (Yes = 1, No = 0)");


	// Assert Player 2 won (has a 1 in scoreList2 array)

	asserttrue(scoreList2[nextPlayer], 1, "Player 2 won (Yes = 1, No = 0)");


	printf("\n\nEnd of Unit Test!\n");

	return 0;
}