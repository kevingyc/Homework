#include<stdio.h>
#include<stdlib.h>
#include"tools.h"

Data* read_input_data(int &data_size)
{    
    // 以下範例是寫來測試的
    data_size = 5000; // 任意給個大小
    Data *d = new Data[data_size]; // 動態宣告記憶體
    int i;
    for(i = 0 ; i < 5000 ; i++ ){
        d[i].key = 5000-i;       // 由大到小
    }
    return d;
}

void quick_sort_recursive(Data data[] , int left,int right)
{
	int i,j;
	if(left<right)      
	{
		i=left+1;		/*i為左槓 因為把最左項當作是pivot(中樞)*/
		j=right;		/*j為右槓*/
		do
		{
			for(;i<=right && compare(data[i],data[left])<=0;i++);	/*比data[left]大的放右邊小的放左邊*/
			for(;j>=left+1 && compare(data[j],data[left])>=0;j--);	/*利用左右槓的位置整理*/
			if(i<j)													/*確定位置是否是左小右大 並整理到正確位置*/
			{
				swap(data[i],data[j]);
			}
		}while(i<j);
		swap(data[left],data[j]);									/*把data[left]放到正確位置*/
		quick_sort_recursive(data,left,j-1);						/*以data[left]切成左右兩邊分別做遞回*/
		quick_sort_recursive(data,j+1,right);

	}
}


void quick_sort1(Data data[] , int left, int right)
{
	int i,j;
	if(left < right)
	{
		i = left;
		j = right+1;
		do
		{
			do
			{
				i++; 
			}
			while(compare(data[i], data[left]) == -1 && i <= right); // 大於
			
			do
			{
				j--; 
			}
			while(compare(data[j], data[left]) == 1 && j >=left+1); // 小於
			
			if(i<j)
			{
				swap(data[i],data[j]);
			}
		} while(i<j);

		swap(data[left],data[j]);
		quick_sort1(data,left,j-1);
		quick_sort1(data,j+1,right);
	}
}

void quick_sort(Data data[], int size)
{
	quick_sort1(data,0,size-1);
}

int main()
{

	FILE *inptr;
    int i,j;
/*
	if((inptr = fopen("input.txt", "r")) == NULL) // file not exist 
	{	
		printf("File Not Found.\n");
	}
	else
	{
		fread(data,sizeof(Data),size,inptr);		
	}

*/   
    int data_size = 0; // 存資料數量    
    Data *data = read_input_data(data_size); // 讀入資料

    // 開啟暫存 , 免得讓你拿sort好的資料再拿去sort
    Data *temp = new Data[data_size];     // 暫存data資料
	copy_data(temp , data , data_size);   // 複製函式
    
    quick_sort(temp,data_size);
	//quick_sort_recursive(temp,0,data_size-1);
    for(i = 0 ; i < data_size ; i++)
    {
          printf("temp[%d]=[%d]\n",i,temp[i].key);      
    }   

	show_counter("quick_sort");
    
	return 0;
}
