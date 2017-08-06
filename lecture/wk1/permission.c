#include <stdio.h>
#include <stdlib.h>
#define READ_OWNER 0400
#define WRITE_OWNER 0200
#define EXECUTE_OWNER 0100
#define READ_GROUP 040
#define WRITE_GROUP 020
#define EXECUTE_GROUP 010
#define READ_OTHERS 04
#define WRITE_OTHERS 02
#define EXECUTE_OTHERS 01

typedef unsigned short Permissions;
int main (int argc, char *argv[]){
    Permissions p = 0;
    if (argc < 2) {
        fprintf(stderr, "usage\n"); 
        exit(EXIT_FAILURE);
    }
    if (argc > 1) {
        if (argv[1][0] == 'r') p = p | READ_OWNER;
        if (argv[1][1] == 'w') p = p | WRITE_OWNER;
        if (argv[1][2] == 'x') p = p | EXECUTE_OWNER;
    }
    
    if (argc > 2) {
        if (argv[2][0] == 'r') p = p | READ_GROUP;
        if (argv[2][1] == 'w') p = p | WRITE_GROUP;
        if (argv[2][2] == 'x') p = p | EXECUTE_GROUP;
    }
    if (argc > 3) {
        if (argv[3][0] == 'r') p = p | READ_OTHERS;
        if (argv[3][1] == 'w') p = p | WRITE_OTHERS;
        if (argv[3][2] == 'x') p = p | EXECUTE_OTHERS;
    }
    printf("Owner:");
    if (p & READ_OWNER) printf(" read");
    if (p & WRITE_OWNER) printf(" write");
    if (p & EXECUTE_OWNER) printf(" execute");
    printf("\n");
    
    return 0; 
}
