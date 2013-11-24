// Comment out the next line when you're done with debugging.
#define DEBUG
#define MAX_ARRAY_SIZE 1000
#include <time.h>

#ifdef DEBUG
#include <assert.h>
#endif

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::getline;

/*****************************************************************************
** Task #1: fill in the missing parts in the declarations for class SafeArray
******************************************************************************/

class SafeArray {
      int data[MAX_ARRAY_SIZE];
      int size;
public:
      // Fill in the missig prototypes of
      // the constructor and member functions here.  
	  
	  SafeArray();
	  
	  SafeArray(int initialSize);
	  
	  void setData(int i,int newData);
	  
	  int getData(int i);


};

SafeArray::SafeArray()
{
    size = 0;
}

/***********************************************************************
*** Task #2: fill in the missing parts in the following member functions.
************************************************************************/

SafeArray::SafeArray(int initialSize)
{
// Fill in the missig instruction(s) in this member function.
// You may initialize your array here, but the initialization is not required
// in this assignment.
	size = initialSize;
	for(int i = 0;i<size;i++)
	{
		data[i] = 0;
	}
}

void SafeArray::setData(int i, int newData)
{
// Fill in the missig instruction(s) in this member function.

// NOTE: You must check whether the index i is out of range.
// If i is out of range, then use assert() to show an error for debugging.

#ifdef DEBUG
       assert(i < size);/* add your assertion here */
#endif
	   data[i] = newData;
}

int SafeArray::getData(int i)
{
// Fill in the missig instruction(s) in this member function.

// NOTE: You must check whether the index i is out of range.
// If i is out of range, then use assert() to show an error for debugging.
// If i is OK, then the return value should be data[i].

#ifdef DEBUG
       assert(i < size);/* add your assertion here */
#endif
	   return data[i];
}


int main( void )
{
    int smallSize = 10;
    int i, randomI, randomData;
    SafeArray array( smallSize );

	srand(time(NULL));

    // Fill in the array randomly.
    // Note that we have created an out-of-range error here on purpose.
    for (i=0; i<smallSize; i++) {
        randomI = rand() % (smallSize + 1);  // Creating a bug here for testing.
        randomData = rand() % 1000;
        array.setData(randomI, randomData);
    }

    // Display the current content of the array.
    for (i=0; i<smallSize; i++) {
        cout << "array[" << i << "]=" << array.getData(i) << endl;
    }

    // Pause
    string s;
    getline(cin, s);
    return 0;
}
