#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>

struct sockinfo
{
    int fd;
    pthread_t tid;
    struct sockaddr_in addr;
};

struct sockinfo sockinfos[128];

void *working(void * arg){

        struct sockinfo *pinfo=(struct sockinfo *)arg;
        char cliIp[16];
        inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
        unsigned short cliPort = ntohs(pinfo->addr.sin_port);

        printf("client ip is : %s, prot is %d \n", cliIp, cliPort);
        char recvBuf[1024]={0};
        while(1){
            int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));

            if(len == -1){
                perror("read");
                exit(-1);
            }else if(len > 0){
                printf("revv client data : %s \n",recvBuf);
            }else{
                printf("client connect closed\n");
                break;
            }

            write(pinfo->fd, recvBuf, strlen(recvBuf)+1);
        }
        close(pinfo->fd);
        exit(0);

}
int main(){
    

    //注册信号捕捉

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

    int max= sizeof(sockinfos)/sizeof(sockinfos[0]);
    for(int i=0;i<max;i++){
        bzero(&sockinfos[i],sizeof(sockinfos[i]));
        sockinfos[i].fd=-1;
        sockinfos[i].tid=-1;
    }

    while (1)
    {   
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        
        /* code */
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
        
        struct sockinfo * pinfo;
        for(int i=0;i<max;i++){
            if(sockinfos[i].fd == -1){
                pinfo = &sockinfos[i];
                break;
            }
            if(i==max-1){
                sleep(1);i=0;
            }
        }
        pinfo->fd=cfd;
        memcpy(&pinfo->addr,&cliaddr,len);

        
        pthread_create(&pinfo->tid, NULL,working, pinfo);

        pthread_detach(pinfo->tid);


    }

    close(lfd);
    
}