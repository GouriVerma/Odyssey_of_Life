#include<stdio.h>
int main(){
    int array[10];
    printf("Hex values:\n");
    for(int i=0;i<10;i++){
        printf("Address of array[%d] is %p\n",i,&array[i]);
    }
    printf("Unsigned values:\n");
    for(int i=0;i<10;i++){
        printf("Address of array[%d] is %u\n",i,&array[i]);
    }
    int a,b,c;
    printf("Hex values:\n");
    printf("Address of variable a is %p\n",&a);
    printf("Address of variable b is %p\n",&b);
    printf("Address of variable c is %p\n",&c);
    printf("Unsigned values:\n");
    printf("Address of variable a is %u\n",&a);
    printf("Address of variable b is %u\n",&b);
    printf("Address of variable c is %u\n",&c);
    return 0;
}