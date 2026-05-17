#ifndef __SORT_ING_H__
#define __SORT_ING_H__
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

class MergeSort
{
public:
    MergeSort(int* _buf, int _len) :len(_len)
    {
        buf = new int[len];
        memcpy(buf, _buf, len * sizeof(int));
    }

    ~MergeSort() { delete[]buf; }

    void merge_ing()
    {
        int* tmp = new int[len];
        midsort(buf, tmp, 0, len - 1);
    }

    void midsort(int* _buf, int* _tmp, int l, int r)
    {
        if (l < r)
        {
            int mid = (l + r) / 2;
            midsort(_buf, _tmp, l, mid);
            midsort(_buf, _tmp, mid + 1, r);
            merge(_buf, _tmp, l, mid + 1, r);
        }
    }

    void merge(int* _buf, int* _tmp, int l_s, int r_s, int r_e)
    {
        int l_e = r_s - 1;
        int num = r_e - l_s + 1;
        int tmppos = l_s;
        while (l_s <= l_e && r_s <= r_e)
        {
            if (_buf[l_s] < _buf[r_s])
                _tmp[tmppos++] = _buf[l_s++];
            else
                _tmp[tmppos++] = _buf[r_s++];
        }
        while (l_s <= l_e)
            _tmp[tmppos++] = _buf[l_s++];
        while (r_s <= r_e)
            _tmp[tmppos++] = _buf[r_s++];
        for (int i = 0;i < num;i++, r_e--)
            _buf[r_e] = _tmp[r_e];
    }

    void print()
    {
        cout << "Merge Sort Solution:" << endl;
        for (int i = 0;i < len;i++)
            cout << buf[i] << " ";
        cout << endl;
    }

private:
    int* buf;
    int len;
};

class QuickSort
{
public:
    QuickSort(int* _buf, int _len) :len(_len)
    {
        buf = new int[len];
        memcpy(buf, _buf, len * sizeof(int));
    }

    ~QuickSort() { delete[]buf; }

    void quick_ing() { qsort(buf, 0, len - 1); }

    void qsort(int* _buf, int l, int r)
    {
        if (l + 2 <= r)
        {
            int cur = what_m3(_buf, l, r);
            int i = l, j = r - 1;
            for (;;)
            {
                while (_buf[++i] < cur) {}
                while (_buf[--j] > cur) {}
                if (i < j)
                    swap(_buf[i], _buf[j]);
                else
                    break;
            }
            swap(_buf[i], _buf[r - 1]);
            qsort(_buf, l, i - 1);
            qsort(_buf, i + 1, r);
        }
        else if (_buf[l] > _buf[r])
            swap(_buf[l], _buf[r]);
        // insertsort(_buf, l, r);
    }

    int what_m3(int* _buf, int l, int r)
    {
        int mid = (l + r) / 2;
        if (_buf[l] > _buf[mid])
            swap(_buf[l], _buf[mid]);
        if (_buf[l] > _buf[r])
            swap(_buf[l], _buf[r]);
        if (_buf[mid] > _buf[r])
            swap(_buf[mid], _buf[r]);

        swap(_buf[mid], _buf[r - 1]);
        return _buf[r - 1];
    }

    void print()
    {
        cout << "Quick Sort Solution:" << endl;
        for (int i = 0;i < len;i++)
            cout << buf[i] << " ";
        cout << endl;
    }

private:
    int* buf;
    int len;
};

class InsertSort
{
public:
    InsertSort(int* _buf, int _len) :len(_len)
    {
        buf = new int[len];
        memcpy(buf, _buf, len * sizeof(int));
    }

    ~InsertSort() { delete[]buf; }

    void insert_ing() { insort(buf, len); }

    void insort(int* _buf, int _len)
    {
        for (int i = 1;i <= _len - 1;i++)
        {
            int tmp = _buf[i];
            int j;
            for (j = i;j > 0 && _buf[j - 1] > tmp;j--)
                _buf[j] = _buf[j - 1];
            _buf[j] = tmp;
        }
    }

    void print()
    {
        cout << "Insert Sort Solution:" << endl;
        for (int i = 0;i < len;i++)
            cout << buf[i] << " ";
        cout << endl;
    }


private:
    int* buf;
    int len;
};

#endif /* end sorting */
