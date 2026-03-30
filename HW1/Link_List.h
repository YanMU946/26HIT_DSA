#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

typedef int type;
typedef struct LINKLIST
{
    struct LINKLIST *next;
    type data;
} LINKLIST;

typedef enum
{
    RIGHT,
    LEFT
} DIRECTION;

LINKLIST *LinkList_Init(type *buf, int size);
void LinkList_Printf(LINKLIST *head);
LINKLIST *LinkList_Est(type val);
LINKLIST *LinkList_Find(LINKLIST *head, type val);
int LinkList_GetLen(LINKLIST *head);
LINKLIST *LinkList_GetEnd(LINKLIST *head);

void LinkList_PushBack(LINKLIST **phead, type val);
void LinkList_PushFront(LINKLIST **phead, type val);
void LinkList_Insert(LINKLIST **phead, type pos_val, type val);

void LinkList_Erase(LINKLIST **phead, type val);
void LinkList_EraseBack(LINKLIST *head, type val);
void LinkList_Destroy(LINKLIST **phead);

void LinkList_EraseSpe(LINKLIST *phead, type val);
void LinkList_EraseSame(LINKLIST *head);
void LinkList_Inverse(LINKLIST **phead);
void LinkList_PushK(LINKLIST **phead, int k, DIRECTION dir);
void LinkList_Merge(LINKLIST *head1, LINKLIST *head2);
#endif /* end Link_list */
