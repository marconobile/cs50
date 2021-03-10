#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_owed_change(string prompt);
void cashhh(int a, int b, int *quotient, int *remainder);

int main(void)
{
    float change = get_owed_change("Input the ammout of changed owed: ");
    // printf("Total chage owed: %.2f\n", change);
    change = (int)round(change * 100);

    int result;
    int n_of_coins, res_chance;
    cashhh(change, 25, &n_of_coins, &res_chance);
    // printf("25 - Quotient is: %d\nRemainder is: %d\n", n_of_coins, res_chance);
    result = n_of_coins;
    if (res_chance>0)
    {
        cashhh(res_chance, 10, &n_of_coins, &res_chance);
        // printf("10 - Quotient is: %d\nRemainder is: %d\n", n_of_coins, res_chance);
        result = result + n_of_coins;
    }
    if (res_chance>0)
    {
        cashhh(res_chance, 5, &n_of_coins, &res_chance);
        // printf("5 - Quotient is: %d\nRemainder is: %d\n", n_of_coins, res_chance);
        result = result + n_of_coins;
    }
    result = result + res_chance;
    // printf("Final n of coins %i, final chance %i",result ,res_chance);
    printf("%i\n",result);

}

//////////////////////////////////////////////////////
// Functions
//
void cashhh(int a, int b, int *quotient, int *remainder){
   *quotient = a / b;
   *remainder = a % b;
}

// Prompt user for positive integer
float get_owed_change(string prompt)
{
    float n;
    do
    {
        n = get_float("%s", prompt);
    }
    while (n<0);
    return n;
}