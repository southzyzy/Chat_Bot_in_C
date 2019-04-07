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
#include "linkedlist.c"


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
/* BUFFER FOR KNOWLEDGE.C */
node *knowledge = NULL;

int knowledge_get(const char *intent, const char *entity, char *response, int n) {

    /* to be implemented */
    char *answer = getAnswer(knowledge, intent, entity);
    /* to be implemented */
    if (answer != NULL) {
        snprintf(response, n, "%s", answer);
        return KB_OK;
    } else {
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
    knowledge = insertNode(knowledge, intent, entity, response);
    return KB_OK;
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
    // file pointer
    FILE *f_PTR;

    // variable to store each line of txt file
    char sentence[MAX_INPUT];

    char *comparsion_header[] = {"who", "where", "what"};

    f_PTR = fopen((const char *) f, "rb");

    // Case 1: There is an issue opening the file
    if (f_PTR == NULL) {
        printf("Error: There is an issue accessing the file.\n");
        return 0;
    }

    char delimiter[] = "[]=\n"; // delimiter
    char *intent = malloc(sizeof(sentence)); // construct the intent malloc size

    // loop through the files
    while (!feof(f_PTR) && fgets(sentence, sizeof(sentence), f_PTR)) {
        char *entity = malloc(sizeof(sentence));
        char *response = malloc(sizeof(sentence));

        char *token = strtok(sentence, delimiter);

        for (int i = 0; i < 3; i++) {
            if (strstr(token, comparsion_header[i])) {
                // Get the intent of question
                strcpy(intent, token);
                // move to the next line
                token = strtok(0, delimiter);
            }
        }

        // retrieve the question
        if (!isspace(*token)) {
            strcpy(entity, token);
        }

        while (token != 0) {
            // Get the next line
            token = strtok(0, delimiter);
            // if the read file is an empty line
            if (token == NULL)
                break;
                // if space exist
            else if (isspace(*token))
                break;
            // get the answer
            strcpy(response, token);

            // Insert into the linked list
            knowledge = insertNode(knowledge, intent, entity, response);
            break;
        }
    }
    fclose(f_PTR);

    return 0;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
    /* to be implemented */
    if (knowledge != NULL) {
        node *head = knowledge;
        node *temp = head->next;
        while (head->next != NULL) {
            printLinkedList(head);
            head->next = NULL;
            free(head);
            head = temp;
            temp = head->next;
        }
        //Set the first one to null as well.
        head = NULL;
    } else {
        knowledge = NULL;
    }
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
int knowledge_write(FILE *f) {

    // Table *temp = t;
    // int counter = 0;
    // /* to be implemented */
    // for (int i = 0; i < temp->size; i++) {
    // 	if (i == 0) {
    // 		fprintf(f, "[what]");
    // 		Dict *tempd = temp->list[i];
    // 		while (tempd->next != NULL) {
    // 			fprintf(f, "%s=%s", tempd->question, tempd->answer);
    // 			counter += 1;
    // 		}
    // 		fprintf(f, "%s=%s", tempd->question, tempd->answer);
    // 		counter += 1;
    // 		printf("\n");
    // 	}
    // 	else if (i == 1) {
    // 		fprintf(f, "[where]");
    // 		Dict *tempd = temp->list[i];
    // 		while (tempd->next != NULL) {
    // 			fprintf(f, "%s=%s", tempd->question, tempd->answer);
    // 			counter += 1;
    // 		}
    // 		fprintf(f, "%s=%s", tempd->question, tempd->answer);
    // 		counter += 1;
    // 		printf("\n");
    // 	}
    // 	else if (i == 2) {
    // 		fprintf(f, "[who]");
    // 		Dict *tempd = temp->list[i];
    // 		while (tempd->next != NULL) {
    // 			fprintf(f, "%s=%s", tempd->question, tempd->answer);
    // 			counter += 1;
    // 		}
    // 		fprintf(f, "%s=%s", tempd->question, tempd->answer);
    // 		counter += 1;
    // 		printf("\n");
    // 	}
    // }

    return 0;
}