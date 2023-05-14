#include<stdio.h>
int main(){
    int a=10;
#ifndef DEBUG
    printf("i am onee, i can play ganme...\n");
#endif
    for(int i=0;i<3;++i){
        printf("hello gcc!!!\n");
    }
    return 0;
}
