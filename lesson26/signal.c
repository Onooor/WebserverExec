/*
    #include <signal.h>
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
        - 功能：设置某个信号的捕捉行为
        - 参数：
            - signum: 要捕捉的信号
            - handler: 捕捉到信号要如何处理
                - SIG_IGN ： 忽略信号
                - SIG_DFL ： 使用信号默认的行为
                - 回调函数 :  这个函数是内核调用，程序员只负责写，捕捉到信号后如何去处理信号。
                回调函数：
                    - 需要程序员实现，提前准备好的，函数的类型根据实际需求，看函数指针的定义
                    - 不是程序员调用，而是当信号产生，由内核调用
                    - 函数指针是实现回调的手段，函数实现之后，将函数名放到函数指针的位置就可以了。

        - 返回值：
            成功，返回上一次注册的信号处理函数的地址。第一次调用返回NULL
            失败，返回SIG_ERR，设置错误号
            
    SIGKILL SIGSTOP不能被捕捉，不能被忽略。
*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myalarm(int num){
    static int i=1;
    printf("gianal:%d\n",i++);
    printf("XXXXXXXXXX\n");
}

int main() {

    //注册信号捕捉
    // typedef void (*sighandler_t)(int); 函数指针

    // sighandler_t ret=
    signal(SIGALRM,myalarm);
    // if(ret==SIG_ERR){
    //     perror("signal");
    // }

    struct itimerval new_value;
    new_value.it_interval.tv_sec=2;
    new_value.it_interval.tv_usec=0;

    new_value.it_value.tv_sec=3;
    new_value.it_value.tv_usec=0;
    
    int ret=setitimer(ITIMER_REAL, &new_value, NULL);
    printf("定时器开始了\n");



    if(ret==-1){
        perror("s2titimer");
    }
    getchar();



    return 0;
}