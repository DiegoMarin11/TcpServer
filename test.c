#include <stdlib.h>
#include <tokenizer.h>
#include <string.h>


int main(){
    //GET|ENTITY|ATTRIBUTES 

    char message[] = "GET|1|BRACA|GUSTA";

    printf("Parser... %s", message);

    parse(message);

    return 0;
}