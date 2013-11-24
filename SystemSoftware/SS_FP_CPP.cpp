#include<stdio.h> 
#include<stdlib.h> 

#define reg_len 24;

typedef struct table
{
	char label[6], opcode[6];
}TABLE;

char AssemblerDirectives[7][6] = {"START", "END", "BYTE", "WORD", "RESW", "RESB", "BASE"};


int Search(char word[], char type[], char address[])
{
    int i;
    
    if(strcmp(type, "ST") == 0) // a1
    {
        for(i = 0  ; i < STindex ; i++)   
        {
            if(strcmp(SymbolTable[i].label, word) == 0)   
            {
                return 1;   
            }
        }
        strcpy(SymbolTable[STindex++].label, word);
        strcpy(SymbolTable[STindex++].address, address);
    }
    else if(strcmp(type, "AD") == 0) // a2
    {
        for(i = 0  ; i < 7 ; i++)   
        {
            if(strcmp(AssemblerDirectives[i], word) == 0)   
            {
                return 1;   
            }
        }
    }
    else if(strcmp(type, "IS") == 0) // a2
    {
        for(i = 0  ; i < 20 ; i++)   
        {
            if(strcmp(Instruction[i], word) == 0)   
            {
                return 1;   
            }
        }
    }
    else if(strcmp(type, "SF") == 0) // a2, a3
    {
        for(i = 0 ; i < 5 ; i++)   
        {
            if(SpecialFormat[i] == word[0])
            {
                return 1;   
            }
            else
            {
                int j;
                for(j = 0 ; SpecialFormat[j] != '\0' ; j++)   
                {
                    if(word[j] == SpecialFormat[5])   // ,X (index mode)
                    {
                        return 1;   
                    }
                }
            }
        }
    }

    return 0;
}
    
    
    
int main()
{

    
    /*
	char A[reg_len] = {'\0'}, X[reg_len] = {'\0'}, L[reg_len] = {'\0'},PC[reg_len] = {'\0'}, SW[reg_len] = {'\0'},
		 B[reg_len] = {'\0'}, S[reg_len] = {'\0'}, T[reg_len] = {'\0'}, F[reg_len] = {'\0'};
	
	char start_loc[4], end_loc[4]
	*/
	
	FILE *fptr;
	
	char buffer[100], accept[100] = {'\0'};
	
	if((fptr = fopen("fig2.5.txt", "r")) != NULL)
	{
        printf("file found\n");
        while(!feof(fptr))
        {
          	char a1[10], a2[10], a3[10];
            fgets(accept, 30, fptr);
            if((int)accept[0] != 9)
            {
                sscanf(accept,"%s %s %s",a1, a2, a3);
                printf("%-6s     %-6s     %-6s\n",a1, a2, a3);
            }
            else
            {
                sscanf(accept,"%s %s",a2, a3);
                printf("           %-6s     %-6s\n", a2, a3);
            }
        }
    }
    else
    {
        printf("file not found\n");
    }
	system("pause");
	return 0;	
}
