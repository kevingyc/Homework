#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::getline;

#include "hw12.h"
    
string s;
    
int main( void )
{
    cout << "Inital values of counters:" << endl;
    Matrix::displayCounters();

    cout << "Test (1): constructor" << endl;
    Matrix A(3,3);
    cout << "\nMatrix A is:" << endl;
    A = 3;
    A.display();

    cout << "Current values of counters:" << endl;
    Matrix::displayCounters();

    Matrix B(4,4);
    cout << "\nMatrix B is:" << endl;
    B = 4;
    B.display();

    cout << "Current values of counters:" << endl;
    Matrix::displayCounters();

    cout << "\nTest (2-1): copy constructor, C(B)" << endl;
    Matrix C(B);
    cout << "Current values of counters:" << endl;
    C.displayCounters();

    cout << "\nTest (2-2): operator = (Matrix), C = A" << endl;
    C = A;
    cout << "Current values of counters:" << endl;
    C.displayCounters();
    cout << "\nTest (3-1): C = A + A" << endl;
    C = A + A;
    C.display();
    cout << "Current values of counters:" << endl;
    Matrix::displayCounters();
 getline(cin, s);
    cout << "\nTest (3-2): C = B + B" << endl;
    C = B + B;
    C.display();
    cout << "Current values of counters:" << endl;
    Matrix::displayCounters();

    // Pause
    getline(cin, s);
    return 0;
}
