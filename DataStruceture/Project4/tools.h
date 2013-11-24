#include<iostream>
#include<cstring>
struct Data
{
    int key;
    char str;
    bool yes;
};
// 同學可使用的函式
int compare(Data a , Data b);
void swap(Data &a , Data &b);

// 以下是給main顯示資料用的
void copy_data(Data a[] , Data b[] , int size);
void show_counter(char Sort_name[]);

// check只是單純的測試有沒有從小到大 , 並不代表答案正確
void check(Data data[] , int data_size);
