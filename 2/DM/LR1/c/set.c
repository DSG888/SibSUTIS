#include "set.h"
#include <stdio.h>
#include <stdlib.h>

const int success = 0;
const int incorrect_input = 2;


void prFill(char* arr, char len, char val)
{
    for (size_t i = 0; i < len; ++i)
    {
        *(arr + i) = val;
    }
}

void prReadUntil(char until)
{
    char c = (char) getchar();
    while (c != until)
    {
        c = (char) getchar();
    }
}

int getSetFromCon(Set** set)
{
    char* data = malloc(sizeof(char) * 26);
    char maxSym = 0;
    prFill(data, 26, 0);
    char lastSym = 0;
    char c = (char) getchar();
    while (c != '\n') {
        if (!(c >= 'a' && c <= 'z') && c!= ' ')
        {
            prReadUntil('\n');
            free(data);
            return incorrect_input;
        }
        if (c != ' ')
        {
            if (lastSym == 0)
            {
                c = (char) (c - 'a');
                if (c > maxSym)
                {
                    maxSym = c;
                }
                *(data + c) = 1;
                lastSym = 1;
            }
            else {
                prReadUntil('\n');
                free(data);
                return incorrect_input;
            }
        }
        else {
            lastSym = 0;
        }
        c = (char) getchar();
    }
    *set = malloc(sizeof(set));
    (*set)->data = data;
    (*set)->maxSym = (unsigned char) maxSym;
    return success;
}

void destSet(Set** set)
{
    free((*set)->data);
    free(*set);
    *set = NULL;
}

void printSet(Set* set)
{
    if (set->maxSym == 0 && *(set->data) == 0)
    {
        printf("Пустое множество\n");
        return;
    }
    size_t max = set->maxSym;
    for (size_t i = 0; i <= max; ++i)
    {
        if (*(set->data + i) == 1)
        {
            printf("%c ", (char) (i + 'a'));
        }
    }
    printf("\n");
}

Set* merge(Set* set1, Set* set2)
{
    size_t max = 0;
    if (set1->maxSym > set2->maxSym)
    {
        max = set1->maxSym;
    }
    else {
        max = set2->maxSym;
    }
    char* data = malloc(sizeof(char) * 26);
    prFill(data, 26, 0);
    size_t tmpMax = 0;
    for (size_t i = 0; i <= max; ++i)
    {
        if (*(set1->data + i) == 1 || *(set2->data + i) == 1)
        {
            *(data + i) = 1;
            tmpMax = i;
        }
    }
    Set* res = malloc(sizeof(Set));
    res->data = data;
    res->maxSym = (unsigned char) tmpMax;
    return res;
}

Set* intersect(Set* set1, Set* set2)
{
    size_t max = 0;
    if (set1->maxSym > set2->maxSym)
    {
        max = set1->maxSym;
    }
    else {
        max = set2->maxSym;
    }
    char* data = malloc(sizeof(char) * 26);
    prFill(data, 26, 0);
    size_t tmpMax = 0;
    for (size_t i = 0; i <= max; ++i)
    {
        if (*(set1->data + i) == 1 && *(set2->data + i) == 1)
        {
            *(data + i) = 1;
            tmpMax = i;
        }
    }
    Set* res = malloc(sizeof(Set));
    res->data = data;
    res->maxSym = (unsigned char) tmpMax;
    return res;
}

char subSet(Set* set1, Set* set2)
{
    if (set1->maxSym == 0 && *(set1->data) == 0)
    {
        return 1;
    }
    size_t max = set1->maxSym;
    for (size_t i = 0; i <= max; ++i)
    {
        if (*(set1->data + i) != *(set2->data + i))
        {
            return 0;
        }
    }
    return 1;
}

Set* complement(Set* set1, Set* set2)
{
    size_t max = 0;
    if (set1->maxSym > set2->maxSym)
    {
        max = set1->maxSym;
    }
    else
    {
        max = set2->maxSym;
    }
    char* data = malloc(sizeof(char) * 26);
    prFill(data, 26, 0);
    size_t tmpMax = 0;
    for (size_t i = 0; i <= max; ++i)
    {
        if (*(set1->data + i) == 1 && *(set2->data + i) == 0)
        {
            *(data + i) = 1;
            tmpMax = i;
        }
    }
    Set* res = malloc(sizeof(Set));
    res->data = data;
    res->maxSym = (unsigned char) tmpMax;
    return res;
}

Set* symComplement(Set* set1, Set* set2)
{
    size_t max = 0;
    if (set1->maxSym > set2->maxSym)
    {
        max = set1->maxSym;
    }
    else {
        max = set2->maxSym;
    }
    char* data = malloc(sizeof(char) * 26);
    prFill(data, 26, 0);
    size_t tmpMax = 0;
    for (size_t i = 0; i <= max; ++i)
    {
        if (*(set1->data + i) == 1 ^ *(set2->data + i) == 1)
        {
            *(data + i) = 1;
            tmpMax = i;
        }
    }
    Set* res = malloc(sizeof(Set));
    res->data = data;
    res->maxSym = (unsigned char) tmpMax;
    return res;
}
