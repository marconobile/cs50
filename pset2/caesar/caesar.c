#include <stdio.h>
#include <cs50.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// char * rotate_message(string s, int k);

int main(int argc, string argv[]){
    // let's check if we have a single command line argument passed
    if (argc != 2){
        printf("Error in user's input\n");
        return 1;
    }
    // let's check if each element of the string passed is a digit (no char allowed)
    int len = strlen(argv[1]);
    for (int j = 0; j<len; j++){
        if ( ! isdigit(argv[1][j])){
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // once the tests are passed we save the input key
    int k = atoi(argv[1]);
    // printf("%i\n",key);

    // let's now ask the user for the tobeencripted message:
    string s = get_string("plaintext: ");

    // rotate_message(s, key);
    int len1 = strlen(s);
    char result[len1];
    for (int i = 0; i<len1; i++){
        if (ispunct(s[i]) || isspace(s[i])){
            result[i] = s[i];
        }

        if (isupper(s[i])){
            int p = (int) s[i] - 65;
            // printf("%c, %i, %i\n", s[i], p, (p+k)%26);
            int rotate = (p+k)%26;
            // printf("%c", 65+rotate);
            result[i] = (char) 65+rotate;

        }
        else if (islower(s[i])){
            int p = (int) s[i] - 97;
            // printf("%c, %i, %i\n", s[i], p, (p+k)%26);
            int rotate = (p+k)%26;
            // printf("%c", 97+rotate);
            result[i] = (char) 97+rotate;
        }
    }
    printf("ciphertext: ");
    for (int idx = 0; idx<len1; idx++){
        printf("%c", result[idx]);
    }
    printf("\n");
    return 0;
}

