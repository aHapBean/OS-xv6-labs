#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char *argv[]) {
    if(argc == 1) {
        write(1,"copy error\n",strlen("copy error\n"));
        exit(1);
    }
    //int nd;
    //char buf[200];
    //while((nd = read(0, buf, 200)) != 0) {
    //    write(1,buf,nd);
    //}
    //char buf[100];
    int n = strlen(argv[1]);
    write(1,argv[1],n);
    exit(0);
}