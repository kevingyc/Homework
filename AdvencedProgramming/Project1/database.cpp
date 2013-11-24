#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"database.h"
/* 
 * exchange two value 
 */
void Swap(Student &a , Student &b)
{
    Student t = a;
    a = b;
    b = t;
}
/* 
 * sort data by name 
 */
void Insertion_Sort(Student data[] , int size)
{
	int i;
	Student temp;
	for(int j = 1 ; j < size ; j++)
	{
		temp = data[j];								/* ���ƻs��ƥX�ӧ@������� */
		i = j-1;
		while(strcmp(temp.GetName(), data[i].GetName()) == -1 && i>=0)/* �p�Gtemp�p��L�e������ */
		{
			Swap(data[i+1],data[i]);				/* �h��̰��洫 */
			//data[i] = data[i+1];			
			i--;									/* �~��V�e��� */
		}
		data[i+1] = temp;							/* ��Jtemp�Ҧb����m */
	}
}

/* 
 * constructor 
 */
Database::Database()
{
	position_ = 0;
}

/* 
 * selection menu
 */
void Database::Instruction()
{
	printf("\nA simple database program\n\n");
	printf("(1) Add a reocrd\n");
	printf("(2) Show all records\n");
	printf("(3) Output record to a text file\n");
	printf("(4) Read in records from a text file\n");
	printf("(5) Exit the program\n\n");
	printf("Please select a function...> ");
}

/* 
 * add record in database 
 */
void Database::AddData(Student person)
{
	data_[position_] = person;
	position_++;
	Insertion_Sort(data_, position_);
}

/* 
 * display all record in database 
 */
void Database::Display()
{
	for(int i = 0 ; i < position_ ; i++)
	{
		printf("%s %c (%d) ",data_[i].GetName(), data_[i].GetGender(), data_[i].GetAge());
		for(int j = 0 ; j < Student::SCORE_NUM ; j++)
		{
			printf("%d ",data_[i].GetScore(j));
		}
		printf("\n");
	} 
}

/* 
 * read record from file 
 */
void Database::ReadFromFile(char filename[])
{
	FILE *fileptr;
	char gender, name[Student::NAME_LEN] = {'\0'};
	int age, score, i;
	if((fileptr = fopen(filename, "r")) != NULL)
	{
		for(i = 0 ; fscanf(fileptr,"%s",&name) != EOF ; i++)
		{
			fscanf(fileptr, " %c %d ", &gender, &age);
			data_[i].SetName(name);
			data_[i].SetGender(gender);
			data_[i].SetAge(age);
			for(int j = 0 ; j < Student::SCORE_NUM ; j++)
			{
				fscanf(fileptr, "%d ", &score);
				data_[i].SetScore(j, score);
			}
		}
		position_ = i;
	}
	else
	{
		printf("File Not Found\n");
	}
	fclose(fileptr);
}

/* 
 * output all record to a file
 */
void Database::WriteToFile(char filename[])
{
    FILE *fileptr = fopen(filename, "w"); 
    
    for(int i = 0 ; i < position_ ; i++)
    {
        fprintf(fileptr, "%s %c %d ",data_[i].GetName(), data_[i].GetGender(), data_[i].GetAge());
		for(int j = 0 ; j < Student::SCORE_NUM ; j++)
		{
			fprintf(fileptr, "%d ",data_[i].GetScore(j));
		}
		fprintf(fileptr, "\n");   
    }
    position_ = 0;
	fclose(fileptr);
}
