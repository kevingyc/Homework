#include<stdio.h>
#include<stdlib.h>
#include"database.h"

int main()
{
    Database database;
	Student std_data;
	int choice = 1;
	char filename[Student::NAME_LEN];

	while(choice != 5)
	{
		database.Instruction();
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:	/* Add a reocrd */
				int age, score;
				char gender, name[Student::NAME_LEN];
				
				getchar();

				printf("\nPlease enter student's name : ");
				gets(name);
				std_data.SetName(name);

				printf("Please enter student's gender(M/F) : ");
				scanf("%c", &gender);
				std_data.SetGender(gender);

				printf("Please enter student's age : ");
				scanf("%d", &age);
				std_data.SetAge(age);

				for(int i = 0 ; i < Student::SCORE_NUM ; i++)
				{
					printf("Please enter student's %dth score : ", i + 1);
					scanf("%d", &score);
					std_data.SetScore(i, score);
				}

				database.AddData(std_data);
				break;
			case 2:	/* Show all records */
				database.Display();
				break;
			case 3:	/* Output record to a text file */
				getchar();
				printf("\nPlease enter input file name : ");
				gets(filename);
				database.WriteToFile(filename);
				break;
			case 4:	/* Read in records from a text file */
				getchar();
				printf("\nPlease enter output file name : ");
				gets(filename);
				database.ReadFromFile(filename);
				break;
			default:
				break;
		}
	}

	return 0;
}
