#include<stdio.h>
#include<string.h>
#include"student.h"

Student::Student()
{
	for(int i = 0 ; i < NAME_LEN ; i++)
	{
		name_[i] = '\0';
	}

	for(int i = 0 ; i < SCORE_NUM ; i++)
	{
		score_[i] = 0;
	}
}

char Student::GetGender()
{
	return gender_;
}

void Student::SetGender(char gender)
{
	gender_ = gender;
}

int Student::GetAge()
{
	return age_;
}

void Student::SetAge(int age)
{
	age_ = age;
}

char *Student::GetName()
{
	return name_;
}

void Student::SetName(char name[])
{
	strcpy(name_,name);
}

int Student::GetScore(int position)
{
	return score_[position];
}

void Student::SetScore(int position, int score)
{
	score_[position] = score;
}
