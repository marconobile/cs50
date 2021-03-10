#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer candidate i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
// An array of pairs, which will represent all of the pairs of candidates (for which one is preferred over the other) in the election.
pair pairs[MAX * (MAX - 1) / 2]; // sum_i=11^i=MAX i = [MAX * (MAX - 1) / 2]

int pair_count;
int candidate_count;
int best_winner=-1;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
// bool check_ancestor(int t, int i);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_order(void);
int find_rank(int ranks[], int i);
bool check_4_cycle(int node, int i);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); // the user inserts the name of the guy that want to place i-th in his pref list

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote, this function is called for each candidate
bool vote(int rank, string name, int ranks[]) // takes the rank to be setted for the candidate name,
{
    for (int i=0; i<candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; // i : idx of the candidate that ranked as rank for this voter

            return true; // if vote registered for this call, return true!
        }
    }
    return false;
}

// Updates preferences given a voter's ranks. The function is called once for each voter!
//THIS should update the global preferences array to add the current voter’s preferences.
//Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j
// ranks: array of a single voter of form: ranks[lvl]=candidate_idx
void record_preferences(int ranks[])
{
    // int len_ = strlen(ranks[]);
    for (int i = 0; i < candidate_count ; i++)
    {
        for (int j = 0; j < candidate_count ; j++)
        {
            if (( i != j ) && (i < j))
            {
                // guy in rank i is higher ranked then guy at rank j
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }

    return;
}

void add_pairs(void)
{
    for (int i = 0 ; i < candidate_count ; i++)
    {
        for (int j = 0 ; j < candidate_count ; j++)
        {
            if ((preferences[i][j] > preferences[j][i]) &&  (i != j))
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if ((preferences[i][j] < preferences[j][i]) &&  (i != j))
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
            }
        }
    }
    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i< pair_count ; i++)
    {
        for (int j = 0; j< pair_count-1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser]<preferences[pairs[j+1].winner][pairs[j+1].loser])
            {
                pair temp = pairs[j];
                pairs[j]=pairs[j+1];
                pairs[j+1]=temp;
            }

        }
    }
    return;
}

void lock_pairs(void)
{
    for (int pair_idx = 0 ; pair_idx< pair_count; pair_idx++)
    {
        if (check_4_cycle(pairs[pair_idx].loser, pairs[pair_idx].winner))
        {
            ;
        }
        else
        {
            locked[pairs[pair_idx].winner][pairs[pair_idx].loser]=true;
        }
    }
    // for each pair, winner:i, loser:j
    //     check if j->...->i is a path: recursion
    //     if above==true
    //         next pair
    //     else
    //         lock

    return;
}

bool check_4_cycle(int node, int i)
{
    // base case
    if (locked[node][i]==true)
    {
        return true;
    }
    // recursion case
    // explore neighbourhood
    bool no_neighbours = true;
    for (int j = 0 ; j< candidate_count ; j++)
    {
        if (locked[node][j]==true)
        {
            no_neighbours = false;
            return check_4_cycle(j,i);
        }
    }
    if (no_neighbours)
    {
        return false;
    }
    return false;
}


// Print the winner of the election
void print_winner(void)
{
    for (int i = 0 ; i < candidate_count ; i++) // for each COL
    {
        bool test_next_cand = false;
        for (int j = 0 ; j < candidate_count ; j++) // for each ROW
        {
            if (locked[j][i]!=false) // if any el of the row is true
            {
                test_next_cand = true;
                break;//  // evaluate next node
            }
        }
        printf("%s\n",candidates[i]);
    }
    return;
}


////////////////////////////////////////////////



int find_rank(int ranks[], int i)
{
    for (int j = 0; j<candidate_count; j++)
    {
        if (ranks[j]==i)
        {
            return j;
        }
    }
    return -1;
}

bool check_order(void)
{
    for (int k = 0; k < pair_count ; k++)
    {
        int i1 = pairs[k].winner; //===> the index i of current pair
        int j1 = pairs[k].loser; //===> the index j ...
        for (int l = 0;  l < pair_count ; l++)
        {
            if (k!=l)
            {
                int i2 = pairs[l].winner; //===> the index i
                int j2 = pairs[l].loser; //===> the index j

                if (preferences[i1][j1] > preferences[i2][j2])
                {
                    ;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}