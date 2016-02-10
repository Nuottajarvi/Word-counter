#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "hashmap.h"

#define HASHMAP_SIZE 16

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

	if(hashmap[hash].in_use != 1){
		struct node* root = linkedlist_create(word);

		struct keyValuePair *pair;
		pair = (struct keyValuePair *) malloc( sizeof(struct keyValuePair*));

		pair->in_use = 1;
		pair->node = root;

		hashmap[hash] = *pair;
	}else{
		struct node* foundNode = linkedlist_find(hashmap[hash].node, word);

		if(strcmp(foundNode->word, "") != 0){
			foundNode->count++;
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

void hashmap_print(){
	for(int i = 0; i < HASHMAP_SIZE; i++){
		if(hashmap[i].node != NULL){

			struct node *currentNode = hashmap[i].node;

			while(true){
				printf("%d - %s - %d\n", i, currentNode->word, currentNode->count);

				if(currentNode->next != NULL){
					currentNode = currentNode->next;
				}else{
					break;
				}
			}
				
		}
	}
}