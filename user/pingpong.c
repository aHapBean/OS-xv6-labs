#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define debug //write(1,"debug here\n",strlen("debug here\n"));

char *
to_string(int pid) {
    char ret[10];
    if(pid > 1e9) {
        write(1,"fork false\n",strlen("fork false\n"));
        exit(1);
    }
    int cur = 0;
    static char ans[10];
    if(pid == 0) {
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }
    while(pid > 0) {
        int tmp = pid % 10;
        ret[cur++] = tmp + '0';
        pid /= 10;
    }
    for(int i = 0; i < cur; ++i)
        ans[i] = ret[cur - 1 - i];
    ans[cur] = '\0';
    return ans;
}
// f[0] 读
// f[1] 写
int
main(int argc, char *argv[]) {
    int fd1[2];
    int fd2[2];
    if(argc != 1) {
        write(1, "ping pong error\n",strlen("ping pong error\n"));
        exit(-1);
    }

    char buf[10];
    pipe(fd1);  // parent -> son    先开辟管道
    pipe(fd2);  // son -> parent
    int pid = fork();
    if(pid == 0) {  //子进程
        close(fd1[1]);   //关闭写
        read(fd1[0],buf,sizeof(buf));    //阻塞

        //收到
        pid = getpid();
        printf("%d: received ping\n",pid);
        //发送
        close(fd2[0]);  //关闭读端
        write(fd2[1],buf,strlen(buf));
        exit(0);
    } else {    //父进程
        close(fd1[0]);   //关闭读
        debug
        write(fd1[1], "b",strlen("b"));


        close(fd2[1]);  //关闭写
        read(fd2[0],buf,sizeof(buf));
        
        pid = getpid(); //得到当前进程吗???为什么是4 3 ??
        printf("%d: received pong\n",pid);
        exit(0);
    }
    exit(0);
}
/*
0 读 
1 写

1.开辟管道 利用阻塞机制
读管道的数据时，如果管道中没有数据，就会唤醒写管道的进程，而读管道进程进入睡眠状态；如果读到了管道数据，就相应地调整管道的头（写）指针，并把数据从内核态的缓冲区拷贝到用户态的应用程序缓冲区中。当然，读管道进程如果将管道数据全部取走后，也需要唤醒等待在写管道的进程。

2.fork

3.得到pid

*/