#include <stdio.h>

int add(int a, int b);

int main(void)
{
    int x, y;
    printf("x: ", x);
    scanf("%i", &x);
    printf("y: ", y);
    scanf("%i", &y);

    printf("%i\n", add(x, y));
}

int add(int a, int b)
{
    return a + b;
}