#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main(){

    int ret=access("fifo1",F_OK);
    if(ret==-1){
        printf("管道文件不存在,创建对应的管道文件\n");

        ret = mkfifo("fifo1",0664);
        if(ret==-1){
            perror("mkfifo1");
            exit(0);
        }

    }

    ret=access("fifo2",F_OK);
    if(ret==-1){
        printf("管道文件不存在,创建对应的管道文件\n");

        ret = mkfifo("fifo2",0664);
        if(ret==-1){
            perror("mkfifo2");
            exit(0);
        }
    }

        int fdr=open("fifo1",O_RDONLY);
    if(fdr==-1){
        perror("open");
        exit(0);
    }
    printf("打开fifo1成功,等待写入...\n");

    int fdw=open("fifo2",O_WRONLY);
    if(fdw==-1){
        perror("open");
        exit(0);
    }
    printf("打开fifo2成功,等待写入...\n");



    char buf[128];
    while(1){
                memset(buf,0,128);
        ret=read(fdr,buf,128);
        if(ret<=0){
            perror("read");
            exit(0);
        }
        printf("buf: %s\n",buf);



        memset(buf,0,128);

        fgets(buf,128,stdin);

        ret=write(fdw,buf,strlen(buf));
        if(ret==-1){
            perror("write");
            exit(0);
        }


    }


        close(fdw);
        close(fdr);
    return 0;

}