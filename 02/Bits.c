// ADT for Bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by Ziming Zheng z5052592

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Bits.h"

// assumes that an unsigned int is 32 bits
#define BITS_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of bits (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant bits
// words[nwords-1] contains the least significant bits
// Within each Word, bits are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct BitsRep {
   int nwords;   // # of Words
   Word *words;  // array of Words
};

// make a new empty Bits with space for at least nbits
// rounds up to nearest multiple of BITS_PER_WORD
Bits makeBits(int nbits)
{
   Bits new;
   new = malloc(sizeof(struct BitsRep));
   assert(new != NULL);
   int  nwords;
   if (nbits%BITS_PER_WORD == 0)
      nwords = nbits/BITS_PER_WORD;
   else
      nwords = 1+nbits/BITS_PER_WORD;
   new->nwords = nwords;
   // calloc sets to all 0's
   new->words = calloc(nwords, sizeof(Word));
   assert(new->words != NULL);
   return new;
}

// release space used by Bits
void  freeBits(Bits b)
{
   assert(b != NULL && b->words != NULL);
   free(b->words);
   free(b);
}

// form bit-wise AND of two Bits a,b
// store result in res Bits
void andBits(Bits a, Bits b, Bits res)
{
   #if 0
   printf("%d nwords\n", a->nwords);
   printf("%d nwords\n", b->nwords);
   #endif
   int i;
   res->nwords = a->nwords;
   for(i = 0;i < res->nwords;i++) {
       res->words[i] = a->words[i] & b->words[i];
   }
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res)
{
   #if 0
   printf("%d nwords\n", a->nwords);
   printf("%d nwords\n", b->nwords);
   #endif
   int i;
   res->nwords = a->nwords;
   for(i = 0;i < res->nwords;i++) {
       res->words[i] = a->words[i] | b->words[i];
   }

}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res)
{
   #if 0
   printf("%d nwords\n", a->nwords);
   #endif
   int i;
   res->nwords = a->nwords;
   for(i = 0;i < res->nwords;i++) {
       res->words[i] = ~ a->words[i];
   }

}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
   int i  = b->nwords - 1;
   int m,j,k,n;
   char buff[32];
   char newBitseq[33];
   Bits temp = makeBits(BITS_PER_WORD);
   res->nwords = b->nwords;
   while (i >= 0) {
       // save the carry if it isn't the first word
       if (i != 0) {
           m = 31;
           while (m >= 32-shift) {
               if ((b->words[i] & (1u<<m)) != 0) buff[31-m] = '1';
               else buff[31-m] = '0';
               m --;
           }
       }

       //take the rest of non-carring bits
       k = 0;
       j = 32 - shift - 1;
       while (j >= 0) {
           if ((b->words[i] & (1u<<j)) != 0) newBitseq[k] = '1';
           else newBitseq[k] = '0';
           j --;
           k ++;
       }
       #if 0 
       int q;
       for(q = 0;q < k;q++) {
           printf("newBitseq[%d] = %c\n", q, newBitseq[q]);
       }
       #endif
       //padding all 0s at the end if it is the last byte
       if (i == b->nwords-1) {
           for (n = 0;n < shift;n++) {
               newBitseq[k] = '0';
               k ++;
           }
       } else { //paddind buff[] at the end if it isn't the last byte
           for (n = 0;n < shift;n++) {
               newBitseq[k] = buff[n];
               k ++;
           }
       }
       newBitseq[k] = '\0';
       setBitsFromString(temp, newBitseq);
       res->words[i] = temp->words[0];
       i --;
   }
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
    int i  = 0;
    int m,j,k,n;
    char buff[32];
    char newBitseq[33];
    Bits temp = makeBits(BITS_PER_WORD);
    res->nwords = b->nwords;
    while (i < b->nwords) {
        // save the carry if it isn't the last word
        if (i != (b->nwords-1)) {
            m = shift - 1;
            while (m >= 0) {
                if ((b->words[i] & (1u<<m)) != 0) buff[shift-m-1] = '1';
                else buff[shift-m-1] = '0';
                m --;
            }
        }

        //take the rest of non-carring bits
        newBitseq[32] = '\0';
        k = 31;
        j = shift;
        while (j <= 31) {
            if ((b->words[i] & (1u<<j)) != 0) newBitseq[k] = '1';
            else newBitseq[k] = '0';
            j ++;
            k --;
        }

        //padding all 0s at the end if it is the first byte
        if (i == 0) {
            n = shift - 1;
            while (n >= 0) {
                newBitseq[k] = '0';
                n --;
                k --;
            }
        } else { //paddind buff[] at the end if it isn't the first byte
            n = shift - 1;
            while (n >= 0) {
                newBitseq[k] = buff[n];
                n --;
                k --;
            }
        }
        #if 0
        int q;
        for(q = 0;q < 32;q++) {
            printf("newBitseq[%d] = %c\n", q, newBitseq[q]);
        }
        #endif
        setBitsFromString(temp, newBitseq);
        res->words[i] = temp->words[0];
        i ++;
    }
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to)
{
   #if 0
   printf("%d nwords\n", from->nwords);
   #endif
   int i;
   to->nwords = from->nwords;
   for(i = 0;i < to->nwords;i++) {
       to->words[i] = from->words[i];
   }
}

// assign a bit-string (sequence of 0's and 1's) to Bits
// if the bit-string is longer than the size of Bits, truncate higher-order bits
void setBitsFromString(Bits b, char *bitseq)
{
    #if 0
    printf("%d nwords\n", b->nwords);
    #endif
    Word numBits = b->nwords * BITS_PER_WORD;
    int i,j,k;
    char str[33];
    char *p = &str[32];
    int diff = numBits - strlen(bitseq);
    if (diff < 0) {
        j = 0;
        for(i = 0;i < b->nwords;i++) {
            k = 0;
            while (j < BITS_PER_WORD*(i+1) + diff) {
                str[k] = bitseq[j];
                j++;
                k++;
            }
            str[k] = '\0';
            b->words[i] = strtoul(str, &p, 2);
        }
    } else {
        j = 0;
        #if 0
        printf("The bitseq is %s\n", bitseq);
        #endif 
        for(i = 0;i < b->nwords;i++) {
            k = 0;
            while (j < BITS_PER_WORD*(i+1) - diff) {
                str[k] = bitseq[j];
                j++;
                k++;
            }
            str[k] = '\0';
            #if 0
            printf("str is %s\n", str);
            #endif
            b->words[i] = strtoul(str, &p, 2);
        }
    }
    #if 0 
    for (i = 0;i < b->nwords;i++) {
        printf("%d\n", b->words[i]);
    }
    #endif
}

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b)
{

	int i,j;
	Word numBytes = b->nwords;
    // check if correct input into function
    #if 0
	for(i = 0;i < numBytes;i++) {
		printf("==>No.%d word,bit-strings: %d<==\n",i, b->words[i]);
	}
    #endif

    for(i = 0;i < numBytes;i++) {
        for(j = 31;j >= 0;j--){
            if ((b->words[i] & (1u<<j)) != 0) {
                printf("1");
            } else {
                printf("0");
            }
        }
    }
}
