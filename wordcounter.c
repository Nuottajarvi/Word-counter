#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hashmap.h"
#include "linkedlist.h"

int main(int argc, char *argv[]){
	char ch;
	FILE *fp;

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("Error while opening the file.\n");
		return 0;
	}
 

	hashmap_new();
	
	char* word = (char*)malloc(64 * sizeof(char)); //Assume that there's no longer words than 64 characters.
	memset(word, 0, 64);
	int wordIndex = 0;

	while( ( ch = fgetc(fp) ) != EOF ){		
		//if character is a letter
		int charAlpha = isalpha(ch);
		//if character is an apostrophe
		if(ch == '\''){
			charAlpha = 1;
		}

		if(charAlpha == 0){
			//if there is some word written already
			if(word[0] != 0){

				char* wordToPut = (char*) malloc(64 * sizeof(char));
				strcpy(wordToPut, word);
				hashmap_put(wordToPut);
				memset(word, 0, 64);
				wordIndex = 0;
			}		
		}else{
			word[wordIndex] = tolower(ch); //Convert char to lowercase and put to array
			wordIndex++;
		}
	}	
 
	fclose(fp);

	hashmap_print();

	return 0;
}

