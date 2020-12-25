#include <stdio.h>
#include <stdlib.h>
#include "./common.h"
#include "common_threads.h"


volatile int counter  = 0;
volatile int loops;

void *worker (void *args)
{
  int i;
  for(i = 0; i < loops; i++)
  {
    counter++;
  }
  return NULL;
}
/***********************************************************************************************************************************************

Description:

  * We run this program with the input value for the variable loops set to 1000.
    The value of loops determines how many times each of the two workers will increment the shared counter in a loop.

  * when we gave an input value of 100,000, instead of getting a final value of 200,000, we instead first get 143,012.
    Then, when we run the program a second time, we not only again get the wrong value, but also a different value than the last time.
    In fact, if you run the program over and over with high values of loops, you may find that sometimes you even get the right answer!
    So, why is this happening?

      * As it turns out, the reason for these odd and unusual outcomes relate to how instructions are executed, which is one at a time.
        Unfortunately, a key part of the program above, where the shared counter is incremented, takes three instructions:
            1. one to load the value of the counter from memory into a register,
            2. one to increment it,
            3. and one to store it back into memory.
        Because these three instructions do not execute atomically (all at once), strange things can happen.

***********************************************************************************************************************************************/

int main (int argc, char* argv [])
{
  if (argc != 2){
    printf("Invalid Input");
    exit(1);
  }

  loops = atoi(argv[1]);
  pthread_t p1, p2;
  printf("Initial value of counter: %d \n", counter);

  Pthread_create(&p1, NULL, worker, NULL);
  Pthread_create(&p2, NULL, worker, NULL);

  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);

  printf("final Value of counter: %d \n", counter );

  return 0;

}
