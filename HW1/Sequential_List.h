#ifndef __SEQLIST_H__
#define __SEQLIST_H__
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

typedef int type;
typedef struct
{
    type *arr;
    int capacity;
    int size;
} SEQLIST;

typedef enum{
    RIGHT,
    LEFT
}DIRECTION;

void SeqList_Init(SEQLIST *obj);
void SeqList_Init_Buffer(SEQLIST *obj, type *buf, int buf_size);
bool SeqList_IsEmpty(SEQLIST *obj);
void SeqList_Destroy(SEQLIST *obj);
void SeqList_Printf(SEQLIST *obj);

void SeqList_CheckCap(SEQLIST *obj);
int SeqList_FindFirst(SEQLIST *obj, type val);

void SeqList_Insert(SEQLIST *obj, type val, type pos);

void SeqList_Erase(SEQLIST *obj, type val);
void SeqList_Erase_ALL(SEQLIST *obj, type val);
void SeqList_Erase_Pos(SEQLIST *obj, int pos);
void SeqList_Erase_Same(SEQLIST *obj);

void SeqList_Inverse(SEQLIST *obj);

#endif /* end Sequential_List */
