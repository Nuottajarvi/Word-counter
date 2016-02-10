#ifndef HASHMAP
#define HASHMAP

struct keyValuePair{
	int in_use;
	struct node *node;
};

void hashmap_new();
unsigned int hashmap_hash(unsigned char *str);
void hashmap_put(char* word);
void hashmap_print();


#endif