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



	printf("TESTING initializeGame():\n");
	printf("\nFirst test 2 players all different kingdom cards!\n\n");

	// TEST 1 -- 2 players all different kingdom cards -- 
	// Should run as expected

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	/*r = */initializeGame(numPlayer, k, seed, &G);


	// Assert number of players correctly set

	asserttrue(G.numPlayers, numPlayer, "Number of Players");


	// Assert supply count of curse is correct for number of players

	asserttrue(G.supplyCount[curse], 10, "Curse Cards in Supply for 2 players");


	// Assert that supply count of provinces is correct for number of players

	asserttrue(G.supplyCount[province], 8, "Province Cards in Supply for 2 players");


	// Assert that copper card supply is correct for number of players

	asserttrue(G.supplyCount[copper], 60 - (7 * numPlayer), "Copper Supply for 2 players");


	// Assert that deck count is set

	asserttrue(G.deckCount[currentPlayer], 5, "Deck Count for Current Player (10 - 5)");


	// Assert that hand count is set

	asserttrue(G.handCount[currentPlayer], 5, "Hand Count for Current Player");



	// TEST 2 -- 2 players invalid kingdom card set (a repeat present) --
	// Should not allow function to run

	printf("\n\nTest 2 2 players, invalid kingdom card set (a repeat present)!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	seed = 1000;
	numPlayer = 2;

	/*k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };*/
	k[1] = minion;

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// Assert number of players correctly set

	asserttrue(G.numPlayers, numPlayer, "Number of Players");


	// Assert supply count of curse is correct for number of players

	asserttrue(G.supplyCount[curse], 10, "Curse Cards in Supply for 2 players");


	// Assert that supply count of provinces is correct for number of players

	asserttrue(G.supplyCount[province], 8, "Province Cards in Supply for 2 players");


	// Assert that copper card supply is correct for number of players

	asserttrue(G.supplyCount[copper], 60 - (7 * numPlayer), "Copper Supply for 2 players");


	// Assert that deck count is set

	asserttrue(G.deckCount[currentPlayer], 5, "Deck Count for Current Player (10 - 5)");


	// Assert that hand count is set

	asserttrue(G.handCount[currentPlayer], 5, "Hand Count for Current Player");



	// TEST 3 -- 3 players, valid kingdom cards --

	printf("\n\nTest 3 3 players, valid kingdom cards!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	seed = 1000;
	numPlayer = 3;

	/*k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };*/
	k[1] = ambassador;

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// Assert number of players correctly set

	asserttrue(G.numPlayers, numPlayer, "Number of Players");


	// Assert supply count of curse is correct for number of players

	asserttrue(G.supplyCount[curse], 20, "Curse Cards in Supply for 3 players");


	// Assert that supply count of provinces is correct for number of players

	asserttrue(G.supplyCount[province], 12, "Province Cards in Supply for 3+ players");


	// Assert that copper card supply is correct for number of players

	asserttrue(G.supplyCount[copper], 60 - (7 * numPlayer), "Copper Supply for 3 players");


	// Assert that deck count is set

	asserttrue(G.deckCount[currentPlayer], 5, "Deck Count for Current Player (10 - 5)");


	// Assert that hand count is set

	asserttrue(G.handCount[currentPlayer], 5, "Hand Count for Current Player");



	// TEST 4 -- 4 players, valid kingdom cards --

	printf("\n\nTest 4 4 players, valid kingdom cards!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	seed = 1000;
	numPlayer = 4;

	/*k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };*/

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// Assert number of players correctly set

	asserttrue(G.numPlayers, numPlayer, "Number of Players");


	// Assert supply count of curse is correct for number of players

	asserttrue(G.supplyCount[curse], 30, "Curse Cards in Supply for 4+ players");


	// Assert that supply count of provinces is correct for number of players

	asserttrue(G.supplyCount[province], 12, "Province Cards in Supply for 3+ players");


	// Assert that copper card supply is correct for number of players

	asserttrue(G.supplyCount[copper], 60 - (7 * numPlayer), "Copper Supply for 4 players");


	// Assert that deck count is set

	asserttrue(G.deckCount[currentPlayer], 5, "Deck Count for Current Player (10 - 5)");


	// Assert that hand count is set

	asserttrue(G.handCount[currentPlayer], 5, "Hand Count for Current Player");



	// TEST 5 -- 5 players (too many), valid kingdom cards --

	printf("\n\nTest 5 5 players (too many), valid kingdom cards!\n\n");

	// initialze new game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	seed = 1000;
	numPlayer = 5;

	/*k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };*/

	/*r = */initializeGame(numPlayer, k, seed, &G);

	// Assert number of players correctly set

	asserttrue(G.numPlayers, numPlayer, "Number of Players");


	// Assert supply count of curse is correct for number of players

	asserttrue(G.supplyCount[curse], 30, "Curse Cards in Supply for 4+ players");


	// Assert that supply count of provinces is correct for number of players

	asserttrue(G.supplyCount[province], 12, "Province Cards in Supply for 3+ players");


	// Assert that copper card supply is correct for number of players

	asserttrue(G.supplyCount[copper], 60 - (7 * numPlayer), "Copper Supply for 5 players");


	// Assert that deck count is set

	asserttrue(G.deckCount[currentPlayer], 5, "Deck Count for Current Player (10 - 5)");


	// Assert that hand count is set

	asserttrue(G.handCount[currentPlayer], 5, "Hand Count for Current Player");


	printf("\n\nEnd of Unit Test!\n");

	return 0;
}