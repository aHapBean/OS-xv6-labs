//#include "ulib.c"
//#include "kernel/stat.h"
/*
#include "user/user.h"

#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/defs.h"
#include "kernel/date.h"
#include "kernel/param.h"
#include "kernel/memlayout.h"
#include "kernel/spinlock.h"
#include "kernel/proc.h"

int
main(int argc, char *argv[])
{
    //int i;
    if(argc == 1) {
        write(1,"sleep error\n",strlen("sleep error\n"));
        exit(-1);
    }

    int n = atoi(argv[1]);
    int ticks0;
    write(1, argv[1], strlen(argv[1]));
    write(1, "\n", 1);
    acquire(&tickslock);
    ticks0 = ticks; // where is ticks ??
    while(ticks - ticks0 < n) {
       if(myproc()->killed) {
           release(&tickslock);
           exit(-1);
       }
       sleep(&ticks, &tickslock);
    
    release(&tickslock);
    exit(0);
}
*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;

  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i])); //1 is standard output
    if(i + 1 < argc){ //complement the output !
      write(1, " ", 1);
    } else {
      write(1, "\n", 1);
    }
  }
  exit(0);
}
