#include "apue.h"
#include <pthread.h>

int quitflag; /*set nonzero by thread*/
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg)
{
    printf("pthread begin:\n");
    int err,signo;

    for(;;){
        err = sigwait(&mask,&signo);
        if(err!=0)
            err_exit(err,"sigwait failed");
        switch(signo){
        case SIGINT:
            printf("\ninterrupt\n");
            break;
        case SIGQUIT:
            pthread_mutex_lock(&lock);
            quitflag = 1;
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&wait);/* 唤醒等待该条件的某个线程*/
            return (0);
        default:
            printf("unexpected signal %d\n",signo);
            exit(1);
        }
    }
}

int main(void)
{
    int err;
    sigset_t oldmask;
    pthread_t tid;

    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGQUIT);

    if((err=pthread_sigmask(SIG_BLOCK,&mask,&oldmask))!=0)
        err_exit(err,"SIG_BLOCK error");

    printf("begin\n");
    err = pthread_create(&tid,NULL,thr_fn,0);
    printf("end\n");
    
    if(err!=0)
        err_exit(err,"can't create thread");  

    pthread_mutex_lock(&lock);

    printf("here\n");
    
    while(quitflag==0){
        printf("foo\n");    
        pthread_cond_wait(&wait,&lock);
    }

      
    pthread_mutex_unlock(&lock);

    /*SIGQUIT has been caught and is now blockded ; do whatever*/ 
    quitflag = 0;
    printf("here2\n");
    
    /*reset signal mask which unblocks SIGQUIT*/
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        err_sys("SIG_SETMASK error");
    
    exit(0);
}