#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/*
$ echo > b
$ mkdir a
$ echo > a/b
$ find . b
./b
./a/b
*/

char*
fmtname(char *path)
{
    static char buf[DIRSIZ+1];
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if(strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf+strlen(p), '\0', 1);  //change here
    return buf;
}

void 
find(char *path,char *destination) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return ;
    }
    if(fstat(fd,&st) < 0) { //获取文件目录以及状态
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return ;
    }
    strcpy(buf, path);

    switch(st.type) {
    case T_FILE:
        if(strcmp(fmtname(buf),destination) == 0)
            printf("%s\n",buf);
        break;

    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';// *p = '/' , p = p + 1
        //读取文件输入，多个文件名可多次读取
        while(read(fd, &de, sizeof(de)) == sizeof(de)) {
            if(de.inum == 0)
                continue;

            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            if(stat(buf, &st) < 0) {
                printf("find: cannot stat %s\n", buf);
                continue;
            }
            if(strcmp(fmtname(buf),".") == 0 || strcmp(fmtname(buf),"..") == 0)
                continue;
            find(buf, destination);
        }
        break;
    }
    close(fd);
}


int 
main(int argc,char *argv[]) {
    if(argc < 3) {
        printf("find error\n");
        exit(1);
    }
    find(argv[1],argv[2]);
    exit(0);
}