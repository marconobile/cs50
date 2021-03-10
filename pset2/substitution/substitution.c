#include <stdio.h>
#include <cs50.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int check_for_dup(string s);

int main(int argc, string argv[])
{

    // check 1: if not ./substitution key; return error
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int len = strlen(argv[1]);

    string alphabet = "NQXPOMAFTRHLZGECYJIUWSKDVBvchprzgjntlskfbdqwaxeuymoi"; // all the letters of the either upper/lower aplhabet
    int len_al = strlen(alphabet);

    int counter = 0;
    // check 2: if not letter in key return error
    for (int i = 0; i < len; i++)
    {
        // for each letter in the key
        if (! isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key, key only chars\n");
            return 1;
        }
        for (int j = 0; j < len_al; j++)
        {
            if (argv[1][i] == alphabet[j])
            {
                counter++;
            }
        }
    }
    if (check_for_dup(argv[1]) == 0)
    {
        printf("Duplicate letters in key not accepted!");
        return 1;
    }

    if (counter == 26)
    {
        string s = get_string("plaintext: ");
        printf("\n");
        int len1 = strlen(s);

        string to_compare = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        printf("ciphertext: ");
        for (int k = 0; k < len1; k++)
        {
            // for each letter in s
            if (ispunct(s[k]) || isblank(s[k]) || isdigit(s[k]))
            {
                printf("%c", s[k]);
            }

            if (islower(s[k]))
            {
                // find pos of s[k] in alphabet
                int pos = (int) s[k] - (int) 'a'; // in pos now we have the position of the letter in the original alphabet
                // thus now we just need to grab that pos in the key
                printf("%c", tolower(argv[1][pos]));
            }
            if (isupper(s[k]))
            {
                int pos = (int) s[k] - (int) 'A';
                printf("%c", toupper(argv[1][pos]));
            }
        }
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    printf("\n");
    return 0;
}


int check_for_dup(string s)
{
    int len_s = strlen(s);

    for (int i1 = 0 ; i1 < len_s; i1++)
    {
        for (int i2 = 0; i2 < len_s ; i2++)
        {
            if (s[i1] == s[i2] && i1 != i2)
            {
                return 0; // if not good
            }
        }
    }
    return 1; // if good
}