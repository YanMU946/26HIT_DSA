#include "Sequential_List.h"

type init_buf[16] = {2, 2, 114, 514, 2026, 3, 2, 2, 19, 20, 46, 2, 2, 4, 55};
type sorted_buf[22] = {0, 1, 1, 1, 2, 2, 2, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 9, 10, 11, 12, 12};
int main()
{
    SEQLIST mamba, outman;

    SeqList_Init_Buffer(&mamba, init_buf, 16);
    SeqList_Insert(&mamba, 79, 3);
    printf("Initialized list:\n");
    SeqList_Printf(&mamba);

    // SeqList_Erase(&mamba, 4);
    SeqList_Erase_ALL(&mamba, 2);
    SeqList_Erase_Pos(&mamba, 6);
    SeqList_Inverse(&mamba);

    SeqList_Init_Buffer(&outman, sorted_buf, 22);
    SeqList_Erase_Same(&outman);

    SeqList_Destroy(&mamba);
    SeqList_Destroy(&outman);
    return 0;
}

void SeqList_Init(SEQLIST *obj)
{
    obj->arr = NULL;
    obj->capacity = obj->size = 0;
}

void SeqList_Init_Buffer(SEQLIST *obj, type *buf, int buf_size)
{
    obj->arr = (type *)malloc(buf_size * sizeof(type));
    if (obj->arr == NULL)
    {
        printf("malloc error\n");
        assert(obj->arr);
    }
    else
    {
        memcpy(obj->arr, buf, buf_size * sizeof(type));
        obj->size = buf_size;
        obj->capacity = buf_size;
    }
}

bool SeqList_IsEmpty(SEQLIST *obj)
{
    assert(obj);
    return (obj->size == 0);
}

void SeqList_Destroy(SEQLIST *obj)
{
    assert(obj);
    if (obj->arr == NULL)
        return;
    free(obj->arr);
    SeqList_Init(obj);
}

void SeqList_Printf(SEQLIST *obj)
{
    assert(obj);
    for (int i = 0; i < obj->size; i++)
        printf("%d ", obj->arr[i]);
    printf("\n");
}

void SeqList_CheckCap(SEQLIST *obj)
{
    if (obj->capacity == obj->size)
    {
        int new_capacity = (obj->capacity == 0) ? 4 : (obj->capacity * 2);
        type *new_arr = (type *)realloc(obj->arr, new_capacity * sizeof(type));
        if (new_arr == NULL)
        {
            printf("realloc error\n");
            assert(new_arr);
        }
        else
        {
            obj->arr = new_arr;
            obj->capacity = new_capacity;
        }
    }
}

int SeqList_FindFirst(SEQLIST *obj, type val)
{
    assert(obj);
    for (int i = 0; i < obj->size; i++)
        if (obj->arr[i] == val)
            return i;
    return EOF;
}

void SeqList_Insert(SEQLIST *obj, type val, type pos)
{
    assert(obj);
    SeqList_CheckCap(obj);
    if (pos > obj->size)
        obj->arr[obj->size] = val;
    else
    {
        for (int i = obj->size - 1; i >= pos; i--)
            obj->arr[i + 1] = obj->arr[i];
        obj->arr[pos] = val;
    }
    obj->size++;
}

void SeqList_Erase(SEQLIST *obj, type val)
{
    assert(obj);
    int check;
    if (~(check = SeqList_FindFirst(obj, val)))
    {
        for (int i = check; i < obj->size; i++)
            obj->arr[i] = obj->arr[i + 1];
        obj->size--;
    }
    else
        printf("404 not found\n");
}

void SeqList_Erase_ALL(SEQLIST *obj, type val)
{
    assert(obj);
    if (SeqList_FindFirst(obj, val) == -1)
    {
        printf("404 not found\n");
        return;
    }
    while (SeqList_FindFirst(obj, val) != -1)
        SeqList_Erase(obj, val);
    printf("Delete all members val: %d\n", val);
    SeqList_Printf(obj);
}

void SeqList_Erase_Pos(SEQLIST *obj, int pos)
{
    assert(obj);
    if (pos > obj->size)
    {
        printf("404 not found\n");
        return;
    }
    else
    {
        for (int i = pos; i < obj->size; i++)
            obj->arr[i] = obj->arr[i + 1];
        obj->size--;
    }
    printf("Delete selected position %d val: \n", pos);
    SeqList_Printf(obj);
}

void SeqList_Erase_Same(SEQLIST *obj)
{
    for (int i = 0; i < obj->size; i++)
    {
        while (obj->arr[i] == obj->arr[i + 1])
            SeqList_Erase(obj, obj->arr[i]);
    }
    printf("Delete same elememts:\n");
    SeqList_Printf(obj);
}

void SeqList_Inverse(SEQLIST *obj)
{
    type temp_buf[obj->size];
    for (int i = 0; i < obj->size; i++)
        temp_buf[i] = obj->arr[obj->size - i - 1];
    memcpy(obj->arr, temp_buf, obj->size * sizeof(type));
    printf("Inverse list:\n");
    SeqList_Printf(obj);
}

void SeqList_PushK(SEQLIST *obj, int k, DIRECTION dir)
{
    if (k % obj->size > 0)
    {
        int temp = k / obj->size;
        k -= temp * obj->size;
    }
    switch (dir)
    {
    case RIGHT:
    {
    }
    break;
    case LEFT:
    {
    }
    break;
    default:
        break;
    }
}
