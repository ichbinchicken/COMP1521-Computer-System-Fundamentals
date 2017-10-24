// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017
// Modified by Ziming Zheng z5052592

#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"

// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

// PTE = Page Table Entry

typedef struct _pte PTE;

struct _pte {
   char status;      // NOT_USED, IN_MEMORY, ON_DISK
   char modified;    // boolean: changed since loaded *
   int  frame;       // memory frame holding this page
   int  accessTime;  // clock tick for last access LRU  *
   int  loadTime;    // clock tick for last time loaded FIFO
   int  nPeeks;      // total number times this page read *
   int  nPokes;      // total number times this page modified *
   int  pno;         // page #
   PTE  *next;       // pointer pointing to the next PTE
   PTE  *before;     // pointer pointing to the before PTE
};

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE  *PageTable;     // array of page table entries
static PTE  *prePage;       // the page one before the current one
static PTE  *curr;          // temporary current pag
static PTE  *first;         // pointer pointing to the first PTE
static PTE  *last;          // pointer pointing to the last PTE
static PTE  *tmp;           // pointer pointing to the victim PTE
static int  nPages;         // # entries in page table
static int  replacePolicy;  // how to do page replacement
// Forward refs for private functions

static int findVictim(int);

// initPageTable: create/initialise Page Table data structures

void initPageTable(int policy, int np)
{
   PageTable = malloc(np * sizeof(PTE));
   if (PageTable == NULL) {
      fprintf(stderr, "Can't initialise Memory\n");
      exit(EXIT_FAILURE);
   }
   replacePolicy = policy;
   nPages = np;
   first = NULL;
   last = NULL;
   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      p->status = NOT_USED;
      p->modified = 0;
      p->frame = NONE;
      p->accessTime = NONE;
      p->loadTime = NONE;
      p->nPeeks = p->nPokes = 0;
      p->pno = i;
      p->next = NULL;
      p->before = NULL;
   }
}

// requestPage: request access to page pno in mode
// returns memory frame holding this page
// page may have to be loaded
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

int requestPage(int pno, char mode, int time)
{
   if (pno < 0 || pno >= nPages) {
      fprintf(stderr,"Invalid page reference\n");
      exit(EXIT_FAILURE);
   }
   PTE *p = &PageTable[pno];
   int fno; // frame number
   switch (p->status) {
   case NOT_USED:
   case ON_DISK:
      // add stats collection
      countPageFault();
      fno = findFreeFrame();
      if (fno == NONE) {
         int vno = findVictim(time);
#ifdef DBUG
         printf("Evict page %d\n",vno);
#endif
         // if victim page modified, save its frame
         // collect frame# (fno) for victim page
         // update PTE for victim page
         // - get page #
         // - new status
         // - no longer modified
         // - no frame mapping
         // - not accessed, not loaded
         // - pointers pointing to NULL
         if (first->modified == 1) saveFrame(first->frame);
         fno = first->frame;
         tmp = first;
         first = tmp->next;
         first->before = NULL;
         tmp->next = NULL;
         tmp->before = NULL;
         tmp->pno = vno; // always equal, just make compiler happy, doesn't want to modify jas's code
         tmp->status = ON_DISK;
         tmp->modified = 0;
         tmp->frame = NONE;
         tmp->loadTime = NONE;
         tmp->accessTime = NONE;
      }
#ifdef DBUG
      printf("Page %d given frame %d\n",pno,fno);
#endif
      // load page pno into frame fno
      // update PTE for page
      // - new status
      // - not yet modified
      // - associated with frame fno
      // - just loaded
      loadFrame(fno, pno, time);
      p->status = IN_MEMORY;
      p->frame = fno;
      p->loadTime = time;
      // when page is loaded, it will be at the end of list
      if (time == 0)  { // empty list
          first = p;
          last = p;
          prePage = p;
          //p->next = NULL; initilised in initPageTable function
          //p->before = NULL; initilised in initPageTable function
      } else { // if not empty
          prePage->next = p;
          p->before = prePage;
          last = p;
          prePage = p;
          p->next = NULL;  
      }
      break;
   case IN_MEMORY:
      // arranging the order of accessing time within page frame
      // only used in lru method
      if (replacePolicy == REPL_LRU) {
        // if the last page is accessed, doing nothing
        // otherwise doing followings
        if (p != last) {
            curr = last;
            curr->next = p;
            last = p;
            prePage = p; 
            // if the first node is accessed, put it to the end 
            if (first == last) {
                p->before = curr;
                first = p->next;
                first->before = NULL;
            // if not first node accessed
            } else {
                p->next->before = p->before;
                p->before->next = p->next;
                p->before = curr;
            }
            p->next = NULL;
        }
      }
      // add stats collection
      countPageHit();
      break;
   default:
      fprintf(stderr,"Invalid page status\n");
      exit(EXIT_FAILURE);
   }
   if (mode == 'r')
      p->nPeeks++;
   else if (mode == 'w') {
      p->nPokes++;
      p->modified = 1;
   }
   p->accessTime = time;
   return p->frame;
}

// findVictim: find a page to be replaced
// uses the configured replacement policy

static int findVictim(int time)
{
   int victim = 0;
   switch (replacePolicy) {
   case REPL_LRU:
   case REPL_FIFO:
      victim = first->pno; //only return the pno of first node
      break;
   case REPL_CLOCK:
      return 0;
   }
   return victim;
}

// showPageTableStatus: dump page table
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

void showPageTableStatus(void)
{
   char *s;
   printf("%4s %6s %4s %6s %7s %7s %7s %7s\n",
          "Page","Status","Mod?","Frame","Acc(t)","Load(t)","#Peeks","#Pokes");
   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      printf("[%02d]", i);
      switch (p->status) {
      case NOT_USED:  s = "-"; break;
      case IN_MEMORY: s = "mem"; break;
      case ON_DISK:   s = "disk"; break;
      }
      printf(" %6s", s);
      printf(" %4s", p->modified ? "yes" : "no");
      if (p->frame == NONE)
         printf(" %6s", "-");
      else
         printf(" %6d", p->frame);
      if (p->accessTime == NONE)
         printf(" %7s", "-");
      else
         printf(" %7d", p->accessTime);
      if (p->loadTime == NONE)
         printf(" %7s", "-");
      else
         printf(" %7d", p->loadTime);
      printf(" %7d", p->nPeeks);
      printf(" %7d", p->nPokes);
      printf("\n");
   }
}
