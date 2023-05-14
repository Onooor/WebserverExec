/*
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);
            参数:
                - fd : 文件描述符,open得到的,可以通过这个文件描述符操作某个文件
                - buf : 需要读取数据存放的地方,数组的地址(传出参数)
                - count : 指定的数组的大小
            返回值
                - 成功 :
                    >0: 返回实际读取到的字节数
                    =0: 文件已经读取完了
                - 失败 : 
                    -1: 并且设置errno


       ssize_t write(int fd, const void *buf, size_t count);
            参数:
                - fd : 文件描述符,open得到的,可以通过这个文件描述符操作某个文件
                - buf : 需要往磁盘写入数据的地方
                - count : 指定的数组的大小
            返回值
                - 成功 :
                    >0: 返回实际写入到的字节数
                    =0: 文件已经写完了
                - 失败 : 
                    -1: 并且设置errno
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    //打开
    int srcfd=open("english.txt",O_RDONLY);
    if(srcfd==-1){
        perror("open");
        return -1;
    }


    //创建
    int fd=open("cpy.txt",O_WRONLY|O_CREAT,0664);
    if(fd==-1){
        perror("open");
        return -1;
    }

    //读写
    char buf[1024]={0};
    int len=0;
    while((len=read(srcfd,buf,sizeof(buf)))>0)
        write(fd,buf,len);
    
    close(fd);
    close(srcfd);
    
    //关闭
    return -1;
}