#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::getline;

#include <iomanip>
using std::setw;

#include"hw10.h"

Matrix3::Matrix3()  // The default constructor
{
	setIdentity();
}

void Matrix3::add( Matrix3 source) // +
{
	for(int i = 0 ; i  < 9 ; i++)
	{
		data[i] += source.data[i];
	}
}

void Matrix3::sub( Matrix3 source) // -
{
	for(int i = 0 ; i  < 9 ; i++)
	{
		data[i] -= source.data[i];
	}
}

void Matrix3::mul( Matrix3 source) // *
{
	Matrix3 temp;

	for(int i = 0 ; i  < 9 ; i++)
	{
		if(i % 3 == 0) // i = 0,3,6
		{
			temp.data[i] = (data[i] * source.data[0]) + (data[i+1] * source.data[3]) + (data[i+2] * source.data[6]);
		}
		else if(i % 3 == 1) // i = 1,4,7
		{
			temp.data[i] = (data[i-1] * source.data[1]) + (data[i] * source.data[4]) + (data[i+1] * source.data[7]);
		}
		else // i = 2,5,8
		{
			temp.data[i] = (data[i-2] * source.data[2]) + (data[i-1] * source.data[5]) + (data[i] * source.data[8]);
		}
	}

	copy(temp);

}

void Matrix3::inverse() // 反矩陣
{
	MTYPE det;
	Matrix3 m;

	det = (data[0]*data[4]*data[8])
		 +(data[3]*data[7]*data[2])
		 +(data[6]*data[1]*data[5])
		 -(data[2]*data[4]*data[6])
		 -(data[5]*data[7]*data[0])
		 -(data[8]*data[1]*data[3]);

	if( det != 0 )
	{
		m.data[0] =  (data[4] * data[8]) - (data[5] * data[7]);
		m.data[1] =  (-1)*((data[1] * data[8]) - (data[2] * data[7]));
		m.data[2] =  (data[1] * data[5]) - (data[2] * data[4]);
		m.data[3] =  (-1)*((data[3] * data[8]) - (data[5] * data[6]));
		m.data[4] =  (data[0] * data[8]) - (data[2] * data[6]);
		m.data[5] =  (-1)*((data[0] * data[5]) - (data[2] * data[3]));
		m.data[6] =  (data[3] * data[7]) - (data[4] * data[6]);
		m.data[7] =  (-1)*((data[0] * data[7]) - (data[1] * data[6]));
		m.data[8] =  (data[0] * data[4]) - (data[1] * data[3]);

		for(int i = 0 ; i < 9 ; i++)
		{
			m.data[i] /= det;

			if( m.data[i] == -0 )
			{
				m.data[i] = 0;
			}
		}

		copy(m);
	}
	else
	{
		cout << "Inverse matrix not exist." << endl;
	}
}

void Matrix3::copy( Matrix3  source)
{
	for(int i = 0 ; i  < 9 ; i++)
	{
		data[i] = source.data[i];
	}
}

void Matrix3::setIdentity() //單位方陣
{
	for(int i = 0 ; i < 9 ; i++)
	{
		if(i % 4 == 0)
		{
			data[i] = 1;
		}
		else
		{
			data[i] = 0;
		}
	}
}

void Matrix3::setZero() //0方陣
{
	for(int i = 0 ; i  < 9 ; i++)
	{
		data[i] = 0;
	}
}

MTYPE Matrix3::get(int r, int c)
{
	if(r < 3 && c < 3 && r > -1 && c > -1)
	{
		return data[ 3 * r + c ];
	}
	else
	{
		cout << endl <<"Invalid row and column.";
		return 0;
	}
}

void Matrix3::load( string filename)
{

	FILE *inptr = fopen( filename.c_str(), "r");

	if(inptr != NULL)
	{
		for(int i = 0 ; i < 9 ; i++)
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

void Matrix3::display()
{
	for(int i = 0 ; i < 9 ; i++)
	{
		cout << setw (8) << data[i];

		if(i % 3 == 2)
		{
			cout << endl;
		}
		else
		{
			cout << " ";
		}
	}
}