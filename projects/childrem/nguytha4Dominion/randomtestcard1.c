#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "rngs.h"


#define MAXHANDCOUNT 5


int randomNumber(int minValue, int maxValue)
{
	int randomNumber;
	const int MIN_VALUE = minValue;
	const int MAX_VALUE = maxValue;

	randomNumber = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

	return randomNumber;
}

void printResults(char* valueName, int expected, int actual) {

	if (expected != actual) {
		printf("Reason: %s, expected value = %d, actual value was = %d\n", valueName, expected, actual);
	}

}


void testBaronCard(int choice1, struct gameState *state, int currentPlayer, int handPos) {

	// Preserve pre-function state

	struct gameState beforeFunction;

	memcpy(&beforeFunction, state, sizeof(struct gameState));

	// Call function to test

	baron_refactor(choice1, state, handPos);

	//baronEffect(choice1, state, currentPlayer);

	// Change the pre-state in the way we expect baronEffect to change the actual code

	beforeFunction.numBuys++;

	if (choice1 > 0) {
		// We set ALL cards in the player's hand to a certain value, the first card baronEffect would see would be
		// position 0
		if (beforeFunction.hand[currentPlayer][0] == estate) {
			beforeFunction.coins += 4;
			beforeFunction.handCount[currentPlayer]--;
			beforeFunction.discardCount[currentPlayer]++;
		}

		// This else will handle both the situation where the player's hand had no estate
		else {
			if (beforeFunction.supplyCount[estate] > 0) {
				beforeFunction.discardCount[currentPlayer]++;	// Estate gets added to discard pile
				beforeFunction.discard[currentPlayer][beforeFunction.discardCount[currentPlayer] - 1] = estate;
				beforeFunction.supplyCount[estate]--;
			}
		}


	}

	else {
		if (beforeFunction.supplyCount[estate] > 0) {
			beforeFunction.discardCount[currentPlayer]++;	// Estate gets added to discard pile
			beforeFunction.discard[currentPlayer][beforeFunction.discardCount[currentPlayer] - 1] = estate;
			beforeFunction.supplyCount[estate]--;
		}
	}

	// If there were no estates in the supply, the before state should equal the after state when choice1 is 0 or the
	// hand didn't have estate cards in it.  So no alteration needed for that case.

	if (memcmp(&beforeFunction, state, sizeof(struct gameState)) == 0) {
		printf("\nTest PASSED!\n");
		//printf("Enum of Card in hand was: %d\n", state->hand[currentPlayer][0]);
	}

	else {
		printf("\nTest FAILED!\n");
		//printf("Enum of Card in hand was: %d\n", state->hand[currentPlayer][0]);
		printf("Value of choice1 was: %d\n", choice1);
		if (choice1 != 0) {
			printResults("Num Coins", beforeFunction.coins + 4, state->coins);
		}
		else {
			printResults("Num Coins", beforeFunction.coins, state->coins);
		}

		printResults("Hand Count", beforeFunction.handCount[currentPlayer], state->handCount[currentPlayer]);
		printResults("Discard Count", beforeFunction.discardCount[currentPlayer], state->discardCount[currentPlayer]);
		printResults("Number of Buys", beforeFunction.numBuys, state->numBuys);
		printResults("Estate Supply Count", beforeFunction.supplyCount[estate], state->supplyCount[estate]);
		printResults("Card Added to Discard Pile",
			beforeFunction.discard[currentPlayer][beforeFunction.discardCount[currentPlayer] - 1],
			state->discard[currentPlayer][state->discardCount[currentPlayer] - 1]);
		printResults("Played Card Count", beforeFunction.playedCardCount + 1, state->playedCardCount);
	}

}


int main() {

	unsigned seed;         // srand expects an unsigned integer
	seed = time(0);        // seed set to changing value of time
	srand(seed);           // initiating seed in srand

	//int seed = 1000;
	int numPlayer = 4;

	int currentPlayer;

	int choice1;

	int cardForHand;	// Randomize what card is filling the player's hand each time a test is run

	int numBarons;
	int handPos;

	int k[10] = { minion, ambassador, tribute, gardens, mine,
				 remodel, smithy, village, baron, great_hall };

	struct gameState G;


	printf("Testing function baronEffect() with RANDOM TESTS!\n");

	

	// Change statement numTest < # to change number of tests run

	for (int numTest = 0; numTest < 10000; numTest++) {
		memset(&G, 23, sizeof(struct gameState));	// Clear previous gamestate
		initializeGame(numPlayer, k, seed, &G);		// Initialize a normal game

		// Start randomizing the necessary member variables that baronEffect uses, but keep them in
		// ranges that would be possible for a normal game

		choice1 = randomNumber(0, 100);		// Random value between 0 and 100
		
		currentPlayer = randomNumber(0, 3);	// Random value between 0 and 3

		G.supplyCount[estate] = randomNumber(0, 100);

		// 0-26 are valid enum values of cards in the game

		cardForHand = randomNumber(0, 26);

		// ALL cards in the player's hand are that one randomly determined card type

		numBarons = randomNumber(1, 4);		// Random number of barons

		for (int handPosition = 0; handPosition < MAXHANDCOUNT; handPosition++) {
			if (numBarons > 0) {
				G.hand[currentPlayer][handPosition] = baron;
				numBarons--;
			}

			else {
				G.hand[currentPlayer][handPosition] = cardForHand;
			}
		}

		G.handCount[currentPlayer] = 5;

		handPos = 0;	// Always guaranteed a baron at position 0


		testBaronCard(choice1, &G, currentPlayer, handPos);

	}


	return 0;
}