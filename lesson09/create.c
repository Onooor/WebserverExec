/*
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

       
        //创建一个新的文件
       int open(const char *pathname, int flags, mode_t mode);
            参数
            -pathname:要创建的文件路径
            -flags:文件的操作权限和其他设置
                -必选项:O_RDONLY O_WRONLY O_RDWR 这三个是互斥的
                -可选项:O_CREAT 文件不存在,创建新文件
            - mode: 八进制的数,表示创建出新的文件的操作权限,比如:0775
            最终的权限是:mode & ~umask //0002
            0777  -> 111111111
        &   0775  -> 111111101
        ==========================
                     111111101
        按位与:0和任何数都为0

        umask作用就是抹去某些权限.

        flag参数是一个int类型数据,占四个字节,32位
        flag 32位,每一个位就是一个标志位
        


*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    int fd=open("create.txt",O_RDWR|O_CREAT,0777);
    if(fd==-1){
        perror("open");
    }

    close(fd);
    return 0;
}