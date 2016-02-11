#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

struct node * linkedlist_create(char* word){
	struct node *root;
	root = (struct node *) malloc( sizeof(struct node));

	root->next = 0;
	root->word = word;
	root->count = 1;

	return root;
}

//Adds a child after node
void linkedlist_addAfter(struct node* node, struct node* child){
	if(node->next == 0){
		node->next = child;
	}else{
		child->next = node->next;
		node->next = child;
	}
}

//Adds a node to the end of linked list
void linkedlist_addChild(struct node* root, struct node* child){
	if(root->next == 0){
		root->next = child;
	}else{
		linkedlist_addChild(root->next, child);
	}
}

struct node * linkedlist_find(struct node* node, char* word){
	//if node matches return it
	if(strcmp(node->word, word) == 0){
		return node;
	}else{
		if(node->next == 0){
			//If run to the end of linked list (not found)
			struct node *empty;
			empty = (struct node *) malloc( sizeof(struct node));

			empty->next = 0;
			empty->word = "";
			empty->count = 0;
			return empty;
		}
		//Go to the next node and check it
		return linkedlist_find(node->next, word);
	}
}





