#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	
	//char string[500];	//input
	//memset(string, ' ', 500);

	char result[500] = "";	//output
	memset(result, '\0', 500);

    //printf("token: %s\n", token);


    //traverse to rest
    int i = 0;
    for (; i < argc; i++) {
	    int len = strlen(argv[i]);
	    result[i] = argv[i][len-1];
    }

    //truncate the first arg
    int resultLen = strlen(result);
    char * truncate = calloc(resultLen, sizeof(result));    
    int h = 1;

    for (; h < resultLen; h++) {
    	truncate[h-1] = result[h];
    }

    printf("%s\n", truncate);

    free(truncate);
    return 0;
}