/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

// linked-list structure
struct node
{
    char key;
    char value;
    struct node *next;
};

// pointer to point to the haed of the linked-list
struct node *head_PTR = NULL;

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {

    /* to be implemented */

    return KB_NOTFOUND;

}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {

    /* to be implemented */

    return KB_INVALID;

}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) 
{
    // file pointer 
    FILE *f_PTR;

    // variable to store each line of txt file 
    char sentence[400];

    f_PTR = fopen(f, "r");

    // Case 1: There is an issue opening the file 
    if (f_PTR == NULL)
    {
        printf("Error: There is an issue accessing the file.");
    }

    // Case 2: There is no issue opening the file 
    else
    {
        while (!feof(f_PTR))
        {
            fgets(sentence, 400, f_PTR);
            insert_node(sentence);
        }
        fclose(f_PTR);
    }
    
    return 0;
}

// Function to insert into linked-list 
void insert_node(char *sentence)
{

    // to be completed
    // temp pointer to point to the head_PTR
    struct node *temp_PTR = head_PTR;

    //

    // Case 1: Linked-list is empty
    if (head_PTR == NULL)
    {
        struct node *newNode = (struct node*)malloc(sizeof(struct node));
        newNode->key;
        newNode->next;
        newNode->value;

    }

}



/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset(int inc, char *inv[]) {

    /* to be implemented */
    while (inv[inc] != NULL) {
        inv[inc] = NULL;
        inc++;
    }
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

    /* to be implemented */

}