#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
//echo hello too | xargs echo bye
//    bye hello too
// echo "1\n2" | xargs echo line
//echo "1\n2" | xargs -n 1 echo line
//他那个什么意思
/*
filename -> read -> exec(cat...) -> continue
*/
int 
main(int argc,char *argv[]) {
    char buf[2000];  //buf max is 200 ? 
    int n;
    char _char;
    char *tail = buf;
    
    //特殊处理
    int flag = 0;
    if(strcmp(argv[1],"-n") == 0) {
        flag = 1;
    }
    char *my_argv[MAXARG];
    for(int i = 0; i < argc; ++i)
        my_argv[i] = argv[i];
    if(flag) {
        for(int i = 1; i < argc - 2; ++i)
            my_argv[i] = my_argv[i + 2];    //please attention the pointer !
        argc -= 2;
    }

    //get the exe file name
    char exec_name[10];//最长操作名?
    strcpy(exec_name, my_argv[1]);
    char exe_file[] = "./";
    char *file_tail = exe_file + strlen(exe_file);
    for(int i = 0; i < strlen(exec_name); ++i) {
        *file_tail++ = exec_name[i];
    }
    *file_tail = 0;


    while((n = read(0,&_char,1)) == 1) {
        if(_char != '\\' && _char != '\n') {    // \n & \n ????
            if(_char == '"') continue;
            *tail++ = _char;continue;
        }
        if(_char == '\\') {
            int n = read(0,&_char,1);
            if(n == 0);
            else if(_char != 'n') {// BUG EOF !!!
                *tail++ = '\\';
                *tail++ = _char;
                continue;
            }
        }

        *tail = 0;
        if(fork() == 0) {
            //update parameter
            char *new_argv[MAXARG];
            for(int i = 1; i < argc; ++i) {
                new_argv[i - 1] = my_argv[i];
            }
            new_argv[argc - 1] = buf;
            new_argv[argc] = 0;
            exec(exe_file, new_argv);

            printf("exec xargs failed\n");
            exit(1);
        } else {
            wait(0);
            tail = buf; //update buf
        }
    }
    if(n < 0) printf("error for the argument is too long\n");
    exit(0);
}