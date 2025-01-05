#include <stdio.h>

int main(void)
{
    char name[50];
    printf("What's your name?\n");
    scanf("%s", name);
    printf("hello %s", name);
    return 0;
}