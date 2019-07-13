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
	int r;			// return value of function being tested
	int k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState G, beforeFunction;
	int maxHandCount = 5;


	int currentPlayer = 0;		// 0 will be player 1 and 1 will be player 2


	int nextPlayer = currentPlayer + 1;


	int retValue;		// returned value from function being tested


	printf("TESTING endTurn():\n");
	printf("\nFirst Player 1 ends turn!\n\n");

	// TEST 1 -- Player 1 ends turn -- 
	// Should be player 2's turn

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// run function to test

	retValue = endTurn(&G);



	// Assert active player is now player 2 (value is 1)

	asserttrue(G.whoseTurn, beforeFunction.whoseTurn + 1, "Active Player(0 = Player 1, 1 = Player 2)");


	// Assert Player 1 has no hand

	asserttrue(G.handCount[currentPlayer], 0, "Player 1 Has No Hand Count");


	// Assert Player 2 has 5 cards in hand

	asserttrue(G.handCount[nextPlayer], beforeFunction.handCount[nextPlayer] + 5, "Player 2 has 5 card hand");

	// Assert Phase is 0

	asserttrue(G.phase, 0, "Current Phase");

	


	// TEST 2 -- Player 2 ends turn --

	printf("\n\nTest 2 Player 2 ends turn!\n\n");

	// Clear former values from beforeFunction

	memset(&beforeFunction, 23, sizeof(struct gameState));

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// run function to test

	retValue = endTurn(&G);



	// Assert active player is now player 1 (value is 0)

	asserttrue(G.whoseTurn, beforeFunction.whoseTurn - 1, "Active Player(0 = Player 1, 1 = Player 2)");


	// Assert Player 2 has no hand

	asserttrue(G.handCount[nextPlayer], 0, "Player 2 Has No Hand Count");


	// Assert Player 1 has 5 cards in hand

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer] + 5, "Player 1 has 5 card hand");

	// Assert Phase is 0

	asserttrue(G.phase, 0, "Current Phase");
	

	printf("\n\nEnd of Unit Test!\n");

	return 0;
}