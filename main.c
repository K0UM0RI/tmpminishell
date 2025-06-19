int *globalint()
{
    static int g = 0;
    return (&g); 
}

void ft(int l)
{
    *globalint() = l;
}
#include <stdio.h>
int main()
{
    printf("%d\n", *globalint());
    ft(4);
    printf("%d\n", *globalint());
}