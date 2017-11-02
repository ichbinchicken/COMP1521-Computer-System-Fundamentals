#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

struct list {
	int x;
	struct list *next;
};

struct lrep {
    int nitems;
	struct list *head;
	struct list *tail;
	void (*insert)(int insertee, struct lrep * head);
	void (*delete)(int deletee,  struct lrep * head);
	void (*fwrite)(char *s, struct lrep * lrep);
	void (*printl)(struct lrep * head);
	struct list * (*create_node)(int val);
};


struct lrep *lrep;
//creates a node
struct list *CN(int val){
	struct list *n = malloc(sizeof(struct list));
	assert(n != NULL);
	n->x = val;
	n->next = NULL;
	return n;
}
void show(struct lrep *lrep) {
    struct list *curr = lrep->head;
    while (curr != NULL) {
        printf("%d->", curr->x);
        curr = curr->next; 
   }
   printf("X\n");
}
//INSERTION SORT
void IN(int x, struct lrep * lrep){
    struct list *new = lrep->create_node(x);
    if (lrep->head == NULL && lrep->tail == NULL) {
        lrep->head = new;
        lrep->tail = new;
    } else if (x >= lrep->tail->x) {
        lrep->tail->next = new;
        lrep->tail = lrep->tail->next;
    } else if (x <= lrep->head->x) {
        new->next = lrep->head;
        lrep->head = new;
    } else {
        struct list *curr = lrep->head->next;
        struct list *prev = lrep->head;
        struct list *after = lrep->head->next->next;
        while (curr != lrep->tail) {
            if (x >= prev->x && x <= curr->x) {
                prev->next = new;
                new->next = curr;
                break;
            } else if (x >= curr->x && x <= after->x) {
                curr->next = new;
                new->next = after;
                break;
            }
            prev = prev->next;
            after = after->next;
            curr = curr->next;
        }       
    }
    lrep->nitems ++;
    //show(lrep); 
}

// FIND AND REMOVE ElEM
void DEL(int x, struct lrep * lrep){
    struct list *curr = lrep->head;
    struct list *prev = NULL;
    while (curr != NULL) {
        if (lrep->head->x == x && curr == lrep->head) {
            lrep->head = curr->next;
            free(curr);
            break;
        } else if (lrep->tail->x == x && curr == lrep->tail) {
            lrep->tail = prev;
            free(curr);
            break;
        } else if (curr->x == x) {
            prev->next = curr->next;
            free(curr);
            break;
        }
        if (prev == NULL) prev = lrep->head;
        else prev = prev->next;
        curr = curr->next;
    }
    lrep->nitems --;
}

//TODO CREATE AND WRITE SPACE SEPARATED ELEMS TO FILE SPECIFIED AS FILE NAME WITH A NEWLINE AT END
void WRITE(char * filename, struct lrep * lrep){
    char buf[2*lrep->nitems+1];
    struct list *curr = lrep->head;
    int i = 0;
    while (curr != NULL) {
        buf[i++] = curr->x + '0'; //important
        buf[i++] = ' ';
        curr = curr->next;   
        printf("i: %d\n", i);
    }
    buf[i-1] = '\n';
    buf[i] = 0;
    
    FILE* fp = fopen(filename, "w+");
    if (!fp) {
        fprintf(stderr, "failed1");
        exit(1);
    }
    int num_buf = fwrite(buf, 1, i, fp);
    if (num_buf == EOF) {
        fprintf(stderr, "failed2");
        exit(1);
    }
    fclose(fp);
}

//TODO WRITE ELEM TO FILE
void PRINTL(struct lrep * lrep){
	printf("write print\n");
	exit(0);
}

int main(void){

	//init lrep
	lrep = malloc(sizeof(struct lrep));
    lrep->nitems = 0;
	lrep->head = NULL;
	lrep->tail = NULL;
	lrep->insert = &IN;
	lrep->delete = &DEL;
	lrep->fwrite = &WRITE;
	lrep->printl = &PRINTL;
	lrep->create_node = &CN;

	printf("inserting elems\n");
	//insert some elements
	lrep->insert(1, lrep);
	lrep->insert(3, lrep);
	lrep->insert(5, lrep);
	lrep->insert(7, lrep);
	lrep->insert(2, lrep);
	lrep->insert(4, lrep);
	lrep->insert(6, lrep);
	
	printf("inserted\n");

	printf("testing correct insert\n");

	//test order is correct
	struct list *tmp = lrep->head;
	assert(tmp != NULL);
	for (int i = 1; i < 8; i++){
		if (i != tmp->x) {
			printf("LIST NOT ORDERED\n");
			exit(1);
		}
		tmp = tmp->next;
	}

	printf("passed\n");
//	lrep->printl(lrep);

	printf("deleting elems\n");

	//remove even nums
	lrep->delete(2, lrep);
	lrep->delete(4, lrep);
	lrep->delete(6, lrep);

	printf("deleted\n");
	printf("testing correct delete\n");
    printf("nitems:%d\n", lrep->nitems);

	//check even nums removed
	tmp = lrep->head;
	assert(tmp != NULL);

	while (tmp != NULL){
		if (tmp->x % 2 == 0) assert("LIST NOT ODD ELEMS NOT REMOVED CORRECTLY");
		tmp = tmp->next;
	}

	printf("passed\n");

	/* possible bugs lie ahead !!!!!!!!! */
	printf("testing write to file\n if you've gotten this far there may be bugs in this test that you can fix :)\n");
	
	//write to file to test
	FILE *fptr = fopen("test.txt", "w");
	fprintf(fptr, "1 3 5 7\n");
	fclose(fptr);
	

	//use implementation
	lrep->fwrite("test1.txt", lrep);

	fptr = fopen("test.txt", "r");
	FILE *fp = fopen("test1.txt", "r");

	char buf[9];
	char buf1[9];
	//copy contents to buffers
	fscanf(fptr, "%s", buf);
	fscanf(fp, "%s", buf1);

	//compare them
	if (strcmp(buf, buf1)){
		printf("WRITE NOT WORKING\n");
	} else {
	    printf("passed\n");
	    printf("ALL TESTS PASSED, YOU ARE AWESOME! :)\n");
    }
	return 0;
}


