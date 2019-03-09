#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>

void sighandler_new(int signo, siginfo_t *psiginfo, void *pReversed)
{
    sleep(1);
    printf("receive signal %d\n", signo);
}

int main(void)
{
    sigset_t sigset, oldsigset, pending_mask;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
     //sigprocmask函数设置全程阻塞
    if(-1 == sigprocmask(SIG_BLOCK, &sigset, &oldsigset))//把旧信号集合存起来，以便恢复原状
    {   
      perror("block SIGINT error");
        exit(-1);
    }

    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sighandler_new;
    sigemptyset(&act.sa_mask);
    if(sigaction(SIGINT, &act, NULL))//注册信号
    {
        printf("install SIGINT error\n");
    }
    sleep(10);

    if(-1 == sigpending(&pending_mask))//把挂起的信号集合放入pending_mask
    {
        perror("get pending mask error");
        exit(-1);
    }
    if(sigismember(&pending_mask, SIGINT))//检测SIGINT信号是否被挂起了
    {
        printf("SIGINT is pending!\n");
    }
    //恢复旧信号集合,旧信号集合没有阻塞，故之前挂起的信号会执行(!!!此处即为SIGINT被解除阻塞)
    if(-1 == sigprocmask(SIG_SETMASK, &oldsigset, NULL))
    {
        perror("unblock signal error");
        exit(-1);
    }
    printf("signal unblocked !\n");
    sleep(10);
    return 0;
}