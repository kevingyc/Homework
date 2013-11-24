#include<iostream>
#include <ctime>
#include"tools.h"
#include"proj4.h"
using namespace std;
int main(void)
{
    int choice;
    while(1){ // �U�T���_���j��
        system("CLS");
        cout << "0.bubble_sort" << endl
             << "1.insertion_sort" << endl
             << "2.heap_sort" << endl
             << "3.quick_sort" << endl
             << "4.merge_sort" << endl
             << "5.���}" << endl
             << "�п�J�A�n���檺�ﶵ:";
        cin >> choice;        
        // Ū��
        int data_size = 0; // �s��Ƽƶq    
        Data *data = read_input_data(data_size); // Ū�J���

        // �}�ҼȦs , �K�o���A��sort�n����ƦA���hsort
        Data *temp = new Data[data_size];     // �Ȧsdata���
        copy_data(temp , data , data_size);   // �ƻs�禡

        // ���O����P�Ǽg���{��
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
            cout << "1.�аO�o�g�W�A�ҨϥΪ�compiler����" << endl
                 << "2.�аO�o�n�g����" << endl
                 << "3.�P�ǥi�ϥ�C��C++�Ӽ��g�A���{��" << endl;
            system("pause");
            break;
        }
        else{
            cout << "���h�~���y�a ...." << endl;
        }

        delete []temp; // �R���Ȧs��
        delete []data; // �R���O����
        
        system("pause");
    }
    return 0;
}
