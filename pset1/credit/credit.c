#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_card_id(string prompt);

int main(void){
    long id = get_card_id("Input the id of the card: ");
    // printf("ID: %li\n", id);

    long id_1 = id;

    int counter = 1;
    int other_number = 0;
    int current_number;
    int valid;
    int result=0;
    int number_of_digits;
    while(id){
        // printf("%li\n", id % 10);
        current_number = id % 10;
        id /= 10;

        if (counter%2 == 0){
            int to_be_decomposed = 2*current_number;
            while(to_be_decomposed){
                // printf("%d\n", to_be_decomposed % 10);
                result = result + to_be_decomposed % 10;
                to_be_decomposed /= 10;
            }
        }
        else{
            other_number = other_number+current_number;
        }
        counter++;
    }
    number_of_digits = counter;
    // printf("number_of_digits = %i", number_of_digits);
    // printf("First result %i\n",result);
    // printf("Second result %i\n", other_number);
    int solution = result+ other_number;
    // printf("Thus solution is %i and its module10 is  %i\n",solution, solution%10);
    if (solution % 10 == 0){
        valid = 1;
        // printf("VALID\n");
    }
    // else
    // {
    //     valid = 0;
    //     printf("INVALID\n");
    // }

    int first_number;
    int second_number;
    int j=0;
    long id_2 = id_1;
    while(id_1){
        first_number = id_1 % 10;
        j++;
        id_1 /= 10;
    }
    // printf("%i\n", first_number);

    for (int k=0; k<j-1; k++){
        second_number = id_2 % 10;
        id_2 /= 10;
    }

    // printf("%i\n", second_number);

    int a = first_number;
    int b = second_number;
    int assigned = 0;
    int real_n = number_of_digits-1;
    // // 371449635398431
    if (a == 3 && valid == 1 && real_n == 15){
        if (b == 4 || b == 7){
            assigned = 1;
            printf("AMEX\n");
        }
    }

    else if (a == 5 && valid == 1 && real_n == 16){
        if (b == 1  || b == 2  || b == 3  || b == 4  || b == 5 ){
            assigned = 1;
            printf("MASTERCARD\n");
        }
    }
    else if (number_of_digits == 13 || real_n == 16){
        if (a == 4  && valid == 1){
            assigned = 1;
            printf("VISA\n");
        }
    }
    // printf("assigned==%i",assigned);
    if (assigned == 0){
        printf("INVALID\n");

    }



}



// 4003600000000014 , visa
// Prompt user for a credit card id
long get_card_id(string prompt){
    long n;
    do
    {
        n = get_long("%s", prompt);
    }
    while (n<0);
    return n;
}