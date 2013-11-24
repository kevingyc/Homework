#include <string>
using std::string;

// Assume the matrix elements are all floats
#define MTYPE float

class Matrix {
public:
       Matrix(int row=3, int col=3);
       Matrix(const Matrix&); //copy constructor 
      ~Matrix(); //destructor
      
       //void add( Matrix3 );  // replaced by operator +
       //void sub( Matrix3 );  // replaced by operator -
       //void mul( Matrix3 );  // replaced by operator *
       //void copy( Matrix3 ); // replaced by oerator = M
       //void setIdentity();   // replaced by oerator = 1
       //void setZero();       // replaced by oerator = 0
       //
       // NOTE: Please declare operators +, -, *, = here.
       // There should be two = operators, one for a Matrix operand,
       // and one for a scalar (i.e., MTYPE) operand.  For example,
       // M = 2 sets M to 2 along the diagonal and 0 elsewhere.
       //
       
       
       const Matrix operator + (const Matrix&) const; 
       const Matrix operator - (const Matrix&) const;
       const Matrix operator * (const Matrix&) const;
         
       const Matrix& operator = (const Matrix&);
       const Matrix& operator = (MTYPE);

	   MTYPE get(int, int);
       void load( string );
       void display();
       
       static void displayCounters();   
           
       bool equal(int, int) const;
	   
private:
        
       MTYPE *data;
       int Row;
       int Col;
       static int countercopy;
       static int counteropera;
};


