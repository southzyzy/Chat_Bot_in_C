#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chat1002.h"


/*int main() {
    Table *t = createTable(5);
    insert(t, 1, "SIT", "SIT is an autonomous university in Singapore.");
    insert(t, 2, "the ICT Cluster", "The ICT Cluster offers degrees in software engineering, information security and telematics.");
    insert(t, 3, "ICT1001", "Introduction to ICT.");
    printf("%s\n", lookup(t, 3));
    return 0;
}*/

Table *createTable(int size) {
    Table *t = (Table *) malloc(sizeof(Table));
    t->size = size;
    t->list = (Dict **) malloc(sizeof(Dict *) * size);
    for (int i = 0; i < size; i++)
        t->list[i] = NULL;
    return t;
}

int hashCode(Table *t, int key) {
    if (key < 0)
        return -(key % t->size);
    return key % t->size;
}

void insert(Table *t, int key, char *question, char *answer) {
    int pos = hashCode(t, key);
    Dict *list = t->list[pos];
    Dict *newNode = (Dict *) malloc(sizeof(Dict));
    Dict *temp = list;

    // Override the value if the key provided is the same as the one that exist in the list
    while (temp) {
        if (temp->key == key) {
            temp->question = question;
            temp->answer = answer;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->question = question;
    newNode->answer = answer;
    newNode->next = list;
    t->list[pos] = newNode;
}

char *lookup(Table *t, int key) {
    int pos = hashCode(t, key);
    Dict *list = t->list[pos];
    Dict *temp = list;
    while (temp) {
        if (temp->key == key) {
//            char question[MAX_INPUT], answer[MAX_INPUT];
//            strcpy(question, temp->question);
//            strcpy(answer, temp->answer);

//            printf("Question: %s\n", question);
//            printf("Answer: %s\n", answer);
            return temp->answer;
        }
        temp = temp->next;
    }
    return "Key does not exist !";
}