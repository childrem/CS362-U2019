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


void testTributeCard(struct gameState *state, int currentPlayer, int nextPlayer, int* tributeRevealedCards) {

	// Preserve pre-function state

	struct gameState beforeFunction;

	memcpy(&beforeFunction, state, sizeof(struct gameState));

	// Call function to test

	tributeEffect(state, currentPlayer, nextPlayer, tributeRevealedCards);

	// Change the pre-state in the way we expect minionEffect to change the actual code

	if ((beforeFunction.discardCount[nextPlayer] + beforeFunction.deckCount[nextPlayer]) <= 1) {

		if (beforeFunction.deckCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = beforeFunction.deck[nextPlayer][beforeFunction.deckCount[nextPlayer] - 1];
			beforeFunction.deckCount[nextPlayer]--;
		}

		else if (beforeFunction.discardCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = beforeFunction.discard[nextPlayer][beforeFunction.discardCount[nextPlayer] - 1];
		}

	}

	else {

		if (beforeFunction.deckCount[nextPlayer] < 2) {

			moveFromDiscardToDeck(&beforeFunction, nextPlayer);	// Move cards from discard pile to the deck


			// Deck is shuffled by the function, we have to trust the results of shuffle fxn because of RNG

			for (int deckPosition = 0; deckPosition < state->deckCount[nextPlayer]; deckPosition++) {
				beforeFunction.deck[nextPlayer][deckPosition] = state->deck[nextPlayer][deckPosition];
			}

		}

		tributeRevealedCards[0] = beforeFunction.deck[nextPlayer][beforeFunction.deckCount[nextPlayer] - 1];
		beforeFunction.deck[nextPlayer][beforeFunction.deckCount[nextPlayer] - 1] = -1;
		tributeRevealedCards[1] = beforeFunction.deck[nextPlayer][beforeFunction.deckCount[nextPlayer] - 2];
		beforeFunction.deck[nextPlayer][beforeFunction.deckCount[nextPlayer] - 2] = -1;
		beforeFunction.deckCount[nextPlayer] -= 2;
	}

	if (tributeRevealedCards[0] == tributeRevealedCards[1]) {//If we have a duplicate card, just drop one 
		// CALL NEW FXN HERE TO ADD THIS CARD TO DISCARD PILE OF "NEXT PLAYER"
		addToDiscardCards(&beforeFunction, nextPlayer, tributeRevealedCards[1]);
		tributeRevealedCards[1] = -1;
	}

	for (int i = 0; i <= 2; i++) {

		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) {//Treasure cards
			beforeFunction.coins += 2;
			// CALL NEW FXN HERE TO ADD THIS CARD TO DISCARD PILE OF "NEXT PLAYER"
			addToDiscardCards(&beforeFunction, nextPlayer, tributeRevealedCards[i]);
		}

		else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) {//Victory Card Found
			
			// Current player draws 2 cards which potentially involves RNG. Need to trust results
			
			for (int handPosition = 0; handPosition < state->handCount[currentPlayer]; handPosition++) {
				beforeFunction.hand[currentPlayer][handPosition] = state->hand[currentPlayer][handPosition];
			}

			// CALL NEW FXN HERE TO ADD THIS CARD TO DISCARD PILE OF "NEXT PLAYER"
			addToDiscardCards(&beforeFunction, nextPlayer, tributeRevealedCards[i]);
		}
		else {//Action Card
			if (tributeRevealedCards[i] != -1) {
				beforeFunction.numActions = beforeFunction.numActions + 2;
				// CALL NEW FXN HERE TO ADD THIS CARD TO DISCARD PILE OF "NEXT PLAYER"
				addToDiscardCards(&beforeFunction, nextPlayer, tributeRevealedCards[i]);
			}
		}
	}

	if (memcmp(&beforeFunction, state, sizeof(struct gameState)) == 0) {
		printf("\nTest PASSED!\n");
	}

	else {
		printf("\nTest FAILED!\n");
	}


}

/*

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

*/

int main() {

	unsigned seed;         // srand expects an unsigned integer
	seed = time(0);        // seed set to changing value of time
	srand(seed);           // initiating seed in srand

	//int seed = 1000;
	int numPlayer = 4;

	int currentPlayer;
	int nextPlayer;

	int tributeRevealedCards[2] = { -1,-1 };	// enum values set by tributeEffect function

	//int handPos;
	int handCount;		// Number of cards each player has
	int deckCount;		// Number of cards in each player's deck
	int discardCount;	// Number of cards in each player's discard pile


	int k[10] = { minion, ambassador, tribute, gardens, mine,
				 remodel, smithy, village, baron, great_hall };

	struct gameState G;

	//tributeEffect(struct gameState *state, int currentPlayer, int nextPlayer, int* tributeRevealedCards)


	printf("Testing function tributeEffect() with RANDOM TESTS!\n");



	// Change statement numTest < # to change number of tests run

	for (int numTest = 0; numTest < 10; numTest++) {
		memset(&G, 23, sizeof(struct gameState));	// Clear previous gamestate
		initializeGame(numPlayer, k, seed, &G);		// Initialize a normal game

		// Start randomizing the necessary member variables that tributeEffect uses


		currentPlayer = randomNumber(0, 3);	// Random value between 0 and 3
		G.whoseTurn = currentPlayer;		// Have to let it know whose turn it is (player playing the card)

		if (currentPlayer == numPlayer - 1) {
			nextPlayer = 0;
		}

		else {
			nextPlayer = currentPlayer + 1;
		}


		for (int playerNum = 0; playerNum < numPlayer; playerNum++) {

			handCount = randomNumber(1, MAX_HAND);

			G.handCount[playerNum] = handCount;

			// We need to make sure all player's have hands so we don't seg fault because players don't get
			// hands until their turn comes up

			for (int handPosition = 0; handPosition < handCount; handPosition++) {
				G.hand[playerNum][handPosition] = randomNumber(0, 26);		
				// Each hand is totally randomized in size and what cards are present
			}

			if (playerNum == currentPlayer) {
				int handPos = randomNumber(0, handCount);	// Position of the minion card itself
				G.hand[playerNum][handPos] = tribute;		// Force a tribute into the hand
			}

			deckCount = randomNumber(0, MAX_DECK);
			discardCount = randomNumber(0, MAX_DECK);

			G.deckCount[playerNum] = deckCount;
			G.discardCount[playerNum] = discardCount;

			for (int deckPosition = 0; deckPosition < deckCount; deckPosition++) {
				G.deck[playerNum][deckPosition] = randomNumber(0, 26);
				// Each player's deck is totally random in size and what cards are present
			}

			for (int discardPosition = 0; discardPosition < discardCount; discardPosition++) {
				G.discard[playerNum][discardPosition] = randomNumber(0, 26);
				// Each player's discard pile is totally random in size and what cards are present
			}

		}


		testTributeCard(&G, currentPlayer, nextPlayer, tributeRevealedCards);



	}


	return 0;
}