#include<stdio.h>
	int main (void)

	{

      int n,n1,n2,n3,n4,n5,n6;

		  printf ("Please Enter a Number:\n");  //input
		  scanf ("%d", &n);
		
		  
	 //take 1000000 lower

   	        n1 = n/1000;//计!
	    	n2 = n%1000;//ㄤ緇!

	  //take 1000000000 lower

			n3 = n1/1000;//κ窾计!
			n4 = n1%1000;//ㄤ緇

	  //take 1000000000000 lower

			n5 = n3/1000;//货计!
			n6 = n3%1000;//ㄤ緇
			
		if ( n < 1000 ) //take 1000 lower
			printf("\n%d\n", n);

		else //take 1000000 lower
			if ( n < 1000000 )	
			printf("\n%d,%03d\n", n1,n2);


		else //take 1000000000 lower
			if ( n < 1000000000 )	
			printf("\n%d,%03d,%03d\n", n3,n4,n2);


		else //take 1000000000000 lower
			if ( n < 2147483648 )
			printf("\n%d,%03d,%03d,%03d\n", n5,n6,n4,n2);

		else 
			printf("Overflow!\n"); 


	return 0; //program ending
	
	}
