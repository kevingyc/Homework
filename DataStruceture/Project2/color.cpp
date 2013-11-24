#include <stdio.h>
#include <stdlib.h>

int main()
{
    int data[52]={21,16,6,46,34,35,5,26,25,17,42,8,15,4,49,39,36,9,7,32,3,10,18,50,13,11,52,47,41,45,33,30,28,12,37,40,14,27,44,43,22,20,29,1,19,2,24,23,31,38,48,51};
    int i;
        
    for(i=0;i<52;i++)
    {
        if((data[i]-1) / 13 == 0)
        {
            printf("spade   ");   
        }
        else if((data[i]-1) / 13 == 1)
        {
            printf("heart   ");   
        }
        else if((data[i]-1) / 13 == 2)
        {
            printf("diamond ");   
        }
        else
        {
            printf("club    ");   
        }
        
        printf("%3d\n",(data[i]-1)%13+1);
        
    }



    system("pause");
    return 0;
}   
