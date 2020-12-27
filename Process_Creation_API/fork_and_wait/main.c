#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv [])
{

  /*
  What is fflush ?

  printf("Enter a number: ");   // print won't appear on console
  printf("Enter a number:\n");  // with \n, it does show on console.

  - The reason for this is that the output to stdout is buffered by the OS and the default behavior is (often) only to actually
  write the output to the terminal when a newline is encountered.

  - Adding an fflush(stdout) after the printf() solves the problem:
  */
  fflush (stdout);
  printf("Initial (pid:%d)\n", (int)getpid());

  int rc = fork() ;
  if (rc < 0)
  {
    // fork has failed
    printf("Fork has Failed \n");
    exit (1);
  }
  else if (rc == 0)
  {
    // You are in child Process
    printf("Child process successfully created , it's PID is : %d \n", getpid());
  }
  else{

    int rc_wait = wait(NULL); // Waits for any child process to finish before continuing.

    // Parent process entry path
    printf("Child: %d, rc_wait: %d  (Parent Pid: %d)",rc, rc_wait, getpid());
  }

  return 0;
}
