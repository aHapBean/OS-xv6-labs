#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//前向素数筛，巧妙
void 
solve(int fd[]) {
    int res;
    close(fd[1]);
    read(fd[0], &res, 4);
    printf("prime %d\n",res);
    int cur;
    int pid;
    int status;
    int flag = read(fd[0], &cur, 4);    //巧
    if(flag > 0) {
        int new_fd[2];
        pipe(new_fd);
        pid = fork();
        if(pid > 0) {
            close(new_fd[0]);
            if(cur % res != 0) write(new_fd[1], &cur, 4);
            while(read(fd[0], &cur, 4))
                if(cur % res != 0) write(new_fd[1], &cur, 4);
            close(fd[0]);
            close(new_fd[1]);
            wait(&status);
        } else {
            solve(new_fd);//由于for的层数不确定，故用递归函数替代
        }
    }
    exit(0);
}

int 
main() {
    int cur = 2;
    int fd[2];
    int pid;
    int status;
    pipe(fd);
    pid = fork();
    if(pid > 0) {
        close(fd[0]);
        for(; cur <= 35; ++cur)
            write(fd[1], &cur, 4);
        close(fd[1]);
        wait(&status);
    } else {
        solve(fd);
    }
    exit(0);
}