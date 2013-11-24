#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 52

int a[SIZE];
int b[SIZE];
int i,j,k,l;
int x,y;
int r;
int n=0;

int cut_and_move( int A[], int B[], int size );
int benchmark( int cards[], int size );

int main(void)
{
	for ( i = 0 ; i < SIZE ; i++ )
	{
		a [i] = i + 1;
	}

	srand(time(NULL));
	r = SIZE;

	while ( r > 2 )
	{
		r = 0;
		if ( n % 2 == 0 )
		{
			cut_and_move( a, b, SIZE );
		}
		else
		{
			cut_and_move( b, a, SIZE);
		}
		//system("pause");
	}

return 0;
}


int cut_and_move( int A[],int B[],int size )
{
	do
	{
		x = rand() % SIZE;
		y = rand() % SIZE;
	}
	while( x < y );

	for ( i = 0, j = y ; i <= x-y, j <= x ; i++, j++ ) 
	{
		B [i] = A [j];
	}

	for ( k = 0 ; k <= y ; k++ )
	{
		B [ x - y + k + 1 ] = A [k];
	}

	for ( l = x + 1 ; l < size ; l++ )
	{
		B [l] = A [l];
	}
		
	if ( x == y )
	{
		B [0] = A [x-1];
		
		for ( i = 0 ; i < x-1 ; i++ )
		{
			B [i+1] = A[i];
		}
			
		for ( j = x ; j < size ; j++ )
		{
			B [j] = A [j];
		}

	}

	n++;
	benchmark( B , SIZE );

return y;
}

int benchmark( int cards[], int size )
{
	for ( k = 0 ; k < size ; k++ )
	{
		if ( cards [ k ] + 1 == cards [ k + 1 ] )
		{
			r++;
			printf( "*%2d ", cards[k] );
		}
		else
		{
			printf( "%3d ", cards[k] );
		}

		if ( k % 13 == 12 )
		{
			printf( "\n" );
		}
	}
	
	printf( "\n" );
	printf( "(%d,%d)\n", x, y );
	printf( "\nRUN %d times, %d stars\n\n", n, r );
return r;
}