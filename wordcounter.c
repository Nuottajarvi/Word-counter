#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include "hashmap.h"

int main(int argc, char *argv[]){
	char ch;
	FILE *fp;

	fp = fopen("test.txt"/*argv[1]*/, "r");

	if(fp == NULL){
		printf("Error while opening the file.\n");
	}
 

	hashmap_new();
	
	char* word = (char*)malloc(64 * sizeof(char)); //Assume that there's no longer words than 64 characters.
	memset(word, 0, 64);
	int wordIndex = 0;

	while( ( ch = fgetc(fp) ) != EOF ){

		printf("%c", ch);
		
		//if character is a letter or a number
		int charAlphaNumeric = isalnum(ch);
		//if character is an apostrophe
		if(ch == '\''){
			charAlphaNumeric = 1;
		}

		if(charAlphaNumeric == 0){
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

