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
    char reply[50] = "SIT is a university in Nanyang Polytechnic.";
    char reply2[100] = "The ICT Cluster offers degrees in software engineering, information security and telematics.";
    char reply3[50] = "Introduction to ICT.";
    /* to be implemented */
    if (compare_token(entity, "sit") == 0) {
        snprintf(response, n, "%s", reply);
        return KB_OK;
    } else if (compare_token(entity, "the ICT Cluster") == 0) {
        snprintf(response, n, "%s", reply2);
        return KB_OK;
    } else if (compare_token(entity, "ICT1001") == 0) {
        snprintf(response, n, "%s", reply3);
        return KB_OK;
    } else {
        snprintf(response, n, "I don't know. What is '%s'?", entity);
        return KB_NOTFOUND;
    }
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
int knowledge_read(FILE *f) {
    //       load D:/SIT/ICT-1002 Programming Fundamentals/C/Assignment/ICT1002_Chat_Bot/codes/test.ini
    // file pointer 
    FILE *f_PTR;

    // variable to store each line of txt file 
    char sentence[MAX_INPUT];

    char *comparsion_header[] = {"[who]"};

    f_PTR = fopen((const char *) f, "r");

    // create hash table based on the size of the file
    Table *knowledge_table = createTable(12);

    // Case 1: There is an issue opening the file 
    if (f_PTR == NULL) {
        printf("Error: There is an issue accessing the file.\n");
        return 0;
    }

    int key = 1; // variable to determine size of hash table to create
    char delimiter[] = "="; // delimiter

    while (!feof(f_PTR) && fgets(sentence, sizeof(sentence), f_PTR)) {
        // get the first token and store it
        char *token = strtok(sentence, delimiter);

        char qn[MAX_INPUT], ans[MAX_INPUT];
        strcpy(qn, token);
        printf("%d. %s\n", key, qn);
        
        // Get the second token and store it
        while (token != 0) {
            token = strtok(0, delimiter);
            strcpy(ans, token);
            printf("%d. %s", key, ans);
            break;
        }

        insert(knowledge_table, key, qn, ans);
        key++;
    }

    fclose(f_PTR);

    return 0;
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