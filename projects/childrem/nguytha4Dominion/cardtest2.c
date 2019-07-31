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
	//int maxHandCount = 5;


	int currentPlayer = 0;		// 0 will be player 1 and 1 will be player 2


	//int nextPlayer = currentPlayer + 1;


	int retValue;		// returned value from function being tested


	printf("TESTING shuffle():\n");
	printf("\nFirst test send in empty deck!\n\n");

	// TEST 1 -- Send in empty deck -- 
	// Should cause an error

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// Need to clear out the deck

	for (int handPosition = 0; handPosition < 10; handPosition++) {

		G.deck[currentPlayer][handPosition] = -1;

	}

	G.deckCount[currentPlayer] = 0;


	// run function to test

	retValue = shuffle(currentPlayer, &G);
	


	// Assert deck count is still 0

	asserttrue(G.deckCount[currentPlayer], 0, "Deck Count of Current Player");


	// Assert deck is still empty

	int emptyDeck = 1;		// Will be used as a bool

	for (int deckPosition = 0; deckPosition < 10; deckPosition++) {
		
		if (G.deck[currentPlayer][deckPosition] != -1) {
			emptyDeck = 0;
		}

	}

	asserttrue(emptyDeck, 1, "Deck was Still Empty (Yes = 1, No = 0):");

	// Assert function returned with -1

	asserttrue(retValue, -1, "Shuffle Return Value");




	// TEST 2 -- 1 card in deck --

	printf("\n\nTest 2 1 card in deck!\n\n");

	// initialze new game
	
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// Need to clear out the deck

	for (int handPosition = 0; handPosition < 10; handPosition++) {

		G.deck[currentPlayer][handPosition] = -1;

	}

	// set first deck position to mine

	G.deck[currentPlayer][0] = mine;

	G.deckCount[currentPlayer] = 1;


	// run function to test

	retValue = shuffle(currentPlayer, &G);



	// Assert deck count is still 1

	asserttrue(G.deckCount[currentPlayer], 1, "Deck Count of Current Player");


	// Assert deck is still the same

	int sameDeck = 1;		// Will be used as a bool

	for (int deckPosition = 0; deckPosition < 10; deckPosition++) {

		if (deckPosition == 0) {
			if (G.deck[currentPlayer][deckPosition] != mine) {
				sameDeck = 0;
			}
		}

		else if (G.deck[currentPlayer][deckPosition] != -1) {
			sameDeck = 0;
		}

	}

	asserttrue(sameDeck, 1, "Deck was the same (Yes = 1, No = 0):");

	// Assert function returned with 0

	asserttrue(retValue, 0, "Shuffle Return Value");


	

	// TEST 3 -- 5 cards sent in --

	printf("\n\nTest 3 5 cards sent in!\n\n");

	// initialze new game
	
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));


	// Need to clear out the deck

	for (int handPosition = 0; handPosition < 10; handPosition++) {

		G.deck[currentPlayer][handPosition] = -1;

	}

	// set the specific deck of cards

	G.deck[currentPlayer][0] = baron;
	G.deck[currentPlayer][1] = minion;
	G.deck[currentPlayer][2] = ambassador;
	G.deck[currentPlayer][3] = tribute;
	G.deck[currentPlayer][4] = mine;

	G.deckCount[currentPlayer] = 5;


	// run function to test

	retValue = shuffle(currentPlayer, &G);



	// Assert deck count is still 5

	asserttrue(G.deckCount[currentPlayer], 5, "Deck Count of Current Player");


	// Assert deck is different

	int differentDeck = 1;		// Will be used as a bool

	if (G.deck[currentPlayer][0] == baron && G.deck[currentPlayer][1] == minion &&
		G.deck[currentPlayer][2] == ambassador && G.deck[currentPlayer][3] == tribute &&
		G.deck[currentPlayer][4] == mine) {

		differentDeck = 0;
	}
	

	asserttrue(differentDeck, 1, "Deck was shuffled (Yes = 1, No = 0):");

	// Assert function returned with 0

	asserttrue(retValue, 0, "Shuffle Return Value");



	printf("\n\nEnd of Unit Test!\n");

	return 0;
}