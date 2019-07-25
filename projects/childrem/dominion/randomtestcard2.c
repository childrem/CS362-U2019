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

/*

void testBaronCard(int choice1, struct gameState *state, int currentPlayer) {

	// Preserve pre-function state

	struct gameState beforeFunction;

	memcpy(&beforeFunction, state, sizeof(struct gameState));

	// Call function to test

	baronEffect(choice1, state, currentPlayer);

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
		printf("Enum of Card in hand was: %d\n", state->hand[currentPlayer][0]);
		printf("Value of choice1 was: %d\n", choice1);
		printResults("Num Coins", beforeFunction.coins, state->coins);
		printResults("Hand Count", beforeFunction.handCount[currentPlayer], state->handCount[currentPlayer]);
		printResults("Discard Count", beforeFunction.discardCount[currentPlayer], state->discardCount[currentPlayer]);
		printResults("Number of Buys", beforeFunction.numBuys, state->numBuys);
		printResults("Estate Supply Count", beforeFunction.supplyCount[estate], state->supplyCount[estate]);
		printResults("Card Added to Discard Pile",
			beforeFunction.discard[currentPlayer][beforeFunction.discardCount[currentPlayer] - 1],
			state->discard[currentPlayer][state->discardCount[currentPlayer] - 1]);
	}

}

*/


void testMinionCard(int choice1, struct gameState *state, int handPos, int currentPlayer, int numPlayer) {

	// Preserve pre-function state

	struct gameState beforeFunction;

	memcpy(&beforeFunction, state, sizeof(struct gameState));

	// Call function to test

	minionEffect(choice1, state, handPos, currentPlayer);

	// Change the pre-state in the way we expect minionEffect to change the actual code

	beforeFunction.numActions++;

	if (choice1) {
		beforeFunction.coins += 2;
		beforeFunction.discardCount[currentPlayer]++;	// discard the minion card itself
		beforeFunction.handCount[currentPlayer]--;
	}

	else {
		beforeFunction.discardCount[currentPlayer] = beforeFunction.discardCount[currentPlayer] + 
			beforeFunction.handCount[currentPlayer];	// Player discards their hand
		beforeFunction.handCount[currentPlayer] = 4;	// Draw 4 cards

		for (int playerNum = 0; playerNum < numPlayer; playerNum++) {
			if (playerNum != currentPlayer) {
				if (beforeFunction.handCount[playerNum] > 4) {
					beforeFunction.discardCount[playerNum] = beforeFunction.discardCount[playerNum] +
						beforeFunction.handCount[playerNum];	// Player discards their hand
					beforeFunction.handCount[playerNum] = 4;	// Draw 4 cards
				}
			}
		}
	}
	
	if (memcmp(&beforeFunction, state, sizeof(struct gameState)) == 0) {
		printf("\nTest PASSED!\n");
	}

	else {
		printf("\nTest FAILED!\n");
		printf("Value of choice1 was: %d\n", choice1);
		if (choice1) {
			printResults("Discard Count Current Player", beforeFunction.discardCount[currentPlayer],
				state->discardCount[currentPlayer]);
		}

		else {
			
		}
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

	int handPos;
	int handCount;		// Number of cards each player has


	int k[10] = { minion, ambassador, tribute, gardens, mine,
				 remodel, smithy, village, baron, great_hall };

	struct gameState G;


	printf("Testing function minionEffect() with RANDOM TESTS!\n");



	// Change statement numTest < # to change number of tests run

	for (int numTest = 0; numTest < 1000; numTest++) {
		memset(&G, 23, sizeof(struct gameState));	// Clear previous gamestate
		initializeGame(numPlayer, k, seed, &G);		// Initialize a normal game

		// Start randomizing the necessary member variables that baronEffect uses, but keep them in
		// ranges that would be possible for a normal game

		choice1 = randomNumber(0, 5);		// Random value between 0 and 5

		currentPlayer = randomNumber(0, 3);	// Random value between 0 and 3
		G.whoseTurn = currentPlayer;		// Have to let it know whose turn it is (player playing the card)

		for (int playerNum = 0; playerNum < numPlayer; playerNum++) {
			
			handCount = randomNumber(1, MAXHANDCOUNT);

			G.handCount[playerNum] = handCount;

			// We need to make sure all player's have hands so we don't seg fault because players don't get
			// hands until their turn comes up

			for (int handPosition = 0; handPosition < handCount; handPosition++) {
				G.hand[playerNum][handPosition] = copper;
			}
			
			if (playerNum == currentPlayer) {
				handPos = randomNumber(0, handCount);	// Position of the minion card itself
				G.hand[playerNum][handPos] = minion;		// Force a minion into the hand
			}
		}


		

		testMinionCard(choice1, &G, handPos, currentPlayer, numPlayer);

	}


	return 0;
}