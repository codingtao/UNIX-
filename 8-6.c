#include "apue.h"

static void charatatime(char *);

int main()
{
    pid_t pid;
    //TELL_WAIT();

    if((pid=fork())<0)
        err_sys("fork error");
    else if(pid==0){
       // WAIT_PARENT();
        charatatime("output from child\n");
    }else{
        charatatime("output from parent\n");    
        //TELL_CHILD(pid);
    }
    exit(0);
}

static void charatatime(char *str)
{
    char *ptr;
    int c;
    setbuf(stdout,NULL);// 设置为不带缓冲的输出
    for(ptr=str;(c=*ptr++)!=0;)
        putc(c,stdout);
}