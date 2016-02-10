#ifndef LINKEDLIST
#define LINKEDLIST

struct node {
	char const* word;
	unsigned int count;
	struct node *next;
};

struct node * linkedlist_create(char* word);

void linkedlist_addChild(struct node* root, struct node* child);

struct node * linkedlist_find(struct node* node, char* word);

#endif