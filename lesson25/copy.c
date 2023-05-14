// 使用内存映射实现文件拷贝的功能
/*
    思路：
        1.对原始的文件进行内存映射
        2.创建一个新文件（拓展该文件）
        3.把新文件的数据映射到内存中
        4.通过内存拷贝将第一个文件的内存数据拷贝到新的文件内存中
        5.释放资源
*/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    // 1.对原始的文件进行内存映射
    int fd1 = open("english.txt", O_RDWR);
    if(fd1==-1){
        perror("open");
        exit(0);
    }
    
    // 获取原始文件的大小
    int len = lseek(fd1, 0, SEEK_END);


    // 2.创建一个新文件（拓展该文件）
    int fd2=open("copy.txt",O_RDWR | O_CREAT,0664);
    if(fd2==-1){
        perror("create");
        exit(0);
    }
    
    
    // 对新创建的文件进行拓展
    truncate("copy.txt",len);
    write(fd2, " ",1);
    // 3.分别做内存映射
    void * ptr1=mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);
    void * ptr2=mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);
    if(ptr1==MAP_FAILED||ptr2==MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    // 内存拷贝
    memcpy(ptr2,ptr1,len);


    // 释放资源
    munmap(ptr2,len);
    munmap(ptr1,len);

    close(fd2);
    close(fd1);
    return 0;

}