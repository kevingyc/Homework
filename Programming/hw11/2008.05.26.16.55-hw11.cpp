#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::getline;

#include <iomanip>
using std::setw;

#include"hw11.h"

Matrix::Matrix(int r, int c) // The default constructor
{
	Row = r;
	Col = c; 
	data = new MTYPE[ r * c ];
	for(int i = 0 ; i < r * c ; i++ )//data = 0; 
	{
		data[ i ] = 0;	
	}
}

Matrix::Matrix( const Matrix& m )  // The copy constructor
{
	Row = m.Row;
	Col = m.Col; 
	data = new MTYPE[ Row * Col ];
	
	for(int i = 0 ; i < ( Row * Col ) ; i++ )//data = m; 
	{
		data[ i ] = m.data[ i ];	
	}
}

Matrix::~Matrix() // The destructor
{
	delete [] data;
}

const Matrix& Matrix::operator + ( const Matrix& m ) const
{
	static Matrix temp( Row, Col);
	
	if( equal( Row, m.Row) && equal( Col, m.Col) ) 
	{
		for( int i = 0 ; i < ( Row * Col ) ; i++)
		{
			temp.data[ i ] = data[ i ] + m.data[ i ];				
		}
	}
	else
	{
		cout << "can't do.";	
	}

	return temp;
} 

const Matrix& Matrix::operator - ( const Matrix& m ) const
{
	static Matrix temp( Row, Col);

	if( equal( Row, m.Row) && equal( Col, m.Col) ) 
	{		
		for( int i = 0 ; i < ( Row * Col ) ; i++)
		{
			temp.data[ i ] = data[ i ] - m.data[ i ];
		}
	}
	else
	{
		cout << "can't do.";	
	}
	return temp;
}

const Matrix& Matrix::operator * ( const Matrix& m ) const
{
	static Matrix temp( Row, m.Col );
			
	if( equal( Col, m.Row ) ) 
	{	
		for( int i = 0 ; i < ( Row * m.Col ) ; i++)
		{
			for( int j = ( i / Col ) * Col, k = i % m.Col ; 
			         j < Col * ( ( i / Col ) + 1 ), k < m.Col * m.Row ; 
					 j++, k = k + m.Col )
			{
				temp.data[ i ] = temp.data[ i ] + ( data [ j ] * m.data[ k ] );
			}
		}
	}
	else
	{
		cout << "can't do.";	
	}
	
	return temp;
}

const Matrix& Matrix::operator = ( const Matrix& m )
{

	if( equal( Row, m.Row) && equal( Col, m.Col) ) 
	{		
		for(int i = 0 ; i < ( Row * Col ) ; i++ )
		{
			data[ i ] = m.data[ i ];	
		}
		
		return *this;
	}
	else
	{
		Row = m.Row;
		Col = m.Col;
		
		delete [] data;
		data = new MTYPE[Row * Col];
		
		for(int i = 0 ; i < ( Row * Col ) ; i++ )
		{
			data[ i ] = m.data[ i ];	
		}
		
		return *this;
	}
	
}

const Matrix& Matrix::operator = ( MTYPE num )
{	
	for(int i = 0 ; i < (Row * Col) ; i++)
	{
		if(i % ( Col + 1 ) == 0)
		{
			data[ i ] = num;	
		}
		else
		{
			data[ i ] = 0;	
		}
	}
	return *this;
}

MTYPE Matrix::get( int r, int c )
{
	return data[ Col * r + c ];
}

void Matrix::load( string filename )
{
	FILE *inptr = fopen( filename.c_str(), "r");

	if(inptr != NULL)
	{
		fscanf(inptr, "%d %d", &Row, &Col);

		data = new MTYPE[ Row * Col ];
		
		for(int i = 0 ; i < ( Col * Row ) ; i++)
		{
			fscanf(inptr, "%f", &data[i]);
		}
	}
	else
	{
		cout << "File not found." << endl;
	}
	
	fclose (inptr);
}

void Matrix::display()
{
	for(int i = 0 ; i < (Col * Row) ; i++)
	{
		cout << setw (8) << data[i];
		
		if( i % Col == ( Col - 1 ))
		{
			cout << endl;
		}

	}
}

bool Matrix::equal( int x, int y ) const
{
	if( x == y)
	{
		return true;	
	}
	else
	{
		return false;	
	}
} 
