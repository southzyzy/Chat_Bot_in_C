/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chat1002.h"

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

    return "Chatbot";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {
    return "User";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {

    /* check for empty input */
    if (inc < 1) {
        snprintf(response, n, "");
        return 0;
    }

    /* look for an intent and invoke the corresponding do_* function */
    if (chatbot_is_exit(inv[0]))
        return chatbot_do_exit(inc, inv, response, n);
    else if (chatbot_is_smalltalk(inv[0]))
        return chatbot_do_smalltalk(inc, inv, response, n);
    else if (chatbot_is_load(inv[0]))
        return chatbot_do_load(inc, inv, response, n);
    else if (chatbot_is_question(inv[0]))
        return chatbot_do_question(inc, inv, response, n);
    else if (chatbot_is_reset(inv[0]))
        return chatbot_do_reset(inc, inv, response, n);
    else if (chatbot_is_save(inv[0]))
        return chatbot_do_save(inc, inv, response, n);
    else {
        snprintf(response, n, "I don't understand \"%s\".", inv[0]);
        return 0;
    }

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

    return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

    snprintf(response, n, "Goodbye!");

    return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {
    if (strcmp(intent, "load") == 0) {
        return 1;
    }

    return 0;
}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
    // variable to store the name of the file
    char file_name[MAX_INPUT];

    strcpy(file_name, inv[1]);

    // read the contents of the file
    knowledge_read((FILE *) file_name);
}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
    // not done
    // char *question_key_words[] = {"what", "where", "who"};

    // for (int i = 0; i < 3; i++) {
    // if (strcmp(intent, question_key_words[i]) == 0) {
    // return 1;
    // }
    // }
    // return 0;
    return compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 ||
           compare_token(intent, "who") == 0;
}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) // to be implemented 
{
    char *after_question_words[] = {"is", "are"};
    char entity[MAX_RESPONSE] = "";

    //Get the entity.
    for (int i = 2; i < inc; i++) {
        strcat(entity, inv[i]);
        if (i != inc - 1) {
            strcat(entity, " ");
        }

    }
    if (knowledge_get(inv[0], entity, response, n)) {
        prompt_user(response, n, "I don't know. What is '%s'?", entity);
        knowledge_put(inv[0], entity, response);
        //Change the buffer to thank the user rather than his inputs.
        snprintf(response, n, "Thank you.");

    }
    return 0;

}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {

    /* to be implemented */
    if (strcmp(intent, "reset") == 0) {
        return 1;
    }
    return 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {

    /* to be implemented */
    knowledge_reset();
    snprintf(response, n, "Chatbot reset.");

    return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "save"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {

    /* to be implemented */
    if (strcmp(intent, "save") == 0) {
        return 1;
    }
    return 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {

	/* to be implemented */
	FILE *to_save_file;
	char filename[MAX_INPUT];
	snprintf(to_save_file, MAX_INPUT, "%s.ini", inv[1]);

	to_save_file = fopen(filename, "w");
	if (to_save_file == NULL) {
		snprintf(response, n, "Could not open file.");
		return 0;
	}
	else {
		//int counter = knowledge_write(to_save_file, knowledge_table);
		fclose(to_save_file);
		snprintf(response, n, "Chatbot saved.");
		//snprintf(response, n, "%d lines written.", counter);
		return 0;
	}
}


/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {
    /* initialise own question */
    char question[MAX_INPUT];
    /* To lower case the intent */
    formatString(strcpy(question, intent));

    /* Load the small talk list and append it into the hash_table */
    FILE *fp;
    char file[MAX_INPUT] = "data/Small_Talk_Questions.txt";

    // Open the file and append the small file question list
    fp = fopen(file, "r");

    // return error if the file cannot be open
    if (fp == NULL) {
        printf("Unable to open %s\n", file);
        return 0;
    }

    char line[MAX_INPUT];
    char delim[] = "::";

    while (fgets(line, sizeof(line), fp)) {
        char *ptr = strtok(line, delim);
        // Checks for delimeter
        while (ptr != 0) {
            if (strstr(ptr, question) != NULL) {
                fclose(fp);
                return 1;
            }

            // Use of strtok to split the :: variable and set strtok counter back to 0
            ptr = strtok(0, delim);
        }
    }

    fclose(fp);

    return 0;

}


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {
    // construct the question input by user
    char question[MAX_INPUT] = "";
    for (int i = 0; i < (int) sizeof(*inv); i++) {
        if (inv[i] == (char *) '\n' || inv[i] == NULL)
            break;
        formatString(inv[i]);
        strcat(question, inv[i]);
        strcat(question, " ");
    }

    FILE *fp;
    char file[MAX_INPUT] = "data/Small_Talk_Questions.txt";

    // Open the file and append the small file question list
    fp = fopen(file, "r");

    // return error if the file cannot be open
    if (fp == NULL) {
        printf("Unable to open %s\n", file);
        return 0;
    }

    char line[MAX_INPUT];
    char delim[] = "::";

    while (fgets(line, sizeof(line), fp) && !feof(fp)) {
        char *ptr = strtok(line, delim);
        // Checks for delimeter
        while (ptr != 0) {
            if (strstr(question, ptr) != NULL) {
                ptr = strtok(0, delim); // get the answer
                snprintf(response, n, ptr);
            }

            // Use of strtok to split the :: variable and set strtok counter back to 0
            ptr = strtok(0, delim);
        }
    }

    fclose(fp);

    return 0;

}

int formatString(char *string) {
    // Remove the newline from fgets
    size_t ln = strlen(string) - 1;
    if (string[ln] == '\n') {
        string[ln] = '\0';
    }

    for (size_t i = 0; i < strlen(string); i++) {
        string[i] = tolower(string[i]);
    }
}
