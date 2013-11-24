#include<stdio.h>
#include<stdlib.h>
    int ope(int x,int y);
    
  		int n; 
		int x,y,z,l; // counter
		int i,j,k,l;
		int a,b,c,d,e; // variable for operation

	int main(void)
	{
		a = b = c = d = e = 1;

        printf( "Please input n: " );
        scanf( "%d", &n );
	for (i=0;i<=n;i++)
    {
        printf("%6d",ope(n-1,i));    
        }
        printf("\n");
    system("pause");
    return 0;
	}

int ope(int x,int y)
{
    
    
    if(y==x+1||y==0)
    {
    return 1;
    }
    else
    {
   
    
     
    return (x+ope(n-1,y-1));
    } 

    return 0;

}
    
