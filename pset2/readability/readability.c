#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int count_letters(int length, char input[]);
int count_words(int length, char input[]);
int count_sentences(int length, char input[]);

int main(void)
{
    string s = get_string("Text: ");
    int len = strlen(s);

    // printf("Number of letters %i\n", count_letters(len, s));
    // printf("Number of words %i\n", count_words(len, s));
    // printf("Number of sentences %i\n", count_sentences(len, s));

    int letters = count_letters(len, s);
    int words = count_words(len, s);
    int sentences =  count_sentences(len, s);

    int L = (letters*100)/words;
    int S = (sentences*100)/words;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index<1){
        printf("Before Grade 1\n");
    }
    else if(index>=16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n", (int) round(index));
    }

}


int count_letters(int length, char input[]){
    int result = 0;
    for (int i = 0; i<length; i++){ // then try the other way
        if (isalpha(input[i])){
            // printf("%c", input[i]);
            result++;
        }

    }
    return result;
}

int count_words(int length, char input[]){
    int result = 0;
    for (int i = 0; i<length; i++){ // then try the other way
        if (isspace(input[i])){
            // printf("%c", input[i]);
            result++;
        }
    }
    return result+1;
}

int count_sentences(int length, char input[]){
    int result = 0;
    for (int i = 0; i<length; i++){ // then try the other way
        // if (iscntrl(input[i])){
        if (input[i]==33 || input[i] == 46 || input[i]==63){
            // printf("ISPUNCT FILTERING %c", input[i]);
            result++;
        }
    }
    return result;
}
