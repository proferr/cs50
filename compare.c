#include <stdio.h>

int main(void)
{
    int x;
    int y;
    printf("What's x?\n");
    scanf("%i", &x);
    printf("What's y?\n");
    scanf("%i", &y);

    if (x < y)
    {
        printf("x is less than y\n");
    }
    else if (x > y)
    {
        printf("x is greater than y\n");
    }
    else
    {
        printf("x is equals to y\n");
    }
}