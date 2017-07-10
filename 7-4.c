#include "apue.h"
#include <setjmp.h>
#define TOK_ADD 5

jmp_buf jmpbuffer;

void do_line(char *);
void cmd_add(void);
int get_token(void);

int main(void)
{
    char line[MAXLINE];
    if(setjmp(jmpbuffer)!=0)/*在希望返回的位置调用setjmp(),直接调用，返回值是０*/
        printf("error!");
    while(fgets(line,MAXLINE,stdin)!=NULL)
        do_line(line);
    exit(0);
}

char *tok_ptr; /* global pointer for get_token()*/
void do_line(char *ptr)
{
    int cmd;
    while((cmd=get_token())>0)
    {
        switch (cmd)
        {
            case TOK_ADD:
                cmd_add();
                break;
        }
    }     
}

void cmd_add(void)
{
    int token;
    token = get_token();     
    if(token<0)
        longjmp(jmpbuffer,1);/*当检查到一个错误的时候，调用ｌｏｎｇｊｍｐ(),参数１为ｅｎｖ,参数２为非０值，作为ｓｅｔｊｍｐ的返回值，用来确定是哪个栈帧返回的s*/
}

int get_token(void)
{

}