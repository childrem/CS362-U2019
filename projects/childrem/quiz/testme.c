// Michael Childress
// CS 362 Software Engineering II
// Random Testing Quiz


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>



char inputChar()
{

	// Generate a random character with ASCII value between 32 and 125
	// All of the necessary characters we need for our logic branches fall in this range

	int randomNumber;
	const int MIN_VALUE = 32;		// ASCII value of SPACE character
	const int MAX_VALUE = 125;		// ASCII value of } character

	randomNumber = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;


    return (char)randomNumber;			// Return the character represented by that ASCII code
}

char *inputString()
{

	// I am deciding to fix my string length to 5 letters and 1 null terminator because of how hard
	// it will be to hit the right randomization of letters to form "reset"
	// I am also going to fix the last position of the string as a null terminator
	// I am further restricting the input pool to just the letters in the word "reset" as including
	// all lowercase letters proved too difficult to achieve hitting the word reset.

	int randomNumber;
	const int MIN_VALUE = 1;			// These values will be used to determine what letter gets added
	const int MAX_VALUE = 4;	

	int stringLength = 6;

	char charToAdd;

	static char stringToReturn[6];	// Room for 5 letters and 1 null terminator

	// clear memory used by this string

	memset(stringToReturn, '\0', sizeof(stringToReturn));

	for (int stringPos = 0; stringPos < stringLength - 1; stringPos++) {

		randomNumber = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

		if (randomNumber == 1) {
			charToAdd = 'r';
		}

		else if (randomNumber == 2) {
			charToAdd = 'e';
		}

		else if (randomNumber == 3) {
			charToAdd = 's';
		}

		else if (randomNumber == 4) {
			charToAdd = 't';
		}

		stringToReturn[stringPos] = charToAdd;
	}


    return stringToReturn;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
