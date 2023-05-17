#include<stdio.h>
#include<arpa/inet.h>
int main(){

    char buf[]="192.168.123.1";
    unsigned int num = 0;
    inet_pton(AF_INET, buf, &num);
    unsigned char* p=(unsigned char*)&num;
    
    printf("%d %d %d %d \n",*p,*(p+1),*(p+2),*(p+3));
    printf("=========================\n");
    char ip[16] ="";

    const char * str = inet_ntop(AF_INET, &num, ip, 16);
    printf("%s \n", str);


    return 0;
}