#include <stdio.h>
#include <stdlib.h>

// Here we define a new type via deftype
// This type is named node
// Which is composed by a struc (structure)
// The struct is defined by:
    // - the integer to be saved in the linked list
    // - a pointer (*next) that points to the next element of the linked list
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // Let's create an empty linked list
    // We need to initialize a list (of type node)
    // i.e. we itialize a pointer to null

    node *list = NULL; // a pointer to an address in memory that will contain
    // data of type node

    // So now we can insert the first element in the linked list
    // to so we allocate memory to contain a 'node' item

    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    // so now we can define the contenet of the first node
    n->number = 1; // define number of struct
    n->next = NULL; // defining the pointer of the next element (non existent atm)
    list = n; // update the pointer list

    // let's suppose that I need to add a value
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        // if error:
        free(list); // clear memory
        return 1;
    }
    // update the contenet of the temp node n
    n->number = 2;
    n->next = NULL;

    // update the linked list
    list->next=n;
    // ie from the starting pointer of list (node), get to the
    // go to addres of list, go to next of first node, set it as pointer of the
    // next node

    // let's add the third el
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;

    list->next->next=n;

    //print contenet:
    // tmp is the list pointer, until the pointer is non NULL, go to the next
    for (node *tmp=list; tmp!=NULL; tmp=tmp->next)
    {
        printf("%i", tmp->number);
    }

    // then finally let's as usual free the mem taken by list

    while(list != NULL) // ie if list is not empty
    {
        // from right to left empty each node
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}