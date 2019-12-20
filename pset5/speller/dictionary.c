/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"
#define HASHTABLE 190800


int count=0;
char word[LENGTH+1];
int hash(const char* word);

typedef struct node
{
    char* word;
    struct node* next;
} node;

node *hashtable[HASHTABLE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    node* cursor=malloc(sizeof(node));
    
    int bucket=hash(word);
    cursor=hashtable[bucket];
    if (cursor==NULL)
    {
        free(cursor);
        return false;
    }
    if (strcasecmp(word,cursor->word)==0)
    {
        return true;
    }
    else
    {
        while (cursor!=NULL)
        {
            if (strcasecmp(word,cursor->word)==0)
            {
                return true;
            }
            else
            {
                cursor=cursor->next;
            }
        }
    }
    free(cursor);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    {
        FILE* dicpointer = fopen(dictionary, "r");
    
        if (dicpointer==NULL)
        {
            return false;
        }
    
        while (fscanf(dicpointer, "%s\n", word)!=EOF)
        {
            node *new = malloc(sizeof(node));
            new->word=malloc(sizeof(word)+1);
        
            strcpy(new->word, word);
            int bucket=hash(word);
        
            //check if pointing anywhere
            if (hashtable[bucket]==NULL)
            {
                hashtable[bucket]=new;
                new->next=NULL;
            }
            //if pointing to something already
            else
            {
                new->next=hashtable[bucket];
                hashtable[bucket]=new;
            }
            count++;
        }
        fclose(dicpointer);
    }
    return true;
}

int hash(const char* word)
{
    int index=0;
    
    for (int i=0; word[i]!='\0'; i++)
    {
        index+=toupper(word[i]);
        if (i%2==0)
        {
            index+=(20*tolower(word[i]));
        }
    }
    
    int bucket=index%HASHTABLE;
    return bucket;
    
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    
    
    for (int i=0; i<HASHTABLE; i++)
    {
        node *cursor;
        cursor=hashtable[i];
        
        while (cursor!=NULL)
        {
            node *temp=cursor;
            cursor=cursor->next;
            free(temp);
        }
        hashtable[i]=NULL;
    }
    
    return true;
}
