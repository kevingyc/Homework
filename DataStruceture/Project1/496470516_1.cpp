#include <stdio.h>
#include <stdlib.h>
/*the prototype of functions*/ 
int magic_square(int row, int col, int **square, int n, int size);
int **makearray(int size);
 /*program strat*/ 
int main()                                           
{/*declare variables*/
    int i, j;                                         
    int row, col, size, n=2;                         /*because 1 has been filled, so start from 2*/
    int **square;
             
    while(1)                                         /*while loop start, it won't stop*/
    {
        printf("Please set the Magic Square Size : "); /*notice user to enter the size of*/ 
        scanf("%d", &size);                          /*this magic square               */
                                                    
        if( size == 0 )
        {
            break;                                   /*if user enter 0, the program terminate*/
        }
                     
        if( size % 2 == 1 )
        {   
            square = makearray( size );              /*make an 2Darray*/
            
            row = 0;
            col = (size-1)/2; 
            square[row][col] = 1;                    /*set start point*/
            
            magic_square( row, col, square, n, size);/*fill in the value of the magic square*/
            
            for(i = 0 ; i < size ; i++)              /*output magic square*/
            {
                for(j = 0 ; j < size ; j++)   
                {
                    printf("%3d ", square[i][j]);   
                }
                printf("\n");
            }
            
            for(i = 0 ; i < size ; i++)
            {
			    free(square[i]);
            }
            
		    free(square);                                        /*for loop end*/
        }                                            /*if end*/
        else
        {
            printf("n must be odd\n");               /*notice user to enter odd number*/
        }
    }                                                /*while loop end*/
    system("pause");
    return 0;
}                                                    /*program end*/
 /*function strat*/
int magic_square(int row, int col, int **square, int n, int size)
{
    row = (row-1<0) ? (size-1) : (row-1);            /*move the position of filling*/
    col = (col-1<0) ? (size-1) : (col-1);
    
    if( n <= ( size * size ) )                             
    {
        if( square[row][col] != 0 )                  /*if the current position has been filled*/
        {                                            /*it must be back to original position   */
            row = ( (row+1>=size)? 0 :(row+1) ) + 1; /*and move to the next row               */
            col = (col+1>=size)? 0 :(col+1);         /*                                       */
        }
        square[row][col] = n;                        /*fill value to this position*/
        return magic_square(row,col,square,n+1,size);/*recursive filling values */
     }
     
     return 0;
}/*function end*/
 /*function strat*/
int **makearray(int size)
{
    int **s, i;
    
    s = (int**) calloc( size, sizeof(int) );          /*make the row of this array*/
            
    for(i = 0 ; i < size+1 ; i++)
    {
         s[i] = (int*)calloc( size+1, sizeof(int) );    /*make the col of this array*/
    }
    return s;
}/*function end*/    

