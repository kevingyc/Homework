#include<stdio.h>

  
	int main(void)
//program start
	{
		int n; 
		int x,y,z,l; // counter
		int a,b,c,d,e; // variable for operation

		a = b = c = d = e = 1;

        printf( "Please input n: " );
        scanf( "%d", &n );
		

		for ( x = 0 ; x <= n ; x++ ) // lines
		{
			
			for ( l = 1 ; l <= ( n - x ) ; l++ ) // space
			{            
				printf( "   " );
			} // l for end

  				if ( x == 0) // for first line
				{
					printf("    1");
				}

			for ( y = x, z = 1 ; y > 0, z <= x ; y--, z++ ) // factorial operation
			{				

  				if ( y == x) // for first number
				{
					printf("    1");
				}


				e = b / a;
				b = e * y;	
				a = z;
				d = b / a;

				printf("%6d", d);
				d = 1;
			} // yz for end

			printf("\n");
			a = b = d = 1;

		} // x for end

  system("pause");
    return 0;
	}
// program end
