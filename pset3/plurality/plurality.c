#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates THIS GUY IS GLOBAL
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates, here we set candidate_count
    candidate_count = argc - 1; // by command line we need to pass candidates (?), -1 cuz the first arg is the program name
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // NB candidates is an array, candidate is the data struct, and we fill the array with the names that we pass via argv
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters, we setted the number of voters in voter_count
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: "); // here we require as input from the user the name of one of the possible candididates

        // Check for invalid vote <<<<====
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // printf("THis is the vote func for%s\n", name);
    // for (int k=0; k<candidate_count;k++){
    //     printf("%s",candidates[k].name);

    // }
    // input name that was voted
    for (int i = 0 ; i < candidate_count; i++)
    {
        // printf("We have: %s, %s, %i",candidates[i].name, name, strcmp(candidates[i].name, name));
        if ( strcmp(candidates[i].name, name)==0 ){
            // printf("HI");
            candidates[i].votes =  candidates[i].votes+1;
            return true;
        }
    }
    // printf("Nope");
    return false;

}


// Print the winner (or winners) of the election


void print_winner(void)
{
    int current_max = 0;
    for (int i=0 ; i<candidate_count ; i++){
        if (current_max > candidates[i].votes)
        {
            ;
        }
        else
        {
            current_max = candidates[i].votes;
        }
    }
    for (int j=0 ; j<candidate_count ; j++)
    {
        if (candidates[j].votes == current_max)
        {
            printf("%s\n",candidates[j].name);
        }
    }


    return;
}

// void print_winner(void)
// {
//     // TODO, SORTING

//     return;
// }


// void merge_sort(int l,h)
// {
//     if (l<h){
//         int mid = (l+h)/2;
//         merge_sort(l, mid);
//         merge_sort(mid+1, h);
//         merge(l, mid, h)

//     }
// }