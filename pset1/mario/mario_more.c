#include <stdio.h>
#include <cs50.h>

int get_height(string prompt);



int main(void)
{
    int height = get_height("Insert the height of the pyramid (max 8):\n----\n");
    printf("stored: %i\n", height);

    for (int row = 1; row<=height; row++)
    {

        if (height-row !=0)
        {
            printf("%*c",height-row, ' '); // care this guy always prints something even if height-row == 0
        }
        for (unsigned i = row; i !=0;--i)
        {
            printf("#");
        }
        printf(" ");
        for (unsigned j = row; j !=0;--j)
        {
            printf("#");
        }
        printf("\n");
    }

}


// Prompt user for positive integer
int get_height(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while ((n<0) || (n>8));
    return n;
}
