#include <stdio.h>
#include <cs50.h>

int get_height(string prompt);


int main(void)
{
    int height = get_height("Insert the height of the pyramid (max 8):\n----\n");
    printf("stored: %i\n", height);

    for (int row = 0; row < height;  row++)
    {
        // printf("ROW: %i",row);
        printf("%*c",height-row+1 , ' ');
        for (unsigned i = row+1; i !=0;--i)
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
