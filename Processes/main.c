/*
    - This file uses structure of xv6 Proc Structure to understand how OS uses data structures to keep a track of
      processes and their current state.
*/


struct context {

  int eip;
  int esp;
  int ebx;
  int ecx;
  int edx;
  int esi;
  int edi;
  int edp;
};


enum process_state = { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };


struct process {

  char *memory;                   // Start of process memory
  uint size;                      //   Size of process memory
  char * kstack;                  //  Bottom of Kernel Stack
  enum process_state state;       // Process State
  int pid;                        // current process ID
  struct proc *parent;            // Parent of current process

  void *chan;                     // if !zero, sleeping on chan
  int killed;                     // if !zero, has been killed

  struct file *ofile[NOFILE];     // open files
  struct inode *cwd;              // current directory
  struct context contexxt;        // switch heere to run process
  struct trapframe *tf;           // Trap Frame for the current Interrupt


};
