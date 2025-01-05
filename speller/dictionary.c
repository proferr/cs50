// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int n = hash(word);
    // Pointer node which points to the head of the hash table
    node *ptr = table[n];
    // Loop list until the final node is reached
    for (node *tmp = ptr; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Get the lengh of the word
    // Sum the value of the characters
    unsigned int hash_word = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_word += tolower(word[i]);
        hash_word = (hash_word * tolower(word[i])) % N;
    }
    return hash_word;
}

int counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    // Define list
    // Define counter
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not load gile.");
        return false;
    }

    char list[LENGTH + 1];

    while (fscanf(file, "%s", list) != EOF)
    {
        // Word counter, used for size function
        counter++;

        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return 1;
        }

        // Copy word in the list to a node new_node
        // Copy the word in the list to a node
        // Set NULL to next node
        strcpy(new_node->word, list);
        new_node->next = NULL;

        int h = hash(list);

        if (table[h] == NULL)
        {
            table[h] = new_node;
        }
        else
        {
            // makes the next the new head
            new_node->next = table[h];
            // head points to the new node
            table[h] = new_node;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Assign list to a new node
    node *tmp = NULL;
    node *ptr = NULL;

    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }

    return true;
}
