#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//declare methods
char * function();
char * tokenize(char * string);

int main(int argc, char* argv[]) {

	//ask for the string
    //printf("Enter string here: ");
    //scanf("%s", file);
	
	//Create the string
	int len = strlen( argv[1] );
	char * str = calloc( len, sizeof(char)* len );
	strcpy(str, argv[1]);

	tokenize(str);

	free(str);
	return 0;
}

char * tokenize(char * string) {
	//store final string for return
	char * result;
	char letter = string[0];	//Extract our letter
	int counter = 0;	//keep track of freq.
	int i = 0;
	
	//Prepare key
	char key[2];
	memset(key, '\0', 10);

	//Prepare the string for strcat()
	//Note: strcat() stops @ first \0
	char tokenStr[256];
	memset(tokenStr, '\0', 256);


	//go through the rest of the string to tokenize
	for (; i <= strlen(string); i++) {

		//Check for spaces
		if ( !isalpha(string[i]) && string[i] != '\0' ) {
			return "error";
		}

		//if we found the next letter
		if (letter != string[i]) {
			
			//printf("letter: %c\n", letter);
			//printf("counter: %d\n", counter);

			//Create key
			char str[5];
			snprintf(str, sizeof(str), "%d", counter);
			char * test = str;
			//printf("\n char: %s", test);

			//printf("test: %d", test);
			
			//Concatenate key
			key[0] = letter;
			strcat(key, test);

			//printf("\nKey: %s check\n", key);

			//Concatenate
			strcat(tokenStr, key);

			//rinse and repeat
			letter = string[i];
			test = calloc(strlen(test), sizeof(test) );
			memset(key, '\0', 2);

			//printf("\nnew letter: %c", string[i]);

			counter = 0;		//reset counter

			//printf("\nString: %s", tokenStr);
			//printf("\n-----------------------------------\n");
			free(test);

		}
		counter++;
	}

	//printf("%s", tokenStr);

	result = tokenStr;		//convert back to char *

	//Check if the compressed string is
	//longer, then return original.
	if ( strlen(result) > strlen(string) ) {
		return string;
	}

	printf("%s\n", result);
	return result;	//else
}