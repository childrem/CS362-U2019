#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


#define MAXHANDCOUNT 5

void printResult() {


}



void testBaronCard(int choice1, struct gameState *state, int currentPlayer) {

	// Preserver pre-function state

	// Call function to test

	// Implement Assertions


}


int main() {
	int seed = 1000;
	int numPlayer = 2;

	int currentPlayer;

	int choice1;

	int cardForHand;	// Randomize what card is filling the player's hand each time a test is run

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

		// Start randomizing the necessary member variables that baronEffect uses, but keep them in
		// ranges that would be possible for a normal game

		choice1 = floor(Random() * 2);		// Random value between 0 and 1
		
		currentPlayer = floor(Random() * 2);	// Random value between 0 and 1

		G.supplyCount[estate] = floor(Random() * 9);	// Valid values are from 0-8 in a game with 2 players

		// 0-26 are valid enum values of cards in the game

		cardForHand = floor(Random() * 27);

		// ALL cards in the player's hand are that one randomly determined card type

		for (int handPosition = 0; handPosition < MAXHANDCOUNT; handPosition++) {
			G.hand[currentPlayer][handPosition] = cardForHand;
		}

		G.handCount[currentPlayer] = 5;

		testBaronCard(choice1, &G, currentPlayer);

	}


	return 0;
}