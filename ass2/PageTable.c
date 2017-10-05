// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

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
   int  pno;
   PTE  *next;
   PTE  *before;
   // add more fields here, if needed ...
};

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE  *PageTable;     // array of page table entries
static PTE  *prePage;       // the page one before the current one
static PTE  *curr;          // temporary current pag
static PTE  *first;
static PTE  *last;
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
         // TODO:
         // if victim page modified, save its frame
         // collect frame# (fno) for victim page
         // update PTE for victim page
         // - new status
         // - no longer modified
         // - no frame mapping
         // - not accessed, not loaded
      }
      printf("Page %d given frame %d\n",pno,fno);
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
      if (time == 0)  {
          first = p;
          last = p;
          prePage = p;
          //p->next = NULL; initilised in initPageTable function
          //p->before = NULL; initilised in initPageTable function
      } else {
          prePage->next = p;
          p->before = prePage;
          last = p;
          prePage = p;
          p->next = NULL;  //in case 
      }
      break;
   case IN_MEMORY:
      if (replacePolicy == REPL_LRU) {
          curr = last;
          curr->next = p;
          last = p;
          prePage = p;  //in case
          if (first == last) {
              p->before = curr;
              first = p->next;
              first->before = NULL;
          } else {
              p->next->before = p->before;
              p->before->next = p->next;
              p->before = curr;
          }
          p->next = NULL;
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
#if 1
   curr = first;
   while (curr != NULL) {
       printf("(%d)->", curr->pno);
       curr = curr->next;
   }
   printf("\n");
#endif
   return p->frame;
}

// findVictim: find a page to be replaced
// uses the configured replacement policy

static int findVictim(int time)
{
   int victim = 0;
   switch (replacePolicy) {
   case REPL_LRU:
      // TODO: implement LRU strategy
      break;
   case REPL_FIFO:
      // TODO: implement FIFO strategy
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
