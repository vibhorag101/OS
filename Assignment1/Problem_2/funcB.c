#include "function.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void (*ptr)() = & funcC;
char charBin[30];
void stackModify(){
    asm volatile("pop %r10");
    asm volatile("pop %r11");
    asm volatile("push ptr");
    asm volatile("push %r10");
}
void funcB(char binString[100]){
    printf("We are in function B now\n");

    char *ptrTemp;

    char octalStrings[100][100];
    char temp[8];
    for (int i = 0; i < 8; i++)
    {
        strncpy(octalStrings[i], &binString[i * 8], 8);
    }
        for (int i = 0; i < 8; i++)
    {
        printf("octalStrings %s\n",octalStrings[i]);
    }

    for (int j = 0; j < 8; j++)
    {
        charBin[j] = strtol(octalStrings[j], &ptrTemp, 2);
    }
    for (int i = 0; i < 8; i++)
    {
        printf("charBin %d\n",charBin[i]);
    }
    
    charBin[8] =10;
    register char *arg2 asm("rsi") = charBin;
    asm("mov $1, %rax; mov $1, %rdi; mov $14, %rdx; syscall;");
    printf("Modifying the function Stack\n");
    stackModify();
    return;
}
