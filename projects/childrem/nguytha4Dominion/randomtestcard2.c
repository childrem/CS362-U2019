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

		// Since this is not a test of discardCard's functionality, I am trusting the functionality of this function
		// and therefore not manually changing everything that it changes

		discardCard(handPos, currentPlayer, &beforeFunction, 0);
	}

	else {
		while (beforeFunction.handCount[currentPlayer] > 0) {
			discardCard(handPos, currentPlayer, &beforeFunction, 0);
		}

		// We don't have control over the random number generation of draw card so I'm trusting these values
		// Draw 4 cards

		for (int handPosition = 0; handPosition < 4; handPosition++) {
			beforeFunction.hand[currentPlayer][handPosition] = state->hand[currentPlayer][handPosition];
		}

		beforeFunction.handCount[currentPlayer] = 4;

		// Everyone with more than 4 cards discards their current hand and should then have a hand count of 4

		for (int playerNum = 0; playerNum < numPlayer; playerNum++) {
			if (playerNum != currentPlayer) {
				if (beforeFunction.handCount[playerNum] > 4) {	// They have to discard their hand
					
					while (beforeFunction.handCount[playerNum] > 0) {
						discardCard(handPos, playerNum, &beforeFunction, 0);
					}


					for (int handPosition = 0; handPosition < 4; handPosition++) {
						beforeFunction.hand[playerNum][handPosition] = state->hand[playerNum][handPosition];
					}

					beforeFunction.handCount[playerNum] = 4;

				}
			}
		}
	}
	
	if (memcmp(&beforeFunction, state, sizeof(struct gameState)) == 0) {
		printf("\nTest PASSED!\n");
		printf("Value of choice1 was: %d\n", choice1);
	}

	else {
		printf("\nTest FAILED!\n");
		printf("Value of choice1 was: %d\n", choice1);
		printResults("Number of Actions", beforeFunction.numActions, state->numActions);
		if (choice1) {
			printResults("Played Card Enum Value", minion, state->playedCards[state->playedCardCount - 1]);
			printResults("Number of Coins", beforeFunction.coins, state->coins);
			printResults("Hand Count Current Player", beforeFunction.handCount[currentPlayer], 
				state->handCount[currentPlayer]);
		}

		else {
			printResults("Played Card Enum Value", minion, state->playedCards[0]);
			printResults("Hand Count Current Player", beforeFunction.handCount[currentPlayer], 
				state->handCount[currentPlayer]);
			for (int playerNum = 0; playerNum < numPlayer; playerNum++) {
				if (playerNum != currentPlayer) {
					printResults("Hand Count of Other Player", beforeFunction.handCount[playerNum],
						state->handCount[playerNum]);
				}
			}

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