#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

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
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount;
	int bonus;
	int k[10] = { minion, ambassador, tribute, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState G, beforeFunction;
	int maxHandCount = 5;

	int choice1;
	int currentPlayer;		// 0 will be player 1 and 1 will be player 2
	int retValue;		// return value for function being tested

	// arrays of all coppers, silvers, and golds
	//int coppers[MAX_HAND];
	//int silvers[MAX_HAND];
	//int golds[MAX_HAND];
	//for (i = 0; i < MAX_HAND; i++)
	//{
		//coppers[i] = copper;
		//silvers[i] = silver;
		//golds[i] = gold;
	//}

	printf("TESTING baronEffect():\n");


	// TEST 1 -- choice1 is set -- we should be discarding an estate and adding 4 gold to currentPlayer

	// initialze game
	memset(&G, 23, sizeof(struct gameState));
	memset(&beforeFunction, 23, sizeof(struct gameState));

	r = initializeGame(numPlayer, k, seed, &G);

	// capture initial state of the game
	memcpy(&beforeFunction, &G, sizeof(struct gameState));

	// run function to test

	

	// TEST 2 -- choice1 is NOT set -- currentPlayer should be gaining an estate (coins should remain the same)




	//asserttrue(5, 6, "coins");

	/*
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 1; handCount <= maxHandCount; handCount++)
		{
			for (bonus = 0; bonus <= maxBonus; bonus++)
			{
#if (NOISY_TEST == 1)
				printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.handCount[p] = handCount;                 // set the number of cards on hand
				memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
				printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
				assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

				memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
				updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
				printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
				assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

				memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
				updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
				printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
				assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
			}
		}
	}

	*/

	printf("\nEnd of Unit Test!\n");

	return 0;
}