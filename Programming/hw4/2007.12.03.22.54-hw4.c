#include<stdio.h>

int gcd( int x, int y );

int lcm( int x, int y );

int add( int w,int x,int y,int z );

int sub( int w,int x,int y,int z );

int mul( int w,int x,int y,int z );

int div( int w,int x,int y,int z );

int main( void )
{

	int n1,n2; //numerators
	int d1,d2; //denominators
	char ope; //operators

	scanf("%d%d\n%c%d%d", &n1, &d1, &ope, &n2, &d2);

	if ( d1 !=0 && d2 != 0 )
	{
		switch ( ope )
		{

			case '+':
				printf("\n" , add( n1, d1, n2, d2 ) );
				break;

			case '-':
				printf("\n" , sub( n1, d1, n2, d2 ) );
				break;

			case '*':
				printf("\n" , mul( n1, d1, n2, d2 ) );
				break;

			case '/':
				printf("\n" , div( n1, d1, n2, d2 ) );
				break;
			default :
				printf("Please enter again\n");
		}
	}
	else
		printf("please enter again\n");

	return 0;
}

////////////////////////////////////////////////////////////////////////////

int gcd( int x, int y )
{
   	int gcd; //GCD operate

        
               while( x != 0 && y != 0)
               
               {
                      if ( x > y )
                         x = x % y;
                      else
                         y = y % x;
               }

                 gcd = x + y;    

    return gcd;
}



int lcm( int x, int y )
{
	int lcm; //LCM operate

    lcm =( x * y /  gcd ( x , y ) );

    return lcm;
}


int add( int w,int x,int y,int z )
{

	int n; //numerators
	int d; //denominators
	int m1,m2; //multiple
	int g,l; //GCD&LCM
	int a; //addition

	if ( w == 0 && y == 0)
		printf("\n0\n");
	else
	{
		l = lcm( x , z );

		if (l != x)
			{
				m1 = l / x;
				w = w * m1;
			}
		if (l != z)
			{
				m2 = l / z;
				y = y * m2;
			}
	
		a = w + y;
		g = gcd( a , l );
		
		n = a / g;	
		d = l / g;

		if ( d != 1 )
		printf("\n%d / %d\n", n, d );
		else
		printf("\n%d\n", n );


	}
	

	return 0;

}

int sub( int w,int x,int y,int z )
{

	int n; //numerators
	int d; //denominators
	int m1,m2; //multiple
	int g,l; //GCD&LCM
	int s; //subtraction 

	
	l = lcm( x , z );

	if (l != x)
	{
		m1 = l / x;
		w = w * m1;
	}
	if (l != z)
	{
		m2 = l / z;
		y = y * m2;
	}

	if( w - y != 0)
	{
      if ( w > y )
	  {
		 s = w - y;
		 g = gcd( s , l );
		 n = s / g;
		 d = l / g;

		if ( d != 1 )
		printf("\n%d / %d\n", n, d );
		else
		printf("\n%d\n", n );
	  }
      
	  else
	  {
         s = y - w;
		 g = gcd( s , l );
		 n = s / g;
		 d = l / g;

		if ( d != 1 )
		printf("\n-%d / %d\n", n, d );
		else
		printf("\n-%d\n", n );
	  }
	}
	else 
	  printf("\n0\n");
	return 0;
}

int mul( int w,int x,int y,int z )
{

	int n; //numerators
	int d; //denominators
	int m1,m2; //multiple
	int g; //GCD&LCM
	
	if ( w != 0 && y != 0 )
	{
		m1 = w * y;
		m2 = x * z;
		g = gcd( m1 , m2 );
		n = m1 / g;
		d = m2 / g;

		if ( d != 1 )
		printf("\n%d / %d\n", n, d );
		else
		printf("\n%d\n", n );
	}
	else
		printf("\n0\n");

	return 0;
}


int div( int w,int x,int y,int z )
{

	int n; //numerators
	int d; //denominators
	int m1,m2; //multiple
	int g; //GCD&LCM
	
	if ( w != 0 && y != 0 )
	{ 
		m1 = w * z;
		m2 = x * y;
		g = gcd( m1 , m2 );
		n = m1 / g;
		d = m2 / g;

		if ( d != 1 )
		printf("\n%d / %d\n", n, d );
		else
		printf("\n%d\n", n );
	}
	else
		printf("\n0\n");

	return 0;
}
