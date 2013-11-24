/*     Compiler Environment : Microsoft Visual C++ 2008 Express Version    Language : C & C++ Language    */
#include<cstdlib>
#include<iostream>
#include<fstream>
#include"tools.h"
#include"proj4.h"
using namespace std;
// 請完成以下五個函式 , 要由小排到大喔 ~

// 老師說要讓同學學習如何用binary讀檔
// 請注意 , 讀檔的時候要將讀到的資料數目存到data_size裡
// 然後在動態宣告記憶體位置 , 並回傳給main

/*
Data* read_input_data(int &data_size)
{    
    // 以下範例是寫來測試的
    data_size = 5000; // 任意給個大小
    Data *d = new Data[data_size]; // 動態宣告記憶體
    int i;
    for(i = 0 ; i < 5000 ; i++ ){
        d[i].key = 5000 - i;       // 由大到小
    }
    return d;
}
*/

Data* read_input_data(int &data_size)
{    
	FILE *inptr,*countptr;							// 檔案指標
	Data i;
	bool b;
	int j;


	if((countptr = fopen("input.txt", "r")) == NULL)// 檔案如果不存在 
	{	
		printf("File Not Found.\n");				// 顯示錯誤訊息
	}
	else
	{
		fseek (countptr, 0, SEEK_END);				// 從一開始到最後
		data_size = ftell(countptr) / 8;			// 個數 = byte數 / 8
	}	

	fclose(countptr);								// 關閉入口
	
	Data *d = new Data[data_size];					// 動態宣告記憶體

	if((inptr = fopen("input.txt", "r")) == NULL)	// 檔案如果不存在 
	{	
		printf("File Not Found.\n");				// 顯示錯誤訊息
	}
	else
	{
		fread(d,sizeof(Data)+2,data_size,inptr);		// 從input檔案讀取資料 
	}

	for(j=0;j<data_size;j++)
	{
		printf("%d ",d[j].key);
	}

	fclose(inptr);									// 關閉入口
	return d;

}

// 助教範例 
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

// 以下是同學要完成的函式 ~~

// Insertion sort
void insertion_sort(Data data[] , int size)
{
	int i,j;
	Data temp;
	for(j = 1 ; j < size ; j++)
	{
		temp = data[j];								// 先複製資料出來作為比較用
		i = j-1;
		while(compare(temp , data[i]) == -1 && i>=0)// 如果temp小於他前面那個
		{
			swap(data[i+1],data[i]);				// 則兩者做交換
			data[i] = data[i+1];			
			i--;									// 繼續向前比較
		}
		data[i+1] = temp;							// 填入temp所在的位置
	}
}

//Heap sort
void copyarray(Data a[], Data b[], int size)		// 複製資料，從n個資料的array複製到n+1個資料的array
{													// 然後資料從位置1開始存
    int i;
    for(i = 0 ; i < size ; i++ )
	{
        a[i+1] = b[i];
    }
}

void rcopyarray(Data a[], Data b[], int size)		// 複製資料，從n+1個資料的array複製到n個資料的array
{													// 然後資料從位置0開始存
    int i;
    for(i = 0 ; i < size ; i++ )
	{
        a[i] = b[i+1];
    }
}

void adjust(Data data[], int root, int n)			// 調整heap為已排序狀態
{
	int child;
	Data temp;
	temp = data[root];								// 調整起始點
	child = 2 * root;

	while(child <= n)
	{
		if((child < n) && compare(data[child], data[child+1]) == -1) // 如果右邊小孩比較小
		{
			child++;								// 就拿右邊小孩去做交換
		}
		
		if(compare(temp, data[child]) == 1)			// 如果父母比小孩大
		{
			break;									// 就不做交換
		}
		else
		{
			swap(data[child/2],data[child]);		// 父母跟小孩交換位置
			data[child] = data[child/2];			
			child*=2;								// 繼續去找下面的子孫比較
		}
	}
	data[child/2] = temp;							// 填入temp所在的位置
}

void heap_sort(Data data[], int size)
{
	int i;
	Data *extra = new Data[size+1];					// 新開一個大小為size+1的heap

	copyarray(extra,data,size);						// 複製資料

	for(i = size/2 ; i > 0 ; i--)					// 先調整一邊
	{
		adjust(extra,i,size);
	}
	for(i = size-1 ; i > 0 ; i--)
	{
		swap(extra[1],extra[i+1]);					// 調整回已排序狀態
		adjust(extra,1,i);							
	}
	
	rcopyarray(data,extra,size);					// 把資料複製回去
}
// Quick_sort
void quick_sort1(Data data[] , int left, int right, int size) // 排序data[left:right]
{
	int i,j;
	Data pivot;										

	if(left < right)
	{	
		i = left;									// 左杆杆
		j = right + 1;								// 右杆杆

		pivot.key = data[left].key;					// 從最左邊開始排序
		do
		{
			do i++; 
				while(compare(data[i], pivot) == -1 && i < size ); // 大於
			do j--; 
				while(compare(data[j], pivot) == 1 && i > 0); // 小於
			if(i<j)
			{
				swap(data[i],data[j]);				// 杆杆衝過頭就兩個交換
			}
		} while(i<j);
		swap(data[left],data[j]);					// 把最左邊的排到他應該在的位置
		quick_sort1(data,left,j-1,size);			// 排序左半邊
		quick_sort1(data,j+1,right,size);			// 排序右半邊
	}
	
}

void quick_sort(Data data[] , int size)				// 偽‧quick sort
{
	quick_sort1(data,0,size-1,size);				// 開始作真正的quick sort...
}

// Merge sort
void merge(Data initlist[], Data mergedlist[], int i, int m, int n) // 融合
{
	int j=0,k,t;
	k = i;											// 右邊子list的索引
	j = m + 1;										// mergedlist的索引

	while(i <= m && j <= n)
	{
		if(compare(initlist[i], initlist[j]) < 1)	// 左邊小於右邊
		{
			swap(mergedlist[k],initlist[i]);		// [左:右]
			initlist[i++] = mergedlist[k++];
		}
		else
		{
			swap(mergedlist[k],initlist[j]);		// [右:左]
			initlist[j++] = mergedlist[k++];
		}
	}
	
	if(i > m)										// mergedlist[k:n] = initlist[j:n]
	{
		for(t = j ; t <= n ; t++)
		{
			swap(mergedlist[t],initlist[t]);		// 把值丟進去
			initlist[t] = mergedlist[t];
		}
	}
	else											// mergedlist[k:n] = initlist[i:m]
	{
		for(t = i ; t <= m ; t++)
		{
			swap(mergedlist[k+t-i],initlist[t]);	// 把值丟進去
			initlist[t] = mergedlist[k+t-i];
		}
	}
}

void mergepass(Data initlist[], Data mergedlist[], int n, int s)
{
	int i,j;
	for(i = 0 ; i < n - 2 * s + 1 ; i += 2 * s)
	{
		merge(initlist, mergedlist,i,i+s-1,i+2*s-1);// 逐段組合
	}

	if(i + s - 1 < n)
	{
		merge(initlist, mergedlist,i,i+s-1,n);		// 繼續組合
	}
	else
	{
		for(j = i ; j <= n ; j++)
		{
			mergedlist[j] = initlist[j];			// 組合剩下多餘的直接丟進結果
		}
	}
}

void merge_sort(Data data[], int size)				// 排序data[1:size]
{
	int length = 1;									// 區段大小
	Data *extra = new Data[size];					// 開一個新的array去存中途運算需保存的值

	while(length < size)							// 區段大小比array小的話
	{
		mergepass(data,extra,size-1,length);		// 組合，結果存在extra
		length*=2;									// 區段大小*2
		mergepass(extra,data,size-1,length);		// 組合，結果存在data
		length*=2;									// 區段大小*2
	}
}
