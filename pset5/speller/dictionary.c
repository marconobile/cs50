// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <strings.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool unload(void);


int size_of_dict=0;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N]; // initially an empty array, as soon as we plug in a node it becomes an arrray of nodes, each node a struct that contains a word and a pointer to the next el of the list

// Returns true if word is in dictionary, else false
bool check(const char *word_)
{
    int word_bucked = hash(word_);
    // then access hash table at the given bucket idx
    //  and traverse it while looking if the current word is the word in input

    for (node *tmp=table[word_bucked]; tmp != NULL; tmp=tmp->next)
    {
        int length1 = strlen(tmp->word);
        char word_from_dict[length1];
        strcpy(word_from_dict, tmp->word);
        word_from_dict[strcspn(word_from_dict, "\n")] = 0;

        if (strcasecmp(word_from_dict, word_) == 0)
        {
            return true;
        }
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // We take the word, take its first el, subtract 97, and get the bucket value
    int asci_value;
    asci_value = tolower(word[0]) - 97;
    return asci_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TEST OF HASH TABLE
    int bucket_idx;

    for (int i = 0; i <N; i++)
    {
        table[i] = NULL; // a pointer to an address in memory that will contain data of type node, in a non contiguous manner (i.e. linked list)
    }


    char current_word[100];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    while (fgets(current_word, sizeof(current_word), file)) {
        size_of_dict++;

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {

            fclose(file);
            return false;
        }

        // so now we can define the contenet of the first node
        strcpy(n->word, current_word); // define number of struct


        // get hash value:
        bucket_idx = hash(current_word);
        // printf("Selected bucket = %i\n", bucket_idx);


        // set the new node n to point at the first node in the linked list in hash table[idx]
        n->next = table[bucket_idx];
        // then make the linked list point to the new node
        table[bucket_idx] = n;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (size_of_dict != 0)
    {
        return size_of_dict;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int j = 0; j <N; j++)
    {
        while(table[j] != NULL) // ie if list is not empty
        {
        // from right to left empty each node
        node *tmp = table[j]->next;
        free(table[j]);
        table[j] = tmp;
        }
    }

    for (int k = 0; k <N; k++)
    {
        if(table[k] != NULL)
        {
            return false;
        }
    }
    return true;
}
