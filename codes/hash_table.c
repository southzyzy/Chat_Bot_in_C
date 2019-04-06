#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    char *val;
    struct node *next;
} Dict;

typedef struct table {
    int size;
    Dict **list;
} Table;

/* Table *createTable(int size);
int hashCode(Table *t, int key);
void insert(Table *t, int key, char *val);
char *lookup(Table *t, int key); */


/* int main() {
    Table *t = createTable(5);
    insert(t, 1, "Hello");
    insert(t, 2, "World");
    printf("%s\n", lookup(t, 3));
    return 0;
} */

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

void insert(Table *t, int key, char *val) {
    int pos = hashCode(t, key);
    Dict *list = t->list[pos];
    Dict *newNode = (Dict *) malloc(sizeof(Dict));
    Dict *temp = list;

    // Override the value if the key provided is the same as the one that exist in the list
    while (temp) {
        if (temp->key == key) {
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    t->list[pos] = newNode;
}

char *lookup(Table *t, int key) {
    int pos = hashCode(t, key);
    Dict *list = t->list[pos];
    Dict *temp = list;
    while (temp) {
        if (temp->key == key) {
            return temp-> val;
        }
        temp = temp->next;
    }
    return "Key does not exist !";
}