#include "sort_ing.h"

int main()
{
    ifstream infile("unsorted.in");
    if (!infile.is_open())
    {
        cout << "Fail to open file!" << endl;
        return 1;
    }

    int unsorted_len;
    infile >> unsorted_len;
    int* unsorted_buf = new int[unsorted_len];
    for (int i = 0;i < unsorted_len;i++)
        infile >> unsorted_buf[i];

    infile.close();

    MergeSort mg_sort(unsorted_buf, unsorted_len);
    auto mg_start = chrono::high_resolution_clock::now();
    mg_sort.merge_ing();
    auto mg_end = chrono::high_resolution_clock::now();
    mg_sort.print();
    auto mg_duration_us = chrono::duration_cast<chrono::microseconds>(mg_end - mg_start);
    cout << "--------------------------------------------------" << endl;

    QuickSort q_sort(unsorted_buf, unsorted_len);
    auto q_start = chrono::high_resolution_clock::now();
    q_sort.quick_ing();
    auto q_end = chrono::high_resolution_clock::now();
    q_sort.print();
    auto q_duration_us = chrono::duration_cast<chrono::microseconds>(q_end - q_start);
    cout << "--------------------------------------------------" << endl;

    InsertSort in_sort(unsorted_buf, unsorted_len);
    auto in_start = chrono::high_resolution_clock::now();
    in_sort.insert_ing();
    auto in_end = chrono::high_resolution_clock::now();
    in_sort.print();
    auto in_duration_us = chrono::duration_cast<chrono::microseconds>(in_end - in_start);
    cout << "--------------------------------------------------" << endl;
    cout << "Merge Sort us:" << mg_duration_us.count() << endl;
    cout << "Quick Sort us:" << q_duration_us.count() << endl;
    cout << "Insert Sort us:" << in_duration_us.count() << endl;
    system("pause");
    return 0;
}
