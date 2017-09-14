//
//  COMP1927 Assignment 1 - Vlad: the memory allocator
//  allocator.c ... implementation
//
//  Created by Liam O'Connor on 18/07/12.
//  Modified by John Shepherd in August 2014, August 2015
//  Copyright (c) 2012-2015 UNSW. All rights reserved.
//

#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FREE_HEADER_SIZE  sizeof(struct free_list_header)  
#define ALLOC_HEADER_SIZE sizeof(struct alloc_block_header)  
#define MAGIC_FREE     0xDEADBEEF
#define MAGIC_ALLOC    0xBEEFDEAD

#define BEST_FIT       1
#define WORST_FIT      2
#define RANDOM_FIT     3

typedef unsigned char byte;
typedef u_int32_t vsize_t;
typedef u_int32_t vlink_t;
typedef u_int32_t vaddr_t;

typedef struct free_list_header {
   u_int32_t magic;  // ought to contain MAGIC_FREE
   vsize_t size;     // # bytes in this block (including header)
   vlink_t next;     // memory[] index of next free block
   vlink_t prev;     // memory[] index of previous free block
} free_header_t;
typedef free_header_t * FreeHeader;

typedef struct alloc_block_header {
   u_int32_t magic;  // ought to contain MAGIC_ALLOC
   vsize_t size;     // # bytes in this block (including header)
} alloc_header_t;
typedef alloc_header_t * AllocHeader;

// Global data

static byte *memory = NULL;   // pointer to start of allocator memory
static vaddr_t free_list_ptr; // index in memory[] of first block in free list
static vsize_t memory_size;   // number of bytes malloc'd in memory[]
static u_int32_t strategy; // allocation strategy (by default BEST_FIT)


// Private functions

static void vlad_merge();
static int testThreshold(u_int32_t headerSize, u_int32_t n);

// Input: size - number of bytes to make available to the allocator
// Output: none              
// Precondition: Size >= 1024
// Postcondition: `size` bytes are now available to the allocator
// 
// (If the allocator is already initialised, this function does nothing,
//  even if it was initialised with different size) 

void vlad_init(u_int32_t size)
{
   if(memory ==NULL) {
      memory_size = 1;
      while(memory_size < size) memory_size = 2 * memory_size;
      //after loop: the smallest value which is bigger than size.
      
      if(memory_size < 1024) memory_size = 1024;
      size = memory_size ; //maybe don't need it 
      memory = malloc(memory_size);
      FreeHeader ptr = (free_header_t *)memory;
      if(memory ==NULL) {
         fprintf(stderr, "vlad_init: Insufficient memory\n");
         exit(EXIT_FAILURE);
      }
      ptr->magic = MAGIC_FREE;
      ptr->size = memory_size;
      ptr->next = 0;
      ptr->prev = 0;
      free_list_ptr = (vaddr_t)0;
   }
   strategy = BEST_FIT;
}


// Input: n - number of bytes requested
// Output: p - a pointer, or NULL
// Precondition: n < size of largest available free block
// Postcondition: If a region of size n or greater cannot be found, p = NULL
//                Else, p points to a location immediately after a header block
//                      for a newly-allocated region of some size >= 
//                      n + header size.

void *vlad_malloc(u_int32_t n)
{
   void * vlad_ptr;
   byte * vlad_ptr0;
   FreeHeader curr0;
   u_int32_t headerSize;
   byte * vlad_split;
   //split pointers:
   FreeHeader free_split;
   FreeHeader last; 
   FreeHeader before;
   FreeHeader after;
   FreeHeader before2;
   FreeHeader after2;
   FreeHeader free_one;
   FreeHeader free_one0;
   FreeHeader free_one2;
   AllocHeader ptrA;

   //n = round up the size
   if (n % 4==1) n = n + 3;
   else if (n % 4 ==2) n = n + 2;
   else if (n % 4 ==3) n = n + 1;
   if (n < 8) n = 8 ;
  
   curr0 = (free_header_t *)&memory[free_list_ptr];
   
   if (curr0->magic != MAGIC_FREE) {
      fprintf(stderr, "vlad_alloc error 1: Meomory corruption\n");
      exit(EXIT_FAILURE);
   }
  
   vlad_ptr = &memory[free_list_ptr];
   vlad_ptr0 = &memory[free_list_ptr];
   headerSize = curr0->size;                        // the first free block size
   vlad_ptr0 = &memory[curr0->next]; 
   curr0 = (free_header_t *) vlad_ptr0;
  //printf("headerSize is %d\n", headerSize);

   while (vlad_ptr0 != &memory[free_list_ptr]) {
      //printf("curr0->size is %d\n", curr0->size);
      if (curr0->magic != MAGIC_FREE) {
         fprintf(stderr, "vlad_alloc error 2: Meomory corruption\n");
         exit(EXIT_FAILURE);
      }
      if (curr0->size >= (n+ALLOC_HEADER_SIZE)) {
         if (curr0->size < headerSize || headerSize < (n+ALLOC_HEADER_SIZE)) {
            headerSize = curr0->size;
            vlad_ptr = vlad_ptr0;
         }
      }
      vlad_ptr0 = &memory[curr0->next];
      curr0 = (free_header_t *)&memory[curr0->next];
   }
   // after loop: the smallest size exclude the first one
   // vlad_ptr0 return to &memory[free_list_ptr]
   // curr0 return to (free_header_t *)&meomory[free_list_ptr]
   
   if (headerSize == curr0->size) {
      if (headerSize < n+ALLOC_HEADER_SIZE) {
         vlad_ptr = NULL;
         return vlad_ptr;
      }
   }
   //now headSize = smallest enough size
   vlad_split = vlad_ptr;
   curr0 = (free_header_t *)&memory[free_list_ptr];
   free_one = (free_header_t *) vlad_ptr;
   if (testThreshold(headerSize, n) == 1) {
      vlad_split = vlad_split + n + ALLOC_HEADER_SIZE;
      free_split = (free_header_t *)vlad_split; 
      //initial split header:
      free_split->magic = MAGIC_FREE;
      free_split->size = headerSize - n - ALLOC_HEADER_SIZE;
      headerSize = n + ALLOC_HEADER_SIZE; //arrange allocated size
      if (curr0->next != free_list_ptr || curr0->next != curr0->prev) { //if there are many free blocks in the memory
         if (vlad_ptr == &memory[free_list_ptr]) { //if split the first block
            u_int32_t index1 = vlad_split - &memory[0];
            last = (free_header_t *)&memory[curr0->prev];
            last->next = index1;
            if (curr0->next == curr0->prev && curr0->next !=free_list_ptr) {
               last->prev = index1;
            }
            free_split->next = curr0->next;
            free_split->prev = curr0->prev;
         } else if (vlad_ptr == &memory[curr0->prev]) { //if split the last block
            u_int32_t index0 = vlad_split - &memory[0];
            //printf("index0 %d\n", index0);
            free_split->next = free_list_ptr;
            //printf("free_split->next %d\n", free_split->next);
            last = (free_header_t *)&memory[curr0->prev];
            free_split->prev = last->prev;
            if (curr0->next == curr0->prev && curr0->next !=free_list_ptr) { 
               curr0->next = index0;
               curr0->prev = index0;
            } else {
               curr0->prev = index0;
               FreeHeader before3 = (free_header_t *)&memory[free_list_ptr];
            while (vlad_ptr != &memory[before3->next]) {
               before3 = (free_header_t *)&memory[before3->next];
            }
            before3->next = index0;
            }
         } else {                                      //if split the middle block
            before = curr0;
            after = curr0;
            while (vlad_ptr != &memory[before->next]) {
               before = (free_header_t *)&memory[before->next];

            }
            while (vlad_ptr != &memory[after->prev]) {
               after = (free_header_t *)&memory[after->next];
            }
            if (before->magic != MAGIC_FREE) {
               fprintf(stderr, "vlad_alloc error 3: Meomory corruption\n");
               exit(EXIT_FAILURE);
            }
            if (after->magic != MAGIC_FREE) {
               fprintf(stderr, "vlad_alloc error 4: Meomory corruption\n");
               exit(EXIT_FAILURE);
            }
            before2 = (free_header_t *)&memory[before->prev];
            after2 = (free_header_t *)&memory[after->next];
            if (before2->magic != MAGIC_FREE) {
               fprintf(stderr, "vlad_alloc error 5: Meomory corruption\n");
               exit(EXIT_FAILURE);
            }
            if (after2->magic != MAGIC_FREE) {
               fprintf(stderr, "vlad_alloc error 6: Meomory corruption\n");
               exit(EXIT_FAILURE);
            }
            free_split->next = after2->prev;
            free_split->prev = before2->next;
         }
      } else if (curr0->prev == curr0->next && curr0->next == free_list_ptr) { //if there is only one block in the memory
            free_split->next = free_list_ptr + n + ALLOC_HEADER_SIZE;
            free_split->prev = free_list_ptr + n + ALLOC_HEADER_SIZE;
      }
   } else if (testThreshold(headerSize,n) == 0) {
      //if it is the last free region and can't be splited, return NULL
      if ((curr0->next == free_list_ptr) && (curr0->prev == free_list_ptr) ) { 
         vlad_ptr = NULL;
         return vlad_ptr;
      }
      free_one0 = (free_header_t *)&memory[free_one->prev];
      free_one2 = (free_header_t *)&memory[free_one->next];
      free_one2->prev = free_one->prev;
      free_one0->next = free_one->next;
      //free_one2->next doesn't change
      //free_one0->prev doesn't change
   }
   
   //if (vlad_split != vlad_ptr) {
//         printf("free_split->next is %d\nfree_split->prev is %d\nfree_split->size is %d\n", free_split->next, free_split->prev, free_split->size);
 //  }
   
   //set new free_list_ptr value
   if (vlad_ptr == &memory[free_list_ptr]) {
      if (vlad_split == vlad_ptr) { //if is not splitted
         free_list_ptr = free_one->next;
      } else {
         free_list_ptr = free_list_ptr + n + ALLOC_HEADER_SIZE;
      }
   } /*else if (vlad_ptr != &memory[free_list_ptr]){
      if (vlad_split == vlad_ptr) {//if is not splitted
         free_list_ptr = free_one->next;
      }
   }*/

   ptrA = (alloc_header_t *)vlad_ptr;
   ptrA->magic = MAGIC_ALLOC;
   ptrA->size = headerSize;
   
   return ((void*)(vlad_ptr + ALLOC_HEADER_SIZE));
}


// Input: object, a pointer.
// Output: none
// Precondition: object points to a location immediately after a header block
//               within the allocator's memory.
// Postcondition: The region pointed to by object has been placed in the free
//                list, and merged with any adjacent free blocks; the memory
//                space can be re-allocated by vlad_malloc

void vlad_free(void *object)
{
   u_int32_t offset_index;
   u_int32_t alloc_size;
   u_int32_t index;
   
   FreeHeader curr0;
   AllocHeader alloc0;
   FreeHeader free0;
   FreeHeader last;
   FreeHeader before;
   
   offset_index = (byte *)object - &memory[0] - ALLOC_HEADER_SIZE;
   object = &memory[offset_index];
   //object points to the first byte of alloc now
   if (offset_index >= memory_size) {
      fprintf(stderr, "vlad_free: Attempt to free via invalid pointer\n");
      exit(EXIT_FAILURE);
   }
   if (*(u_int32_t *)object != MAGIC_ALLOC) {
      fprintf(stderr, "vlad_free: Attempt to free non-allocated memory\n");
      exit(EXIT_FAILURE);
   }
   //now let's free
   curr0 = (free_header_t *)&memory[free_list_ptr];
   before = (free_header_t *)&memory[free_list_ptr];
   last = (free_header_t *)&memory[free_list_ptr];
   alloc0 = (alloc_header_t *)object;
   alloc_size = alloc0->size;
   free0 = (free_header_t *)object;
   free0->magic = MAGIC_FREE;
   free0->size = alloc_size;
   
   if (curr0->prev == curr0->next && curr0->next == free_list_ptr) {//only one block
      curr0->prev = offset_index;
      curr0->next = offset_index;
      free0->prev = free_list_ptr;
      free0->next = free_list_ptr;
      if (offset_index < free_list_ptr) {
         free_list_ptr = offset_index;
      }
   } else { //other cases
      if (offset_index > free_list_ptr) { //if offset_index is after free_list_ptr
         index = curr0->next;
         curr0 = (free_header_t *)&memory[curr0->next];
         while (offset_index > index) {
            index = curr0->next;
            curr0 = (free_header_t *)&memory[curr0->next];
         }
         while (before->next != index){
            before = (free_header_t *)&memory[before->next];
         }
         free0->next = index;
         free0->prev = curr0->prev;
         curr0->prev = offset_index;
         before->next = offset_index;
         //curr0->next doesn't change
      } else if (offset_index < free_list_ptr) {//if offset_index is before free_list_ptr
         while (last->prev != free_list_ptr) {
            last = (free_header_t *)&memory[last->next];
//         printf("last->next is %d\n", last->next);
         }
         free0->prev = curr0->prev;
         free0->next = free_list_ptr;
         curr0->prev = offset_index;
         //curr0->next doesn't change
         free_list_ptr = offset_index;
         last->next = free_list_ptr;
         
      }

   }
/*   printf("free0->prev is %d\n", free0->prev);
   printf("free0->next is %d\n", free0->next);*/
   vlad_merge();
}

// Input: current state of the memory[]
// Output: new state, where any adjacent blocks in the free list
//            have been combined into a single larger block; after this,
//            there should be no region in the free list whose next
//            reference is to a location just past the end of the region

static void vlad_merge()
{
   FreeHeader curr0;
   FreeHeader curr1;
   FreeHeader curr2;
   byte * scanp;
   u_int32_t offset_index;
   u_int32_t diff;
   
//   printf("For merge: free_list_ptr is %d\n", free_list_ptr);
   curr0 = (free_header_t *)&memory[free_list_ptr];
//   printf("before merge: curr0->next is %d\n", curr0->next);
//   printf("before merge: curr0->prev is %d\n", curr0->prev);

   curr0 = (free_header_t *)&memory[curr0->next];
//   printf("*before merge: curr0->next is %d\n", curr0->next);
//   printf("*before merge: curr0->prev is %d\n", curr0->prev);
   scanp = &memory[curr0->next];
   
   while (scanp != &memory[free_list_ptr]) {
      curr1 = (free_header_t *)scanp;
      curr2 = (free_header_t *)&memory[curr1->next];
//      printf("curr1->next is %d\n", curr1->next);
//      printf("curr1->prev is %d\n", curr1->prev);
      
      offset_index = scanp - &memory[0];
      diff = offset_index - curr0->size;
//      printf("offset is %d\n", offset_index);
      
      if (diff == curr1->prev) {
         curr0->next = curr1->next;
         //curr0->prev doesn't change
         curr2->prev = curr1->prev;
         curr0->size = curr0->size + curr1->size;
      } else {
         curr0 = (free_header_t *)&memory[curr0->next];
      }
      scanp = &memory[curr0->next];
//      printf("curr0->next is %d\n", curr0->next);
   }
   
   if (scanp == &memory[free_list_ptr]) {
      curr0 = (free_header_t *)&memory[free_list_ptr];
      scanp = &memory[curr0->next];
      curr1 = (free_header_t *)scanp;
      curr2 = (free_header_t *)&memory[curr1->next];
      
      offset_index = scanp - &memory[0];
      if ((offset_index - curr0->size) == curr1->prev) {
         curr0->next = curr1->next;
         curr2->prev = curr1->prev;
         curr0->size = curr0->size + curr1->size;
      }
   }
//   printf("after merge: curr0->next is %d\n", curr0->next);
//     printf("before merge: curr0->prev is %d\n", curr0->prev);
}

// Stop the allocator, so that it can be init'ed again:
// Precondition: allocator memory was once allocated by vlad_init()
// Postcondition: allocator is unusable until vlad_int() executed again

void vlad_end(void)
{
   free(memory);
   memory = NULL;
}


// Precondition: allocator has been vlad_init()'d
// Postcondition: allocator stats displayed on stdout

void vlad_stats(void)
{
   printf("free_list_ptr is %d\n", free_list_ptr);
   

   //printf("vlad_stats() won't work until vlad_malloc() works\n");
   return;
}

static int testThreshold(u_int32_t headerSize, u_int32_t n)
{
   u_int32_t Threshold = ALLOC_HEADER_SIZE+n+2*FREE_HEADER_SIZE;
   if (headerSize >= Threshold) return 1;
   else return 0;
}






