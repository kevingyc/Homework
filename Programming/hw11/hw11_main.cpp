#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::getline;

#include "hw11.h"

int main( void )
{
    cout << "Test (1): constructor" << endl;
    Matrix A(4,4);
    A.display();

    cout << "\nTest (2): operator = (scalar value)" << endl;
    A = 1;
    A.display();

    cout << "\nTest (3): Load; Matrix A is:" << endl;
    A.load("hw11_data1.txt");
    A.display();
    Matrix B;
    cout << "\nMatrix B is:" << endl;
    B.load("hw11_data2.txt");
    B.display();

    cout << "\nTest (4-1): copy constructor, C(B)" << endl;
    Matrix C(B);

    cout << "\nTest (4-2): operator = (Matrix), C = A" << endl;
    C = A;
    C.display();

    cout << "\nDoes Matrix B change?" << endl;
    B.display();

    cout << "\nTest (5): C = B + B" << endl;
    Matrix D;
    C = B + B;
    C.display();

    cout << "\nTest (6): C = C - B" << endl;
    C = C - B;
    C.display();

    cout << "\nTest (7): C = A * B" << endl;
    C = A * B;
    C.display();
    
    Matrix X,Y,Z;
    X.load("hw11_data3.txt");
    Y.load("hw11_data4.txt");
    X.display();
    Y.display();
    
    Z = X+Y; 
    Z.display();
    Z = X-Y;
    Z.display();
    Z = X*Y;
	Z.display();
	
    // Pause
    string s;
    getline(cin, s);
    return 0;
}
