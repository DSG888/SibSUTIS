#ifndef SET_H
#define SET_H

typedef struct {
    char* data;
    unsigned char maxSym;
} Set;

int getSetFromCon(Set** set);
void destSet(Set** set);
void printSet(Set* set);
Set* merge(Set* set1, Set* set2);
Set* intersect(Set* set1, Set* set2);
char subSet(Set* set1, Set* set2);
Set* complement(Set* set1, Set* set2);
Set* symComplement(Set* set1, Set* set2);

#endif
