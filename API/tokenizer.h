#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 1024

int tokenize(char * message,char * tokens []){
    int count = 0;
    char *token = strtok(message, "|");//string, delimiter

    while(token != NULL){
        tokens[count++] = token;
        token = strtok(NULL, "|");

    }

    return count;

}



void parse(const char *message){

    char buffer [MAX_BUFFER];

    strncpy(buffer, message, sizeof(buffer) - 1);
    buffer [sizeof(buffer) - 1] = '\0';

    char *fields [MAX_BUFFER];

    int count = tokenize(buffer, fields);

    if (count == 0){

        printf("Invalid format");
        return;
    }
/*
    for (int i = 0 ; i< count; i++){

        printf("field %d : %s\n",i,fields[i]);
    }

*/

}