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


	printf("TESTING drawCard():\n");
	printf("\nPlayer's deck is empty, and discard pile is empty!\n\n");

	// TEST 1 -- Player's deck is empty, and discard pile is empty -- 

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);


	// Alter the number of cards player has

	// Clear the hand

	for (int handPosition = 0; handPosition < maxHandCount; handPosition++) {

		G.hand[currentPlayer][handPosition] = -1;
	}

	G.handCount[currentPlayer] = 0;


	// Clear the deck

	for (int deckPosition = 0; deckPosition < 10; deckPosition++) {

		G.deck[currentPlayer][deckPosition] = -1;

	}

	G.deckCount[currentPlayer] = 0;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// run function to test


	retValue = drawCard(currentPlayer, &G);


	// Assert drawCard returned -1

	asserttrue(retValue, -1, "Return Value of drawCard");

	// Assert that hand count is 0

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Hand Count of Player");

	// Assert that deck count is 0

	asserttrue(G.deckCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Deck Count of Player");

	// Assert that discard count is 0

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer], "Discard Count of Player");




	// TEST 2 -- Player has no cards in deck or hand, but has a card in their discard pile --

	printf("\n\nTest 2 Player has no cards in deck or hand, but has a card in their discard pile\n\n");

	G.discard[currentPlayer][0] = tribute;
	G.discardCount[currentPlayer] = 1;


	// run function to test


	retValue = drawCard(currentPlayer, &G);


	// Assert drawCard returned 0

	asserttrue(retValue, 0, "Return Value of drawCard");

	// Assert that hand count is 1

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer] + 1, "Hand Count of Player");

	// Assert that deck count is 0

	asserttrue(G.deckCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Deck Count of Player");

	// Assert that discard count is 0

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer], "Discard Count of Player");


	// TEST 3 -- Player now has a card in their deck

	printf("\n\nTest 3 Player now has a card in their deck\n\n");

	// Add a card to the deck

	G.deck[currentPlayer][0] = ambassador;
	G.deckCount[currentPlayer] = 1;

	// run function to test


	retValue = drawCard(currentPlayer, &G);


	// Assert drawCard returned 0

	asserttrue(retValue, 0, "Return Value of drawCard");

	// Assert that hand count is 2 (prior drawed card + this new one)

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer] + 2, "Hand Count of Player");

	// Assert that deck count is 0

	asserttrue(G.deckCount[currentPlayer], beforeFunction.handCount[currentPlayer], "Deck Count of Player");

	// Assert that discard count is 0

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer], "Discard Count of Player");


	printf("\n\nEnd of Unit Test!\n");

	return 0;
}