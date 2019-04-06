#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "chat1002.h"

// int main(){
// 	node *head = NULL;
	
// 	head=insertNode(head,"What","SIT","Just Sit.");
// 	head=insertNode(head,"Where","SIT","In Nanyang Poly.");
// 	head=insertNode(head,"Who","SIT","I'll do you better, why SIT?");
// 	printLinkedList(head);
// 	return 0;
// }
typedef struct NODE {
	char intent[32];
	char entity[64];
	char answer[256];
	struct NODE *next;
} node;

void printLinkedList(node *head);
void deleteLinkedList(node *head);
node* insertNode(node *head, char *intent, char *entity, char *answer);

/*Use this to check the total structure of the list*/
void printLinkedList(node *head)
{
	node *cursor = head;
	int count = 1;
	while(cursor != NULL)
	{
		printf("Data at node%d is: %s\n",count,cursor->answer);
		cursor = cursor->next;
		count++;
	}
		
}

/*Always inserts in front. Remember to put head to catch the node pointer from this method.*/
node *insertNode(node *head, char *intent, char *entity, char *answer)
{
	node *newnode=(node *)malloc(sizeof(node));
	newnode->next = head;
	strcpy(newnode->intent,intent);
	strcpy(newnode->entity,entity);
	strcpy(newnode->answer,answer);
	
	return (newnode);
}

/*Prototype delete end of list*/
void deleteLinkedList(node *head)
{
	node *cursor = head;
	node *temp;
	while(cursor->next != NULL)
	{
		temp = cursor;
		cursor = cursor->next;
	}
	temp->next = NULL;
	free(cursor);
}

/*Get answer based on intent filter and entity filter*/
char *getAnswer(node *head, const char *intent, const char *entity)
{
	node *cursor = head;
	// tolower(intent);
	// tolower(entity);
	if(cursor != NULL)
	{
		while(cursor->next != NULL)
		{
			if(strcmp(intent,cursor->intent) == 0)
			{
				if(strcmp(entity,cursor->entity) == 0)
				{
					return cursor->answer;
				}
			}
			else
			{
				cursor = cursor->next;
			}
		}
	}
	return NULL;
}

/*Lowercase everything to check.*/
// void lowerWord(char *word)
// {
// 	int i = 0;
// 	while(word[i])
// 	{
// 		word[i] = tolower(word[i]);
// 		i++;
// 	}
// }