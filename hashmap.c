#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "hashmap.h"

#define HASHMAP_SIZE 1024

struct keyValuePair *hashmap;

void hashmap_new(){
	hashmap = (struct keyValuePair*) calloc(HASHMAP_SIZE, sizeof(struct keyValuePair));
}

unsigned long hashmap_hash(char* str){

	//DJB2 hash by Dan Bernstein
	unsigned long hash = 5381;
    int c;

    *str = (unsigned char) *str;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void hashmap_put(char* word){

	unsigned int hash = (unsigned int)(hashmap_hash(word) % HASHMAP_SIZE);

	//If the node in hashmap is empty
	if(hashmap[hash].in_use != 1){
		struct node* root = linkedlist_create(word);

		struct keyValuePair *pair;
		pair = (struct keyValuePair *) malloc( sizeof(struct keyValuePair));

		pair->in_use = 1;
		pair->node = root;

		hashmap[hash] = *pair;
	//If the node in hashmap already has a linked list
	}else{
		//Check if the word exists in the linked list already
		struct node* foundNode = linkedlist_find(hashmap[hash].node, word);

		//If it does increment the count
		if(strcmp(foundNode->word, "") != 0){
			foundNode->count++;
		//If it doesn't add it to the end of the linked list
		}else{
			struct node *child;
			child = (struct node *) malloc( sizeof(struct node));

			child->next = 0;
			child->word = word;
			child->count = 1;

			linkedlist_addChild(hashmap[hash].node, child);
		}
	}
}

void findPlaceInLinkedList(struct node* linkedlist_node, struct node* previous_node, struct node* child){
	//When ordering the words by count. Find by recursion the right node
	if(child->count < linkedlist_node->count){
		if(linkedlist_node->next == 0){	
			linkedlist_node->next = child;
		}else{
			findPlaceInLinkedList(linkedlist_node->next, linkedlist_node, child);
		}
	}else{
		linkedlist_addAfter(previous_node, child);
	}
}

void hashmap_print(){
	//ORDER THE WORDS BY COUNT
	struct node* root = linkedlist_create(NULL);

	int linkedlist_index = 1;
	struct node* linkedlist_node = root;
	linkedlist_node->count = 9999999; //Just a very large number

	for(int i = 0; i < HASHMAP_SIZE; i++){
		if(hashmap[i].node != NULL){

			struct node *currentNode = hashmap[i].node;

			while(true){
				struct node *currentNodeCopy;
				currentNodeCopy = (struct node *) malloc( sizeof(struct node));

				//Copy to a new reference and add to the sorted linked list
				memcpy(currentNodeCopy, currentNode, sizeof(struct node));
				findPlaceInLinkedList(linkedlist_node, NULL, currentNodeCopy);

				if(currentNode->next != NULL){
					currentNode = currentNode->next;
				}else{
					break;
				}
			}
				
		}
	}

	printf("\nThe 100 most common words:\n");

	//PRINT THE LINKED LIST

	linkedlist_node = root;
	if(linkedlist_node->next == 0){
		printf("No words in text file!");
		return;
	}

	struct node *currentNode = linkedlist_node->next;
	int i = 1;

	while(i <= 100){
		printf("%02d - %s - %d\n", i, currentNode->word, currentNode->count);
		
		if(currentNode->next != NULL){
			currentNode = currentNode->next;
		}else{
			break;
		}
		i++;
	}
}
