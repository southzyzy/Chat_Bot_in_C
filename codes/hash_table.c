#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int val;
    struct node *next;
} Dict;

typedef struct table {
    int size;
    Dict **list;
} Table;

Table *createTable(int size);
int hashCode(Table *t, int key);
void insert(Table *t, int key, int val);
int lookup(Table *t, int key);


int main() {
    Table *t = createTable(5);
    insert(t, 1, 3);
    insert(t, 2, 4);
    printf("%d", lookup(t, 1));
    return 0;
}

Table *createTable(int size) {
    Table *t = (Table *) malloc(sizeof(Table));
    t->size = size;
    t->list = (Dict **) malloc(sizeof(Dict *) * size);
    int i;
    for (i = 0; i < size; i++)
        t->list[i] = NULL;
    return t;
}

int hashCode(Table *t, int key) {
    if (key < 0)
        return -(key % t->size);
    return key % t->size;
}

void insert(Table *t, int key, int val) {
    int pos = hashCode(t, key);
    Dict *list = t->list[pos];
    Dict *newNode = (Dict *) malloc(sizeof(Dict));
    Dict *temp = list;
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

int lookup(Table *t, int key) {
    int pos = hashCode(t, key);
    Dict *list = t->list[pos];
    Dict *temp = list;
    while (temp) {
        if (temp->key == key) {
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}