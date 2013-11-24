#include<stdio.h>
  
  int main(void)

{
 int n,x,y,z,a;
 
        printf("Please input n: ");
        scanf("%d", &n);


  for (z=n;z>=0;z--)
  
  {  
     for (a=1;a<=(n-z);a++)
     {            
        printf(" ");
     }
     for (x=1;x<=z;x++)
     {
                        for (y=1;y<=n;y++)
                         {
                             printf("");
                         }
        printf("*");
     }
     printf("\n");
  }

    return 0;
}
