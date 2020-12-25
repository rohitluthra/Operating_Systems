#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


/*
Description:

    - To accomplish this task, the program makes three calls into the operating system a call to :->
        1. open(), opens the file and creates it;
        2. write(), writes some data to the file;
        3. close(), simply closes the file thus indicating the program won’t be writing any more data to it.

    - These system calls are routed to the part of the operating system called the file system, which then handles
      the requests and returns some kind of error code to the user.

    - You might be wondering what the OS does in order to actually write to disk.
        - The file system has to do a fair bit of work:
            - first figuring out where on disk this new data will reside,
            - then keeping track of it in various structures the file system maintains.
        - Doing so requires issuing I/O requests to the underlying storage device, to either read existing structures or update (write) them.
          As anyone who has written a device driver knows, getting a device to do something on your behalf is an intricate and detailed process.
          It requires a deep knowledge of the low-level device interface and its exact semantics. Fortunately, the OS provides a standard and
          simple way to access devices through its system calls.

    - Thus, the OS is sometimes seen as a standard library.
*/
int main(int argc, char* argv[])
{

  /*
    - O_WRONLY  -> Open for writing only.
    - O_CREAT   -> Creating a file, If not created then create one and set permission bits accordingly.
    - O_TRUNC   -> If the file exists and is a regular file, and the file is successfully opened O_RDWR or O_WRONLY
    - S_IRUSR   -> Read permission bit for the owner of the file. On many systems this bit is 0400.
    - S_IWUSR   -> Write permission bit for the owner of the file. Usually 0200.
  */

  int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  assert (fd >= 0);

  char buffer[40];

   /* function int sprintf(char *str, const char *format, ...) sends formatted output to a string pointed to, by str */

  sprintf(buffer, "This string will go in buffer");

  int rc = write(fd, buffer, strlen(buffer));

  assert( rc == (strlen(buffer)));

  /*
    - fsync() transfers ("flushes") all modified in-core data of the file referred to by the file descriptor fd to the disk device
      (or other permanent storage device) so that all changed information can be retrieved even if the system crashes or is rebooted.
      This includes writing through or flushing a disk cache if present.

    - The call blocks until the device reports that the transfer has completed.
  */
  fsync(fd);

  close(fd);

  return 0;


}
