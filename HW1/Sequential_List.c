#include "Sequential_List.h"

type init_buf[16] = {2, 2, 114, 514, 2026, 3, 2, 2, 19, 20, 46, 2, 2, 4, 55};                 // 乱给的数
type sorted_buf[22] = {0, 1, 1, 1, 2, 2, 2, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 9, 10, 11, 12, 12}; // 已排好序的线性表
int main()
{
    /* --------------------------------- DEFINE --------------------------------- */
    SEQLIST mamba, outman;

    // mamba表都是乱给的数，从init_buf给
    SeqList_Init_Buffer(&mamba, init_buf, 16); // 数组初始化线性表
    SeqList_Insert(&mamba, 79, 3);             // 插入一个数
    printf("Initialized list:\n");
    SeqList_Printf(&mamba); // 线性表打印

    // SeqList_Erase(&mamba, 4);     // 这个是删除值为x的，只删除1个
    SeqList_Erase_ALL(&mamba, 2); // 删除所有值为x的
    SeqList_Erase_Pos(&mamba, 6); // 删除位置x的数
    SeqList_Inverse(&mamba);      // 线性表“逆置”

    SeqList_PushK(&mamba, 3, LEFT); // 左移k位

    // outman表是排好序的数，从sorted_buf给
    SeqList_Init_Buffer(&outman, sorted_buf, 22);
    SeqList_Erase_Same(&outman); // 删去所有相同元素

    SeqList_PushK(&outman, 50, RIGHT); // 右移k位

    /* ---------------------------------- FREE ---------------------------------- */
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
        type *buf_l = malloc((obj->size - k) * sizeof(type));
        type *buf_r = malloc(k * sizeof(type));
        if (buf_l == NULL || buf_r == NULL)
        {
            printf("malloc failed!\n");
            assert(buf_l);
            assert(buf_r);
        }
        memcpy(buf_l, obj->arr, (obj->size - k) * sizeof(type));
        memcpy(buf_r, obj->arr + obj->size - k, k * sizeof(type));

        memcpy(obj->arr, buf_r, k * sizeof(type));
        memcpy(obj->arr + k, buf_l, (obj->size - k) * sizeof(type));
        printf("Push right %d num:\n", k);
        SeqList_Printf(obj);
        free(buf_l);
        free(buf_r);
    }
    break;
    case LEFT:
    {
        type *buf_l = malloc(k * sizeof(type));
        type *buf_r = malloc((obj->size - k) * sizeof(type));
        if (buf_l == NULL || buf_r == NULL)
        {
            printf("malloc failed!\n");
            assert(buf_l);
            assert(buf_r);
        }
        memcpy(buf_l, obj->arr, k * sizeof(type));
        memcpy(buf_r, obj->arr + k, (obj->size - k) * sizeof(type));

        memcpy(obj->arr, buf_r, (obj->size - k) * sizeof(type));
        memcpy(obj->arr + obj->size - k, buf_l, k * sizeof(type));
        printf("Push left %d num:\n", k);
        SeqList_Printf(obj);
        free(buf_l);
        free(buf_r);
    }
    break;
    default:
        printf("Delay no more! Choose wrong direction!\n");
        break;
    }
}
