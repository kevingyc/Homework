#include<stdio.h>
#include<stdlib.h>
#include"tools.h"

Data* read_input_data(int &data_size)
{    
    // �H�U�d�ҬO�g�Ӵ��ժ�
    data_size = 5000; // ���N���Ӥj�p
    Data *d = new Data[data_size]; // �ʺA�ŧi�O����
    int i;
    for(i = 0 ; i < 5000 ; i++ ){
        d[i].key = 5000-i;       // �Ѥj��p
    }
    return d;
}

void quick_sort_recursive(Data data[] , int left,int right)
{
	int i,j;
	if(left<right)      
	{
		i=left+1;		/*i�����b �]����̥�����@�Opivot(����)*/
		j=right;		/*j���k�b*/
		do
		{
			for(;i<=right && compare(data[i],data[left])<=0;i++);	/*��data[left]�j����k��p������*/
			for(;j>=left+1 && compare(data[j],data[left])>=0;j--);	/*�Q�Υ��k�b����m��z*/
			if(i<j)													/*�T�w��m�O�_�O���p�k�j �þ�z�쥿�T��m*/
			{
				swap(data[i],data[j]);
			}
		}while(i<j);
		swap(data[left],data[j]);									/*��data[left]��쥿�T��m*/
		quick_sort_recursive(data,left,j-1);						/*�Hdata[left]�������k������O�����^*/
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
			while(compare(data[i], data[left]) == -1 && i <= right); // �j��
			
			do
			{
				j--; 
			}
			while(compare(data[j], data[left]) == 1 && j >=left+1); // �p��
			
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
    int data_size = 0; // �s��Ƽƶq    
    Data *data = read_input_data(data_size); // Ū�J���

    // �}�ҼȦs , �K�o���A��sort�n����ƦA���hsort
    Data *temp = new Data[data_size];     // �Ȧsdata���
	copy_data(temp , data , data_size);   // �ƻs�禡
    
    quick_sort(temp,data_size);
	//quick_sort_recursive(temp,0,data_size-1);
    for(i = 0 ; i < data_size ; i++)
    {
          printf("temp[%d]=[%d]\n",i,temp[i].key);      
    }   

	show_counter("quick_sort");
    
	return 0;
}
