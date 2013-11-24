#include<stdio.h>

	int main(void)

	{

// program start

		int n1,n2,gcd;

		printf( "Please enter the first integer :  " );		// input integer 1
		scanf( "%d", &n1 );

		printf( "Please enter the second integer:  " );		// input integer 2
		scanf( "%d", &n2 );


			if ( n1 != 0 && n2 != 0 )	// check the input integer
			{

				while ( n1 != 0 && n2 != 0 )	 // check the remainder
				{

					if ( n1 > n2 )

					{
						n1 = n1 % n2;
					}				 // if end

					else

					{
						n2 = n2 % n1;
					}				// else end

				}			// while end
				
					gcd = n1 + n2;		// calculate the GCD
					printf( "\nThe GCD is : %d\n" ,gcd );		// output result

			}		// if end
			else

					printf( "\nPlease enter again!\n");	// output error result

		return 0;

	}		
// program end
