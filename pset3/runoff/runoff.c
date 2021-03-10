#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Max voters and candidates
#define MAX_VOTERS 100 // max number of voters in the election
#define MAX_CANDIDATES 9 // max numb of candidates in the election

// preferences[i][j] is j-th preference for voter i
// i is the voter guy out of 100
// j = 0,.. represent the oder of preference for the voter i, j points to a candidate aswell
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// GLOBAL Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: "); // first param required from the user, get the number of voters in the election
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}



// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i=0 ; i<candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i; //index of the candidate
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i<voter_count; i++)
    {
        bool voter_not_done = true;
        int rank = 0;
        while (voter_not_done)
        {
            if ( ! candidates[preferences[i][rank]].eliminated)
            {
                candidates[preferences[i][rank]].votes = candidates[preferences[i][rank]].votes+1;
                voter_not_done = false;
            }
            rank++;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int half = ceil(voter_count/2);
    for (int j =0; j<candidate_count; j++)
    {
        if (candidates[j].votes>half)
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count+1;
    // string killed;
    for (int i =0; i<candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes< min)
            {
                min = candidates[i].votes;
                // killed = candidates[i].name
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i=0; i< candidate_count; i++)
    {
        if (!(candidates[i].votes == min ) && (!candidates[i].eliminated))
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i=0; i< candidate_count; i++)
    {
        if (candidates[i].votes == min )
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
