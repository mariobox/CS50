// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


typedef struct node
{
    char dicword[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[26]; // one element for each letter in the alphabet
node *head = NULL;
//node *cursor = NULL;
unsigned int wordcount = 0;

// Loads dictionary into memory, returning true if successful else false

bool load(const char *dictionary)
{

    for (int i = 0; i < 26; i++)
    {
        hashtable[i] = NULL;
    }

    FILE *fin = fopen(dictionary, "r");
    if (fin == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }

    char *entry = malloc((LENGTH + 1) * sizeof(char));

    while (fscanf(fin, "%s", entry) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            // load word into new node
            strcpy(new_node->dicword, entry);

            // increase dictionary word count
            wordcount++;

            // hash word: hash will be the index (from 0 to 25) of first letter
            int hash = (int) entry[0] - 97;


            if (hashtable[hash] == NULL)
            {
                hashtable[hash] = new_node;
                head = new_node;
            }
            else
            {
                new_node->next = head;
                hashtable[hash] = new_node;
                head = new_node;
            }
        }
    }
    free(entry);
    fclose(fin);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded

unsigned int size(void)
{

    return wordcount;
}


// Unloads dictionary from memory, returning true if successful else false

bool unload(void)
{
    // For each member of the 26 pointer array free linked list
    for (int i = 0; i < 26; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
    //return false;
}

// Returns true if word is in dictionary else false

bool check(const char *word)
{
    int hash = (int) tolower(word[0]) - 97;
    node *cursor = hashtable[hash];

    // create temp variable to store value of word
    char temp[LENGTH + 1];
    int size = strlen(word);

    // copy word into temp
    strncpy(temp, word, size);//word is the const char pointer.

    // initialize closing character for temp
    temp[size] = '\0';

    // convert temp to lowercase
    int i = 0;
    while (temp[i] != '\0')
    {
        temp[i] = tolower(temp[i]);
        i++;
    }

    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->dicword) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }


    return false;
}


