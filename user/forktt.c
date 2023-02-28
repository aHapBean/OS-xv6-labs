#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid,status;

    pid = fork();
    //pid = fork();奇怪
    if(pid == 0) {
        //Unix提供了一个wait系统调用，如第20行所示。wait会等待之前创建的子进程退出。
        //1.9讲了
        char *argv[] = {"echo","this IS ECHO","\0"};
        exec("echo",argv);
        printf("exec failed!\n");
        exit(1);
    } else {
        printf("parent waiting!\n");
        // 中途不会转到child去吗
        //int status2;
        wait(&status);
        printf("child over with status %d %d\n",status);
    }
    exit(0);
}