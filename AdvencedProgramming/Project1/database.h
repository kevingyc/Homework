#include<stdio.h>
#include"student.h"

class Database
{
	public:
        static const int DATA_NUM = 200;
        
		Database();
		
        void AddData(Student person);
		void Display();
		void ReadFromFile(char filename[]);
		void WriteToFile(char filename[]);
		void Instruction();

	private:
		int position_;
		Student data_[DATA_NUM];
};
