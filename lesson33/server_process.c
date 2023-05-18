#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<wait.h>
#include<errno.h>
void recyleChild(int arg){
    while(1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret==-1||ret==0){
            break;
        }else{
            printf("子进程 %d 被回收了\n",ret);
        }
    }
}
int main(){

    //注册信号捕捉
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    sigaction(SIGCHLD, &act, NULL);

    int lfd=socket(PF_INET, SOCK_STREAM, 0);
    if(lfd==-1){
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret==-1){
        perror("bind");
        exit(-1);
    }


    ret = listen(lfd, 128);
    if(ret==-1){
        perror("listen");
        exit(-1);
    }


    while (1)
    {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        
        /* code */
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
        if(cfd==-1){
            if(errno == EINTR){
                continue;
            }
            perror("accept");
            exit(-1);
        }
        pid_t pid = fork();
        if(pid==0){
            //子进程
            char cliIp[16];
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
            unsigned short cliPort = ntohs(cliaddr.sin_port);

            printf("client ip is : %s, prot is %d \n", cliIp, cliPort);
            char recvBuf[1024]={0};
            while(1){
                int len = read(cfd, &recvBuf, sizeof(recvBuf));

                if(len == -1){
                    perror("read");
                    exit(-1);
                }else if(len > 0){
                    printf("revv client data : %s \n",recvBuf);
                }else{
                    printf("client connect closed\n");
                    break;
                }

                write(cfd, recvBuf, strlen(recvBuf));
            }
            close(cfd);
            exit(0);
        }
    }

    close(lfd);
    

}