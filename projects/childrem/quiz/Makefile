# Michael Childress
# CS 362 Software Engineering II
# Random Testing Quiz


CFLAGS= -Wall -fpic -coverage -lm -std=c99


quiz: testme.c
	gcc -o testme testme.c $(CFLAGS)
	-testme >> testmeResults.out
	gcov testme.c -b -f >> testmeCoverage.out

clean:
	rm -f testme *.out *.gcov *.gcda *.gcno *.so
