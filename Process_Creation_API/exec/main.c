#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv [])
{

  printf("Initial PID: %d \n", getpid());
  fflush(stdout);

  int rc = fork ();
  if (rc < 0){
    printf("Fork failed \n");
    exit (1);
  }
  else if (rc == 0){
    // Child Process
    fflush(stdout);
    char * myargs[3];

    myargs[0] = strdup("wc");   // program: "wc" (word count)
    myargs[1] = strdup("p2.c"); // argument: file to c ount
    myargs[2] = NULL;           // marks end of array

    execvp(myargs[0], myargs); // run word count

    printf(" This shouldn't print out \n");

  }
  else {
    // Parent Process

    int wc = wait (NULL);

    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
}

return 0;

}
