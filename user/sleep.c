//#include "ulib.c"
//#include "kernel/stat.h"
#include "kernel/types.h" //6 编译顺序
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc == 1) {
      write(1,"sleep error\n",strlen("sleep error\n"));
      exit(-1);
  }

  int n = atoi(argv[1]);
  sleep(n);
  exit(0);
}
