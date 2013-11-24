/*     Compiler Environment : Microsoft Visual C++ 2008 Express Version    Language : C & C++ Language    */
#include<cstdlib>
#include<iostream>
#include<fstream>
#include"tools.h"
#include"proj4.h"
using namespace std;
// �Ч����H�U���Ө禡 , �n�Ѥp�ƨ�j�� ~

// �Ѯv���n���P�Ǿǲߦp���binaryŪ��
// �Ъ`�N , Ū�ɪ��ɭԭn�NŪ�쪺��Ƽƥئs��data_size��
// �M��b�ʺA�ŧi�O�����m , �æ^�ǵ�main

/*
Data* read_input_data(int &data_size)
{    
    // �H�U�d�ҬO�g�Ӵ��ժ�
    data_size = 5000; // ���N���Ӥj�p
    Data *d = new Data[data_size]; // �ʺA�ŧi�O����
    int i;
    for(i = 0 ; i < 5000 ; i++ ){
        d[i].key = 5000 - i;       // �Ѥj��p
    }
    return d;
}
*/

Data* read_input_data(int &data_size)
{    
	FILE *inptr,*countptr;							// �ɮ׫���
	Data i;
	bool b;
	int j;


	if((countptr = fopen("input.txt", "r")) == NULL)// �ɮצp�G���s�b 
	{	
		printf("File Not Found.\n");				// ��ܿ��~�T��
	}
	else
	{
		fseek (countptr, 0, SEEK_END);				// �q�@�}�l��̫�
		data_size = ftell(countptr) / 8;			// �Ӽ� = byte�� / 8
	}	

	fclose(countptr);								// �����J�f
	
	Data *d = new Data[data_size];					// �ʺA�ŧi�O����

	if((inptr = fopen("input.txt", "r")) == NULL)	// �ɮצp�G���s�b 
	{	
		printf("File Not Found.\n");				// ��ܿ��~�T��
	}
	else
	{
		fread(d,sizeof(Data)+2,data_size,inptr);		// �qinput�ɮ�Ū����� 
	}

	for(j=0;j<data_size;j++)
	{
		printf("%d ",d[j].key);
	}

	fclose(inptr);									// �����J�f
	return d;

}

// �U�нd�� 
void bubble_sort(Data data[] , int size)
{
    int i , j;
    for(i = size - 1 ; i > 0 ; i-- ){
        for(j = 0 ; j < i ; j++ ){
            if(compare(data[j],data[j+1]) == 1){
                swap(data[j],data[j+1]);
            }
        }
    }
}

// �H�U�O�P�ǭn�������禡 ~~

// Insertion sort
void insertion_sort(Data data[] , int size)
{
	int i,j;
	Data temp;
	for(j = 1 ; j < size ; j++)
	{
		temp = data[j];								// ���ƻs��ƥX�ӧ@�������
		i = j-1;
		while(compare(temp , data[i]) == -1 && i>=0)// �p�Gtemp�p��L�e������
		{
			swap(data[i+1],data[i]);				// �h��̰��洫
			data[i] = data[i+1];			
			i--;									// �~��V�e���
		}
		data[i+1] = temp;							// ��Jtemp�Ҧb����m
	}
}

//Heap sort
void copyarray(Data a[], Data b[], int size)		// �ƻs��ơA�qn�Ӹ�ƪ�array�ƻs��n+1�Ӹ�ƪ�array
{													// �M���Ʊq��m1�}�l�s
    int i;
    for(i = 0 ; i < size ; i++ )
	{
        a[i+1] = b[i];
    }
}

void rcopyarray(Data a[], Data b[], int size)		// �ƻs��ơA�qn+1�Ӹ�ƪ�array�ƻs��n�Ӹ�ƪ�array
{													// �M���Ʊq��m0�}�l�s
    int i;
    for(i = 0 ; i < size ; i++ )
	{
        a[i] = b[i+1];
    }
}

void adjust(Data data[], int root, int n)			// �վ�heap���w�ƧǪ��A
{
	int child;
	Data temp;
	temp = data[root];								// �վ�_�l�I
	child = 2 * root;

	while(child <= n)
	{
		if((child < n) && compare(data[child], data[child+1]) == -1) // �p�G�k��p�Ĥ���p
		{
			child++;								// �N���k��p�ĥh���洫
		}
		
		if(compare(temp, data[child]) == 1)			// �p�G������p�Ĥj
		{
			break;									// �N�����洫
		}
		else
		{
			swap(data[child/2],data[child]);		// ������p�ĥ洫��m
			data[child] = data[child/2];			
			child*=2;								// �~��h��U�����l�]���
		}
	}
	data[child/2] = temp;							// ��Jtemp�Ҧb����m
}

void heap_sort(Data data[], int size)
{
	int i;
	Data *extra = new Data[size+1];					// �s�}�@�Ӥj�p��size+1��heap

	copyarray(extra,data,size);						// �ƻs���

	for(i = size/2 ; i > 0 ; i--)					// ���վ�@��
	{
		adjust(extra,i,size);
	}
	for(i = size-1 ; i > 0 ; i--)
	{
		swap(extra[1],extra[i+1]);					// �վ�^�w�ƧǪ��A
		adjust(extra,1,i);							
	}
	
	rcopyarray(data,extra,size);					// ���ƽƻs�^�h
}
// Quick_sort
void quick_sort1(Data data[] , int left, int right, int size) // �Ƨ�data[left:right]
{
	int i,j;
	Data pivot;										

	if(left < right)
	{	
		i = left;									// ������
		j = right + 1;								// �k����

		pivot.key = data[left].key;					// �q�̥���}�l�Ƨ�
		do
		{
			do i++; 
				while(compare(data[i], pivot) == -1 && i < size ); // �j��
			do j--; 
				while(compare(data[j], pivot) == 1 && i > 0); // �p��
			if(i<j)
			{
				swap(data[i],data[j]);				// �����ĹL�Y�N��ӥ洫
			}
		} while(i<j);
		swap(data[left],data[j]);					// ��̥��䪺�ƨ�L���Ӧb����m
		quick_sort1(data,left,j-1,size);			// �Ƨǥ��b��
		quick_sort1(data,j+1,right,size);			// �Ƨǥk�b��
	}
	
}

void quick_sort(Data data[] , int size)				// ���Equick sort
{
	quick_sort1(data,0,size-1,size);				// �}�l�@�u����quick sort...
}

// Merge sort
void merge(Data initlist[], Data mergedlist[], int i, int m, int n) // �ĦX
{
	int j=0,k,t;
	k = i;											// �k��llist������
	j = m + 1;										// mergedlist������

	while(i <= m && j <= n)
	{
		if(compare(initlist[i], initlist[j]) < 1)	// ����p��k��
		{
			swap(mergedlist[k],initlist[i]);		// [��:�k]
			initlist[i++] = mergedlist[k++];
		}
		else
		{
			swap(mergedlist[k],initlist[j]);		// [�k:��]
			initlist[j++] = mergedlist[k++];
		}
	}
	
	if(i > m)										// mergedlist[k:n] = initlist[j:n]
	{
		for(t = j ; t <= n ; t++)
		{
			swap(mergedlist[t],initlist[t]);		// ��ȥ�i�h
			initlist[t] = mergedlist[t];
		}
	}
	else											// mergedlist[k:n] = initlist[i:m]
	{
		for(t = i ; t <= m ; t++)
		{
			swap(mergedlist[k+t-i],initlist[t]);	// ��ȥ�i�h
			initlist[t] = mergedlist[k+t-i];
		}
	}
}

void mergepass(Data initlist[], Data mergedlist[], int n, int s)
{
	int i,j;
	for(i = 0 ; i < n - 2 * s + 1 ; i += 2 * s)
	{
		merge(initlist, mergedlist,i,i+s-1,i+2*s-1);// �v�q�զX
	}

	if(i + s - 1 < n)
	{
		merge(initlist, mergedlist,i,i+s-1,n);		// �~��զX
	}
	else
	{
		for(j = i ; j <= n ; j++)
		{
			mergedlist[j] = initlist[j];			// �զX�ѤU�h�l��������i���G
		}
	}
}

void merge_sort(Data data[], int size)				// �Ƨ�data[1:size]
{
	int length = 1;									// �Ϭq�j�p
	Data *extra = new Data[size];					// �}�@�ӷs��array�h�s���~�B��ݫO�s����

	while(length < size)							// �Ϭq�j�p��array�p����
	{
		mergepass(data,extra,size-1,length);		// �զX�A���G�s�bextra
		length*=2;									// �Ϭq�j�p*2
		mergepass(extra,data,size-1,length);		// �զX�A���G�s�bdata
		length*=2;									// �Ϭq�j�p*2
	}
}
