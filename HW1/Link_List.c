#include "Link_List.h"

type Init_Buf[20] = {2026, 3, 30, 11, 5, 202, 411, 10, 78, 5};                                    // 无序初始化数组
type Sorted_Buf[20] = {0, 0, 1, 1, 2, 3, 3, 3, 5, 6, 11, 20, 20, 20, 26, 30, 325, 325, 325, 325}; // 有序初始化数组
type Sorted_Buff[12] = {0, 1, 1, 1, 4, 5, 6, 12, 12, 30, 325, 618};                               // 有序初始化数组
int main()
{
    /* ---------------------------------- MAMBA --------------------------------- */
    LINKLIST *mamba = LinkList_Init(Init_Buf, 10); // 数组初始化，无序
    LinkList_PushBack(&mamba, 2);                  // 一系列尾插
    LinkList_PushBack(&mamba, 3);
    LinkList_PushBack(&mamba, 4);
    LinkList_PushBack(&mamba, 3);
    LinkList_PushBack(&mamba, 2);
    LinkList_PushBack(&mamba, 1);
    printf("Init **mamba** list:\n"); // 展示当前链表
    LinkList_Printf(mamba);

    LinkList_EraseSpe(mamba, 3); // 删除所有值为x的

    LinkList_Inverse(&mamba); // 反转

    LinkList_PushK(&mamba, 3, LEFT);   // 左推k位
    LinkList_PushK(&mamba, 20, RIGHT); // 右推k位
    /* ------------------------------- SORTED LIST ------------------------------ */
    printf("********************************************\n");
    LINKLIST *oi = LinkList_Init(Sorted_Buf, 20); // 有序数组初始化1
    printf("Init **oi** list:\n");                // 依旧展示
    LinkList_Printf(oi);

    LinkList_EraseSame(oi); // 删除相同元素

    LINKLIST *oioi = LinkList_Init(Sorted_Buff, 12); // 有序数组初始化2
    printf("Init **oioi** list:\n");                 // 展示！
    LinkList_Printf(oioi);

    LinkList_Merge(oi, oioi); // 合并已排序
    /* ------------------------------ DESTROY LIST ------------------------------ */
    LinkList_Destroy(&mamba);
    LinkList_Destroy(&oi);
    LinkList_Destroy(&oioi);
    return 0;
}

LINKLIST *LinkList_Init(type *buf, int size)
{
    assert(buf);
    LINKLIST *new_list = LinkList_Est(*buf);
    for (int i = 1; i < size; i++)
        LinkList_PushBack(&new_list, buf[i]);
    return new_list;
}

void LinkList_Printf(LINKLIST *head)
{
    LINKLIST *cur = head;
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int LinkList_GetLen(LINKLIST *head)
{
    if (head == NULL)
        return 0;
    int len = 0;
    LINKLIST *newptr = head;
    while (newptr != NULL)
    {
        len++;
        newptr = newptr->next;
    }
    return len;
}

LINKLIST *LinkList_GetEnd(LINKLIST *head)
{
    if (head == NULL)
        return NULL;
    LINKLIST *newptr = head;
    while (newptr->next != NULL)
        newptr = newptr->next;
    return newptr;
}

LINKLIST *LinkList_Est(type val)
{
    LINKLIST *node = (LINKLIST *)malloc(sizeof(LINKLIST));
    assert(node);
    node->data = val;
    node->next = NULL;
    return node;
}

LINKLIST *LinkList_Find(LINKLIST *head, type val)
{
    LINKLIST *newptr = head;
    while (newptr != NULL)
    {
        if (newptr->data == val)
            return newptr;
        newptr = newptr->next;
    }
    return NULL;
}

void LinkList_PushBack(LINKLIST **phead, type val)
{
    assert(phead);
    LINKLIST *node = LinkList_Est(val);
    if (*phead == NULL)
        *phead = node;
    else
    {
        LINKLIST *end_node = *phead;
        while (end_node->next != NULL)
            end_node = end_node->next;
        end_node->next = node;
    }
}

void LinkList_PushFront(LINKLIST **phead, type val)
{
    assert(phead);
    LINKLIST *node = LinkList_Est(val);
    node->next = *phead;
    *phead = node;
}

void LinkList_Insert(LINKLIST **phead, type pos_val, type val)
{
    assert(phead);
    LINKLIST *node = LinkList_Est(val);
    if (*phead == NULL)
        *phead = node;
    else
    {
        LINKLIST *pcur = *phead, *cur = pcur->next;
        while (cur != NULL)
        {
            if (pcur->data == pos_val)
                break;
            pcur = cur;
            cur = cur->next;
        }
        pcur->next = node;
        node->next = cur;
    }
}

void LinkList_Erase(LINKLIST **phead, type val)
{
    assert(phead);
    if (*phead == NULL)
        return;
    if ((*phead)->data == val)
    {
        LINKLIST *newptr = (*phead)->next;
        free(*phead);
        *phead = newptr;
    }
    else
    {
        LINKLIST *pcur = *phead, *cur = pcur->next;
        while (cur != NULL)
        {
            if (cur->data == val)
                break;
            pcur = cur;
            cur = cur->next;
        }
        if (cur == NULL)
            return;
        pcur->next = cur->next;
        free(cur);
    }
}

void LinkList_EraseBack(LINKLIST *head, type val)
{
    if (head->next == NULL)
        return;
    LINKLIST *cur = LinkList_Find(head, val);
    if (cur == NULL)
        return;
    else
    {
        LINKLIST *t_cur = cur->next;
        cur->next = t_cur->next;
        free(t_cur);
    }
}

void LinkList_Destroy(LINKLIST **phead)
{
    assert(phead);
    if ((*phead)->next == NULL)
    {
        free(*phead);
        *phead = NULL;
    }
    else
    {
        LINKLIST *pcur = *phead, *cur = pcur->next;
        while (cur != NULL)
        {
            free(pcur);
            pcur = cur;
            cur = cur->next;
        }
        free(pcur);
        *phead = NULL;
    }
}

void LinkList_EraseSpe(LINKLIST *head, type val)
{
    if (head == NULL)
        return;
    while (LinkList_Find(head, val) != NULL)
        LinkList_Erase(&head, val);
    printf("##1.Erase specific num:\n");
    LinkList_Printf(head);
}

void LinkList_EraseSame(LINKLIST *head)
{
    if (head == NULL)
        return;
    LINKLIST *pcur = head, *cur = pcur->next;
    while (cur != NULL)
    {
        if (pcur->data == cur->data)
        {
            LinkList_EraseBack(pcur, pcur->data);
            cur = pcur->next;
        }
        else
        {
            pcur = cur;
            cur = cur->next;
        }
    }
    printf("##2.Erase same num:\n");
    LinkList_Printf(head);
}

void LinkList_Inverse(LINKLIST **phead)
{
    assert(phead);
    if (*phead == NULL || (*phead)->next == NULL)
        return;
    LINKLIST *pcur = NULL, *cur = *phead;
    while (cur != NULL)
    {
        LINKLIST *temp_cur = cur->next;
        cur->next = pcur;
        pcur = cur;
        cur = temp_cur;
    }
    *phead = pcur;
    printf("##3.Inverse list:\n");
    LinkList_Printf(*phead);
}

void LinkList_PushK(LINKLIST **phead, int k, DIRECTION dir)
{
    assert(phead);
    int len = LinkList_GetLen(*phead);
    int k_real = (k < len) ? k : (k - k / len * len);

    int cnt = 0;
    LINKLIST *pcur = *phead, *cur = pcur->next;
    switch (dir)
    {
    case LEFT:
    {
        while (cnt < k_real - 1)
        {
            pcur = cur;
            cur = cur->next;
            cnt++;
        }
        LINKLIST *pend = LinkList_GetEnd(*phead);
        pend->next = *phead;
        *phead = cur;
        pcur->next = NULL;
        printf("##4.Push LEFT %d:\n", k);
        LinkList_Printf(*phead);
    }
    break;
    case RIGHT:
    {
        while (cnt < len - k_real - 1)
        {
            pcur = cur;
            cur = cur->next;
            cnt++;
        }
        LINKLIST *pend = LinkList_GetEnd(*phead);
        pend->next = *phead;
        *phead = cur;
        pcur->next = NULL;
        printf("##4.Push RIGHT %d:\n", k);
        LinkList_Printf(*phead);
    }
    break;
    default:
        printf("Choose wrong direction!!!\n");
        return;
        break;
    }
}

void LinkList_Merge(LINKLIST *head1, LINKLIST *head2)
{
    LINKLIST *newptr = (LINKLIST *)malloc(sizeof(LINKLIST));
    newptr->next = NULL;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data <= head2->data)
        {
            LinkList_PushBack(&newptr, head1->data);
            head1 = head1->next;
        }
        else
        {
            LinkList_PushBack(&newptr, head2->data);
            head2 = head2->next;
        }
    }
    LINKLIST *pend = LinkList_GetEnd(newptr);
    if (head1 == NULL)
        pend->next = head2;
    else
        pend->next = head1;
    printf("##5.Merge 2 sorted list:\n");
    LinkList_Printf(newptr->next);
}
