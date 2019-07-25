#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


#define MAXHANDCOUNT 5

void printResult() {


}


void testBaronCard() {

}


int main() {
	int seed = 1000;
	int numPlayer = 2;

	int k[10] = { minion, ambassador, tribute, gardens, mine,
				 remodel, smithy, village, baron, great_hall };

	struct gameState G;

	

	printf("Testing function baronEffect() with RANDOM TESTS!\n");

	SelectStream(2);
	PutSeed(3);


	// Change statement numTest < # to change number of tests run

	for (int numTest = 0; numTest < 10; numTest++) {
		memset(&G, 23, sizeof(struct gameState));	// Clear previous gamestate
		initializeGame(numPlayer, k, seed, &G);		// Initialize a normal game


	}


	return 0;
}