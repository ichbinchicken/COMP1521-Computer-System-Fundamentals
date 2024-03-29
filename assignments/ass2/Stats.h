// Stats.h ... interface to VM stats
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

#ifndef STATS_H

void initStats();
void countPeekRequest(); 
void countPokeRequest();
void countPageLoad();  // # of loading page
void countPageSave(); // # of saving page to the disk
void countPageFault(); 
void countPageHit();
void showSummaryStats();

#endif
