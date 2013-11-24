#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 200

struct Text 
{
	char s[SIZE];
	struct Text *nextptr;
};

typedef struct Text text;
typedef text *textptr;

void instruction();
void filesource( textptr *tptr,textptr *sptr );
void displayall(textptr currptr);
void displaythree( textptr currptr);
void search(textptr *currptr,textptr *firstptr, char cond[]);
void insertline( textptr *sptr, char value[] ,textptr *firstptr);
void deleteline(textptr *sptr,textptr *firstptr);
void replace();
void saveas(textptr *currptr);
int isempty(textptr headptr);

FILE *inptr;
FILE *outptr;

int main()
{
	int choice;
	char word[SIZE]={'\0'};
	
	textptr startptr = NULL;
	textptr disptr = NULL;
	textptr tempptr = NULL;
	filesource(&startptr,&tempptr);
	instruction();

	disptr = startptr;
	
	printf("> ");
	scanf("%d",&choice);

	while( choice != 8 )
	{
		switch(choice)
		{
			case 1:
				printf("1. Display all lines.\n");
				displayall(disptr);
				break;

			case 2:
				printf("2. Display the next 3 lines.\n");
				displaythree(startptr);
				break;

			case 3:
				printf("3. Search.\n");
				printf("Which word would you want to search ?\n"
					   "> ");
				getchar();
				gets(word);
				search(&startptr,&disptr,word);
				break;

			case 4:
				printf("4. Insert.\n");
				printf("Which word would you want to insert ?\n"
					   "> ");
				getchar();
				gets(word);
				insertline(&startptr, word, &disptr);
				break;

			case 5:
				printf("5. Delete. \n");
				deleteline(&startptr,&disptr);
				break;

			case 6:
				printf("6. Replace.\n");
				printf("Which word would you want to replace the old one ?\n"
					   "> ");
				getchar();
				gets(word);
				replace();
				break;

			case 7:
				printf("7. Save\n");
				saveas(&disptr);
				break;

			default:
				printf("Invaild selection. please choose again! \n\n");
				instruction();
				break;
		}

		printf("> ");
		scanf("%d",&choice);
	}

	printf("program will be exit.\n");
	return 0;
}

void instruction()
{
	printf("Which function do you want to do ?\n"
		   "1. Display all lines.\n"
		   "2. Display the next 3 lines.\n"
		   "3. Search.\n"
		   "4. Insert.\n"
		   "5. Delete.\n"
		   "6. Replace.(non-finished)\n"
		   "7. Save\n"
		   "8. Quit\n");

}

void filesource(textptr *sptr,textptr *tptr)
{
	textptr newptr;

	int n = 0;

	char read[SIZE]={'\0'};

	if( ( inptr = fopen("hw8_in.txt", "r") ) == NULL )
	{
  		printf( "File could not be opened\n" ); 	 
	}
	else
	{
		printf( "File opened.....\n\n" );

 		while( !feof( inptr ) )
		{
 			fgets(read, 100, inptr);
			newptr = malloc( sizeof( text ) );

			if( newptr != NULL)
			{
				strcpy(newptr->s,read);
				newptr->nextptr = NULL;

				if( isempty( *sptr ) )
				{
					*sptr = newptr;
				}
				else
				{
					(*tptr)->nextptr = newptr;
				}
					*tptr = newptr;
			}
			else
			{
				printf("Done.\n\n");
			}

		} 	  	 	
		fclose (inptr);   	  	 
	}
}


void displayall(textptr currptr)
{
	if( currptr == NULL )
	{
		printf("No data\n\n");
	}
	else
	{
		while( currptr != NULL )
		{
			printf("%s\n",currptr->s);
			currptr = currptr->nextptr;
		}
	}
}

void displaythree(textptr currptr)
{
	int i; 

	if( currptr == NULL )
	{
		printf("No data\n\n");
	}
	else
	{
		for( i = 0 ; i < 3 ; i++)
		{
			if(currptr->nextptr != NULL)
			{
				printf("%s\n",currptr->s);
				currptr = currptr->nextptr;
			}
			else
			{
				printf("%s\n",currptr->s);
				break;
			}
		}
	}
}

void search(textptr *currptr,textptr *firstptr, char cond[])
{
	int n = 0;
	textptr headptr = *firstptr;

	while( headptr != NULL )
	{
		if( strstr( headptr->s, cond ) == NULL )
		{
			headptr = headptr->nextptr;
		}
		else
		{
			printf("%s is found.\n",cond);
			n++;
			break;
		}
	}
		
	if( n == 0 )
	{
		printf("%s is not found.\n",cond);
	}

	(*currptr) = headptr;
}

void insertline( textptr *sptr, char value[],textptr *firstptr)
{ 
	textptr preptr;
	textptr currptr;
	textptr newptr;

	newptr = malloc( sizeof( text ) ); 

	if ( newptr != NULL ) 
	{ 
		strcpy(newptr->s,value);
		newptr->nextptr = NULL;

		if( (*sptr) != NULL)
		{
			preptr = *sptr;
			currptr = (*sptr)->nextptr;
			preptr->nextptr = newptr;

			if( currptr != NULL )
			{
				newptr->nextptr = currptr;
			}
			else
			{	
				newptr->nextptr = NULL;
			}
		}
		else
		{
			(*sptr) = newptr;
			(*firstptr) = newptr;
			newptr->nextptr = NULL;
		}
	}
	else
	{
		printf("%s not inserted. No memory available. \n", value);
	}
} 

void deleteline(textptr *sptr,textptr *firstptr)
{
	textptr tptr;
	textptr currptr;
	textptr preptr;	
	textptr headptr;

	if( (*sptr) != NULL )
	{
		preptr = *sptr;
		currptr = (*sptr)->nextptr;
		headptr = *firstptr;

		if( (*sptr) == (*firstptr) )
		{
			tptr = preptr;
			preptr = preptr->nextptr;
			(*sptr) = preptr;
			(*firstptr) = preptr;

			free(tptr);
		}
		else
		{		
			while(headptr->nextptr != preptr)
			{
				headptr = headptr->nextptr;
			}
		
			if( currptr == NULL )
			{
				tptr = preptr;
				preptr = headptr;
				preptr->nextptr = NULL;
				(*sptr) = preptr;

				free(tptr);
			}
			else
			{
				tptr = preptr;
				preptr = headptr;
				preptr->nextptr = currptr;
				(*sptr) = currptr;

				free(tptr);
			}
		}
	}
	else
	{
		printf("No Data.\n");
	}
}

void replace()
{
	
}

void saveas(textptr *currptr)
{
	char write[SIZE]={'\0'};

	outptr = fopen("hw8_out.txt", "w");

	if( *currptr == NULL )
	{
		printf("No data\n\n");
	}
	else
	{
		while( *currptr != NULL )
		{
			strcpy(write,(*currptr)->s);
			fputs(write,outptr);
			(*currptr) = (*currptr)->nextptr;
		}
		printf("Saved.\n");
	}
}

int isempty(textptr headptr)
{
	return headptr == NULL;	
}
