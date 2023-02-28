#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int 
isPrime(int num) {
    if(num == 1) return 0;
    for(int i = 2; i * i <= num; ++i)
        if(num % i == 0) return 0;
    return 1;
}

int 
main() {
    int cur = 2;
    int fd[2];
    int pid;
    int res;
    pipe(fd);
    pid = fork();
    // 0 read 1 write
    if(pid > 0) {
        close(fd[0]);
        write(fd[1], &cur, 4);
        close(fd[1]);
    }
    if(pid == 0) {
        close(fd[1]);
        read(fd[0], &res, 4);
        close(fd[0]);
        printf("Prime %d\n",res);
    }
    cur += 1;
    int status;
    wait(&status);
    for(; cur < 35; ++cur) {
        if(pid > 0) break;
        if(!isPrime(cur)) continue;
        //printf("%d\n",cur);
        pipe(fd);
        pid = fork();
        if(pid == 0) {
            close(fd[1]);
            read(fd[0], &res, 4);
            printf("Prime %d\n",res);
        } else {
            int status;
            close(fd[0]);
            write(fd[1], &cur, 4);
            wait(&status);
            break;
        }
    }
    exit(0);
}