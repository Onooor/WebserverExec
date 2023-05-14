#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid=fork();
    if(pid>0){
        printf("pid : %d\n",pid);
        printf("i am parent process,pid : %d,ppid : %d\n",getpid(),getppid());
    }else if(pid==0){
        printf("pid : %d\n",pid);
        printf("i am parent child,pid : %d,ppid : %d\n",getpid(),getppid());

    }

    for(int i=0;i<5;i++){
        printf("I: %d\n",i);
        sleep(1);
    }
    return 0;
}