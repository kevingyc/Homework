#include<iostream>
#include<cstring>
struct Data
{
    int key;
    char str;
    bool yes;
};
// �P�ǥi�ϥΪ��禡
int compare(Data a , Data b);
void swap(Data &a , Data &b);

// �H�U�O��main��ܸ�ƥΪ�
void copy_data(Data a[] , Data b[] , int size);
void show_counter(char Sort_name[]);

// check�u�O��ª����զ��S���q�p��j , �ä��N���ץ��T
void check(Data data[] , int data_size);
