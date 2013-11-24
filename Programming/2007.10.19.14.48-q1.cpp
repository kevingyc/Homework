#include<stdio.h>

	int main(void)

	{

		int n1,n2,n3,n4,n5;
			

		printf( "Please input five integer numbers:\n" );

		scanf( "%d %d %d %d %d" , &n1, &n2, &n3, &n4, &n5);


		
		//largest	

			if ( n1 > n2 && n1 > n3 && n1 > n4 && n1 > n5 )

			printf("The largest number is %d\n", n1);

			else if ( n2 > n1 && n2 > n3 && n2 > n4 && n2 > n5 )
		
			printf("The largest number is %d\n", n2);
			
			else if ( n3 > n2 && n3 > n1 && n3 > n4 && n3 > n5 )
		
			printf("The largest number is %d\n", n3);

			else if ( n4 > n2 && n4 > n3 && n4 > n1 && n4 > n5 )
		
			printf("The largest number is %d\n", n4);

			else if ( n5 > n2 && n5 > n3 && n5 > n4 && n5 > n1 )
		
			printf("The largest number is %d\n", n5);


		//smallest

			if ( n1 < n2 && n1 < n3 && n1 < n4 && n1 < n5 )

			printf("The smallest number is %d\n", n1);

			else if ( n2 < n1 && n2 < n3 && n2 < n4 && n2 < n5 )

			printf("The smallest number is %d\n", n2);

			else if ( n3 < n1 && n3 < n2 && n3 < n4 && n3 < n5 )

			printf("The smallest number is %d\n", n3);

			else if ( n4 < n1 && n4 < n3 && n4 < n2 && n4 < n5 )

			printf("The smallest number is %d\n", n4);

			else if ( n5 < n2 && n5 < n3 && n5 < n4 && n5 < n1 )

			printf("The smallest number is %d\n", n5);


		return 0;
	}