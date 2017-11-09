#include <stdio.h>
#include <stdlib.h>
typedef struct _student {
    int id; char name[99]; float wam;
} Student;
int main (int argc, char **argv) {
    Student stu;
    FILE *fp = fopen(argv[1], "r");
    while (fscanf(fp, "%d:%[^:]:%f\n", &(stu.id), stu.name, &(stu.wam)) != EOF) {
    
        printf("%d:%s:%f\n", stu.id, stu.name, stu.wam);
    }
    fclose(fp);
    return 0;
}
