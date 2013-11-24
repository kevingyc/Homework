#include<stdio.h>
#include<string.h>

class Student
{
	public:
		static const int SCORE_NUM = 3, NAME_LEN = 30;

		Student();

		char GetGender();
		void SetGender(char g);
		int GetAge();
		void SetAge(int a);
		char* GetName();
		void SetName(char *n);
		int GetScore(int position);
		void SetScore(int position, int s);


	private:
		char name_[NAME_LEN], gender_;
		int score_[SCORE_NUM], age_;
};
