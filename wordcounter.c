#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "hashmap.h"
#include "linkedlist.h"

int main(int argc, char *argv[]){

	//START TIMING
	clock_t t;
	t = clock();

	//START READING FILE
	char ch;
	FILE *fp;

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("Error while opening the file.\n");
		return 0;
	}
 

	hashmap_new();
	
	//SET WORD A 64 CHAR LONG EMPTY STRING
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

		//If character is not letter or apostrophe
		if(charAlpha == 0){
			//if there is some word written already
			if(word[0] != 0){

				//Copy the word to new memoryslot and add the reference to hashmap
				char* wordToPut = (char*) malloc(64 * sizeof(char));
				strcpy(wordToPut, word);
				hashmap_put(wordToPut);
				memset(word, 0, 64);
				wordIndex = 0;
			}
		//If character is a letter or apostrophe	
		}else{
			//Convert char to lowercase and put to array
			word[wordIndex] = tolower(ch); 
			wordIndex++;
		}
	}	
 
	fclose(fp);

	hashmap_print();

	//STOP TIMING AND TELL TIME
	t = clock() - t;
	printf("\nexecution time: %.0fms", (((float)t)/CLOCKS_PER_SEC)*1000);

	return 0;
}

