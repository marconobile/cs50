#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int step = 0 ;
int collatz(int n);
int main(void)
{
    int n = get_int("Number: ");
    collatz(n);
    printf("%i\n", step);

}

int collatz(int n)
{
    if (n == 1)
    {
        return step;
    }
    else if (n % 2 == 0)
    {
        step++;
        return collatz(n/2);
    }
    else if (n % 2 != 0)
    {
        step++;
        return collatz(3*n+1);
    }
    return -1;
}
