#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
//echo hello too | xargs echo bye
//    bye hello too


int 
main(int argc,char *argv[]) {
    char buf[200];  //buf max is 200 ? 
    int n;
    char _char;
    while((n = read(0, buf, 200)) > 0);
    while((n = read(0,_char,1)) == 1) {
        
    }
    if(n < 0) printf("error for the argument is too long\n");

    char *tail = buf + strlen(buf);
    if(*(--tail) == '\n') *tail = 0;
    else ++tail;

    char exec_name[10];//最长操作名?
    strcpy(exec_name, argv[1]);
    
    char exe_file[] = "./";
    char *file_tail = exe_file + strlen(exe_file);
    for(int i = 0; i < strlen(exec_name); ++i) {
        *file_tail++ = exec_name[i];
    }
    *file_tail = 0;

    //更新参数
    char *new_argv[MAXARG]; //最大参数个数
    for(int i = 1; i < argc; ++i) {
        new_argv[i - 1] = argv[i];
    }
    new_argv[argc - 1] = buf;
    new_argv[argc] = 0;
    exec(exe_file, new_argv);

    printf("exec xargs failed\n");
    exit(0);
}