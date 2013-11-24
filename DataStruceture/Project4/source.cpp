#include<iostream>
#include <ctime>
#include"tools.h"
#include"proj4.h"
using namespace std;
int main(void)
{
    int choice;
    while(1){ // 萬劫不復的迴圈
        system("CLS");
        cout << "0.bubble_sort" << endl
             << "1.insertion_sort" << endl
             << "2.heap_sort" << endl
             << "3.quick_sort" << endl
             << "4.merge_sort" << endl
             << "5.離開" << endl
             << "請輸入你要執行的選項:";
        cin >> choice;        
        // 讀檔
        int data_size = 0; // 存資料數量    
        Data *data = read_input_data(data_size); // 讀入資料

        // 開啟暫存 , 免得讓你拿sort好的資料再拿去sort
        Data *temp = new Data[data_size];     // 暫存data資料
        copy_data(temp , data , data_size);   // 複製函式

        // 分別執行同學寫的程式
        if(choice == 0){
            bubble_sort(temp,data_size);
            show_counter("bubble_sort");
            check(temp,data_size);
        }
        else if(choice == 1){
            insertion_sort(temp,data_size);
            show_counter("insertion_sort");
            check(temp,data_size);
        }
        else if(choice == 2){
            heap_sort(temp,data_size);
            show_counter("heap_sort");
            check(temp,data_size);
        }
        else if(choice == 3){
            quick_sort(temp,data_size);
            show_counter("quick_sort");
            check(temp,data_size);
        }
        else if(choice == 4){
            merge_sort(temp,data_size);
            show_counter("merge_sort");
            check(temp,data_size);
        }
        else if(choice == 5){
            cout << "1.請記得寫上你所使用的compiler環境" << endl
                 << "2.請記得要寫註解" << endl
                 << "3.同學可使用C或C++來撰寫你的程式" << endl;
            system("pause");
            break;
        }
        else{
            cout << "先去洗把臉吧 ...." << endl;
        }

        delete []temp; // 刪除暫存體
        delete []data; // 刪除記憶體
        
        system("pause");
    }
    return 0;
}
