#include"tools.h"
using namespace std;
long long compare_times = 0;
long long swap_times = 0;
int compare(Data a , Data b)
{
    compare_times++;
    if(a.key > b.key){
        return 1;
    }
    else if(a.key == b.key){
        return 0;
    }
    else if(a.key < b.key){
        return -1;
    }
}
void swap(Data &a , Data &b)
{
    swap_times++;
    Data t = a;
    a = b;
    b = t;
}
void copy_data(Data a[] , Data b[] , int size)
{
    int i;
    for(i = 0 ; i < size ; i++ ){
        a[i] = b[i];
    }
}
void show_counter(char Sort_name[])
{
    cout << Sort_name << endl;
    cout << "compare_times = " << compare_times << endl;
    cout << "swap_times = " << swap_times << endl;
    compare_times = 0;
    swap_times = 0;
}
void check(Data data[] , int data_size)
{
    int i;
    for(i = 1 ; i < data_size && compare(data[i-1],data[i]) != 1; i++ );
    cout << "這次的資料個數 : " << data_size << endl;
    compare_times = 0;
    if(i == data_size){
        cout << "check OK" << endl;
    }
    else{
        cout << "Error ..." << endl;
    }

}
