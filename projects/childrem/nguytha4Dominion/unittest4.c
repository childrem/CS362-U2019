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
	//int maxHandCount = 5;


	int currentPlayer = 0;		// 0 will be player 1 and 1 will be player 2
	//int retValue;		// return value for function being tested


	int tributeRevealedCards[2] = { -1, -1 };		// The enums of the revealed cards from next player
	int nextPlayer = currentPlayer + 1;

	int handPos;		// Hand position of the tribute card



	printf("TESTING tributeEffect():\n");
	printf("\nFirst test next player has no cards to reveal!\n\n");

	// TEST 1 -- Next Player has no cards to reveal -- Should print message

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to set the values of the next player's discard count and deck count
	// This round, next player has no cards to reveal

	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 0;
	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][0] = tribute;		// Added for Assignment 5
	handPos = 0;

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test
	
	/*retValue = */tribute_refactor(&G, handPos);


	// Assert that nothing was discarded for next player (he had no cards to begin with)

	asserttrue(G.discardCount[nextPlayer], beforeFunction.discardCount[nextPlayer], "Discard Count of Next Player");

	// Assert that nothing changed with the current player

	asserttrue(G.discardCount[currentPlayer], beforeFunction.discardCount[currentPlayer], "Discard Card of Current Player");
	

	
	

	// TEST 2 -- Next player has 1 card in deck, 0 in discard pile, and card is a treasure card -- 
	// Current Player should get + 2 coins

	printf("\n\nTest 2 Next Player 1 card in deck 0 in discard pile and card is treasure!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	tributeRevealedCards[0] = -1;
	tributeRevealedCards[1] = -1;

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to set the deck count and discard count of next player
	// First clear out next player's deck

	for (int c = 0; c < G.deckCount[nextPlayer]; c++) {
		G.deck[nextPlayer][c] = -1;
	}

	G.deck[nextPlayer][0] = copper;

	G.deckCount[nextPlayer] = 1;
	G.discardCount[nextPlayer] = 0;

	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][0] = tribute;		// Added for Assignment 5
	handPos = 0;
	

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test
	
	/*retValue = */tribute_refactor(&G, handPos);

	// Make sure the number of coins increased by 2

	asserttrue(G.coins, beforeFunction.coins + 2, "Coins");

	// Make sure number of cards did not change for next player

	asserttrue(G.deckCount[nextPlayer] + G.discardCount[nextPlayer], 
		beforeFunction.deckCount[nextPlayer] + beforeFunction.discardCount[nextPlayer], 
		"Number of Cards Available to Next Player");



	// TEST 3 -- Next player has 1 card in discard pile, 0 cards in deck, and card is an estate --
	// Current player should get 2 more cards in their hand

	printf("\n\nTest 3 Next Player 1 card in discard 0 in deck pile and card is estate!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	tributeRevealedCards[0] = -1;
	tributeRevealedCards[1] = -1;

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to set the deck count and discard count of next player
	// First clear out next player's deck

	for (int c = 0; c < G.deckCount[nextPlayer]; c++) {
		G.deck[nextPlayer][c] = -1;
	}

	G.discard[nextPlayer][0] = estate;

	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 1;

	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][0] = tribute;		// Added for Assignment 5
	handPos = 0;


	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	/*retValue = */tribute_refactor(&G, handPos);


	// Assert that current player got +2 cards in hand

	asserttrue(G.handCount[currentPlayer], beforeFunction.handCount[currentPlayer] + 2, 
		"Number of cards in current player's hand");

	// Check number of cards available to the next player after calling this function

	asserttrue(G.deckCount[nextPlayer] + G.discardCount[nextPlayer],
		beforeFunction.deckCount[nextPlayer] + beforeFunction.discardCount[nextPlayer],
		"Number of Cards Available to Next Player");


	// TEST 4 -- Next player has 1 card in discard and 1 card in deck, all cards will be action cards
	// They will be a different type -- Current player should get + 4 actions

	printf("\n\nTest 4 Next Player 1 card in discard 1 in deck pile and cards are action!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	tributeRevealedCards[0] = -1;
	tributeRevealedCards[1] = -1;

	/*r = */initializeGame(numPlayer, k, seed, &G);

	G.coins = 0;			// Start at 0 in test cases for easy 


	// Need to set the deck count and discard count of next player
	// First clear out next player's deck

	for (int c = 0; c < G.deckCount[nextPlayer]; c++) {
		G.deck[nextPlayer][c] = -1;
	}

	G.discard[nextPlayer][0] = minion;
	G.deck[nextPlayer][0] = ambassador;

	G.deckCount[nextPlayer] = 1;
	G.discardCount[nextPlayer] = 1;

	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][0] = tribute;		// Added for Assignment 5
	handPos = 0;

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	/*retValue = */tribute_refactor(&G, handPos);


	// Assert the number of actions increased by 4

	asserttrue(G.numActions, beforeFunction.numActions + 4, "Number of Actions");



	printf("\n\nEnd of Unit Test!\n");

	return 0;
}