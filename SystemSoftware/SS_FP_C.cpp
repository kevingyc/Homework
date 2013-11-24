/* compiler environment : Microsoft Visual C++ 2008 Express version */
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<ctype.h>

#define reg_len 24;

typedef struct table
{
	char label[10];
	int address;
}TABLE;

typedef struct reg
{
	char label;
	int number;
}Register;

typedef struct instruct
{
	char label[10];
	int opcode, format;
}InstructionSet;

int STindex = 0, noobj = 0, Mindex = 0;
char nil[10] = "";

int Mrecord[20];
TABLE SymbolTable[100] = {"", 0};
Register RegTable[] = {'A', 0, 'X', 1, 'L', 2, 'B', 3, 'S', 4, 'T', 5, 'F', 6,};
InstructionSet ISTABLE[] = {// 59
"ADD", 0X18,3, "ADDF", 0X58,3, "ADDR", 0X90,2, "AND", 0X40,3,
"CLEAR", 0XB4,2, "COMP", 0X28,3, "COMPF", 0X88,3, "COMPR", 0XA0,2,
"DIV", 0X24,3, "DIVF", 0X64,3, "DIVR", 0X9C,2, "FIX", 0XC4,1,
"FLOAT", 0XC0,1, "HIO", 0XF4,1, "J", 0X3C,3, "JEQ", 0X30,3,
"JGT", 0X34,3, "JLT", 0X38,3, "JSUB", 0X48,3, "LDA", 0X00,3,
"LDB", 0X68,3, "LDCH", 0X50,3, "LDF", 0X70,3, "LDL", 0X08,3,
"LDS", 0X6C,3, "LDT", 0X74,3, "LDX", 0X04,3, "LPS", 0XD0,3,
"MUL", 0X20,3, "MULF", 0X60,3, "MULR", 0X98,2, "NORM", 0XC8,1,
"OR", 0X44,3, "RD", 0XD8,3, "RMO", 0XAC,2, "RSUB", 0X4C,3,
"SHIFTL", 0XA4,2, "SHIFTR", 0XA8,2, "SIO", 0XF0,1, "SSK", 0XEC,3,
"STA", 0X0C,3, "STB", 0X78,3, "STCH", 0X54,3, "STF", 0X80,3,
"STI", 0XD4,3, "STL", 0X14,3, "STS", 0X7C,3, "STSW", 0XE8,3,
"STT", 0X84,3, "STX", 0X10,3, "SUB", 0X1C,3, "SUBF", 0X5C,3,
"SUBR", 0X94,2, "SVC", 0XB0,2, "TD", 0XE0,3, "TIO", 0XF8,1,
"TIX", 0X2C,3, "TIXR", 0XB8,2, "WD", 0XDC,3
};

int check(char line[])
{
	if((int)line[0] != 9 && (int)line[0] != 32)
	{
		return 3;
	}
	else if(strlen(line) > 4)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int search_reg(char reg)
{
	int i;
	for(i = 0 ; i < 7 ; i++)
	{
		if(RegTable[i].label == reg)
			return RegTable[i].number;
	}
	return 0;
}



int inSymbol(char *line) // -1: not in table
{
	int i;
	char temp[10];
	strcpy(temp,strtok(line,"#@"));
	for(i = 0 ; i < STindex ; i++)
	{
		if(strcmp(SymbolTable[i].label,temp) == 0)
		{
			return SymbolTable[i].address;
		}
	}
	return -1;
}

int isComment(char *line)
{
	if(line[0] == '.')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
    
int isInstruction(char line[], char type[]) // 1: in table, 0: not in table
{
	int i;
	char temp[10];
	strcpy(temp,strtok(line,"#@+"));
	if(strcmp(type, "FORMAT") == 0)
	{
		for(i = 0 ; i < 59 ; i++)
		{
			if(strcmp(ISTABLE[i].label,temp) == 0)
			{
				return ISTABLE[i].format;
			}
		}
	}
	else if(strcmp(type, "OPCODE") == 0)
	{
		for(i = 0 ; i < 59 ; i++)
		{
			if(strcmp(ISTABLE[i].label,temp) == 0)
			{
				return ISTABLE[i].opcode;
			}
		}
	}
	return 0;
}

int ctoi(char location[], char type[])
{
	int position = 0;

	if(strcmp(type, "BYTE") != 0)
	{
		sscanf(location, "%d", &position);
	}
	else
	{
		if(location[0] == 'X')
		{
			return (strlen(location) - 3) / 2;
		}
		else if(location[0] == 'C')
		{
			return (strlen(location) - 3);
		}
	}
	return position;
}

void generate_objcode(char *objcode, char *operand, char type[])
{
	int l = strlen(operand);
	int i, j;
	if(strcmp(type, "WORD") == 0)
	{
		for(i = 0 ; i < 6 ; i++)
		{
			if(operand[5 - i] < '0')
			{
				objcode[i] = '0';
			}
			else
			{
				objcode[i] = operand[5 - i];
			}
		}
	}
	else if(strcmp(type, "BYTE") == 0)
	{
		if(operand[0] == 'X')
		{
			for(i = 0 ; i + 2 <= l - 2 ; i++)
			{
				objcode[i] = operand[i + 2];
			}
		}
		else if(operand[0] == 'C')
		{
			for(i = 0 , j = 2 ; j < l - 1 ; i += 2, j++)
			{
				objcode[i] = (int)operand[j] / 16 + 48; 
				if((int)objcode[i] > 57)
				{
					char temp = 'A';
					temp += (int)objcode[i] - 58;
					objcode[i] = temp;
				}
				objcode[i + 1] = (int)operand[j] % 16 + 48;
				if((int)objcode[i + 1] > 57)
				{
					char temp = 'A';
					temp += (int)objcode[i + 1] - 58;
					objcode[i + 1] = temp;
				}
			}
		}
	}
}

void read(char *label, char *opcode, char *operand, char *accept)
{
		if(check(accept) == 2)
		{
			sscanf(accept,"%s %s",opcode, operand);
			strcpy(label, nil);
		}
		else if(check(accept) == 1)
		{
			sscanf(accept,"%s",opcode);
			strcpy(label, nil);
			strcpy(operand, nil);
		}
		else
		{
			sscanf(accept,"%s %s %s",label, opcode, operand);
		}
}

void printMrecord()
{
	int i;
	for(i = 0 ; i < Mindex ; i++)
	{
		printf("M %06X 05\n", Mrecord[i]);
	}
}

int isHexadecimal(char *line)
{
	int k;

	for(k = 0 ; k < strlen(line) ; k++)
	{
		if(line[k] > '9' || line[k] < '0')
			return 1;
	}
	return 0;
}

int main()
{

	int start_loc = 0, locctr = 0 , end_loc, program_length = 0, instr_length = 0;
	char program_name[8] = {'\0'}, filename[] = "fig2.5.txt";
	
	FILE *fptr;
	
	char accept[100] = {'\0'};
   	char label[30], opcode[30], operand[30];

	int A = 0, X = 0, L = 0,PC = 0, SW = 0, B = 0, S = 0, T = 0, F = 0;
	int n = 1, i = 1, x = 0, b = 0, p = 0, e = 0, address = 0;

/************************************ pass 1 ****************************************/  	
	if((fptr = fopen(filename, "r")) != NULL)
	{
        //printf("file found\n");
        
        fgets(accept, 30, fptr);
		read(label, opcode, operand, accept);

        if(strcmp(opcode,"START") == 0)
        {
			int k, six = 1, hvalue = 0;
			strcpy(program_name, label);
			if(isHexadecimal(operand) == 1)
			{
				for(k = strlen(operand) - 1, six ; k >= 0 ; k--, six *= 16)
				{
					int temp = (int)operand[k] - 48;
					if(temp > 9)
					{
						temp = 10 + (int)operand[k] - 65;
					}

					hvalue += temp * six;
				}
				start_loc = hvalue;
				locctr = hvalue;
			}
			else
			{
				sscanf(operand, "%d", &start_loc);
				sscanf(operand, "%d", &locctr);
			}
        }
		else
		{
			locctr = 0;
		}

		fgets(accept, 30, fptr);
		read(label, opcode, operand, accept);


        while(!feof(fptr) && strcmp(opcode,"END") != 0)
        {
            if(isComment(accept) == 0) // not a comment
            {
				if(strlen(label) != 0)
				{
					if(inSymbol(label) != -1)
					{
						printf("error, duplicate symbol !!");
						return 0;
					}
					else
					{
						strcpy(SymbolTable[STindex].label, label);
						SymbolTable[STindex++].address = locctr; 
					}
				}

				if(isInstruction(opcode, "FORMAT") != 0)
				{
					if(opcode[0] == '+')
					{
						instr_length = 4;
					}
					else
					{
						instr_length = isInstruction(opcode, "FORMAT");
					}
				}
				else if(strcmp(opcode,"WORD") == 0)
				{
					instr_length = 3;
				}
				else if(strcmp(opcode,"RESW") == 0)
				{
					instr_length = 3 * ctoi(operand, "RESW");
				}
				else if(strcmp(opcode,"RESB") == 0)
				{
					instr_length = ctoi(operand, "RESB");
				}
				else if(strcmp(opcode,"BYTE") == 0)
				{
					instr_length = ctoi(operand, "BYTE");
				}
				else if(strcmp(opcode,"BASE") == 0)
				{
					instr_length = 0;
					int bp = inSymbol(operand);
					B = bp;
				}
				else if(strcmp(opcode,"END") == 0)
				{
					instr_length = 0;
				}
				else
				{
					printf("error, invaild operation code !!");
					return 0;
				}
            }

			locctr += instr_length;
			instr_length = 0;
			fgets(accept, 30, fptr);
			read(label, opcode, operand, accept);
        }

		end_loc = locctr;
		program_length =  end_loc - start_loc;
		fclose(fptr);
    }
    else
    {
        printf("file not found\n");
    }
/************************************ pass 2 ****************************************//*H T E M*/

	locctr = 0;
	instr_length = 0;

	if((fptr = fopen(filename, "r")) != NULL)
	{
        //printf("file found\n");

        fgets(accept, 30, fptr);
		read(label, opcode, operand, accept);

        if(strcmp(opcode,"START") == 0)
        {
			int k, six = 1, hvalue = 0;
			strcpy(program_name, label);
			if(isHexadecimal(operand) == 1)
			{
				for(k = strlen(operand) - 1, six ; k >= 0 ; k--, six *= 16)
				{
					int temp = (int)operand[k] - 48;
					if(temp > 9)
					{
						temp = 10 + (int)operand[k] - 65;
					}

					hvalue += temp * six;
				}
				locctr = hvalue;
			}
			else
			{
				sscanf(operand, "%d", &locctr);
			}
        }
		else
		{
			locctr = 0;
		}

		fgets(accept, 30, fptr);
		read(label, opcode, operand, accept);

		printf("H %-6s %06X %06X\n",program_name, start_loc, program_length);

        while(!feof(fptr) && strcmp(opcode,"END") != 0)
        {
			n = i = 1;
			x = b = p = e = 0;

			char object_code[50] = {'\0'};
            if(isComment(accept) == 0) // not a comment
            {
				if(strcmp(opcode,"WORD") == 0)
				{
					instr_length = 3;
					generate_objcode(object_code, operand, "WORD");
				}
				else if(strcmp(opcode,"RESW") == 0)
				{
					instr_length = 3 * ctoi(operand, "RESW");
				}
				else if(strcmp(opcode,"RESB") == 0)
				{
					instr_length = ctoi(operand, "RESB");
				}
				else if(strcmp(opcode,"BYTE") == 0)
				{
					instr_length = ctoi(operand, "BYTE");
					generate_objcode(object_code, operand, "BYTE");
				}
				else if(strcmp(opcode,"BASE") == 0)
				{
					instr_length = 0;
					noobj = 1;
				}
				else if(strcmp(opcode,"END") == 0)
				{
					instr_length = 0;
					noobj = 1;
				}
				else if(isInstruction(opcode, "FORMAT") != 0)
				{
					if(opcode[0] == '+')
					{			
						char temp[10] = {'\0'};
						strcpy(temp,strtok(operand,"#@"));
						if(inSymbol(temp) != -1)
						{
							Mrecord[Mindex++] = locctr + 1;  
						}

						instr_length = 4;
						e = 1;
						b = p = 0;
					}
					else
					{
						instr_length = isInstruction(opcode, "FORMAT");
					}
				}
				else
				{
					printf("error, invaild operation code !!");
					return 0;
				}
            }
/****************************************************************************************/			
			switch (operand[0])
			{
				case '@':
					n = 1; i = 0;
					break;
				case '#':
					n = 0; i = 1;
					break;
				default:
					n = i = 1;
					if(strstr(operand,",X")!=NULL)
					{
						x = 1;
						strtok(operand,",");
					}
					break;
			}

			if(inSymbol(operand) != -1)
			{
				b = 0; p = 1;
				if(opcode[0] == '+')
				{
					e = 1; b = p = 0;
				}
				address=inSymbol(operand);
			}
			else if(isdigit(operand[1])!=0)
			{
				sscanf(operand + 1,"%d",&address);
			}
			

			if(p == 1)
			{
				address = address - (locctr + instr_length);

				if(address > 2047 || address < -2048)
				{
					b = 1; p = 0;
					address = inSymbol(operand) - B;
				}
			}

			int format = isInstruction(opcode, "FORMAT"), op = isInstruction(opcode, "OPCODE");

			if(strcmp(opcode,"RSUB") == 0)
			{
				b = p = 0;
				address = 0;
			}
						
/******************************************************************************/
			char *head = (char*)malloc(4 * sizeof(char));
			if(format>=3)
			{
				op *= 16;	n *= 32;	i *= 16;	x *= 8;		b *= 4;		p *= 2;
				op += n + i + x + b + p + e;
				sprintf(object_code,"%03X",op);
			}
			else if(format==2)
				sprintf(object_code,"%02X",op);

			if(opcode[0]=='+')
				sprintf(object_code+3,"%05X",address);
			else if(format==3)
			{
				if(address<0)
				{
					sprintf(head,"%3hX",address);
					strcpy(object_code+3,head+1);
				}
				else
					sprintf(object_code+3,"%03X",address);
			}
			else if(format==2)
			{
				sprintf(object_code+2,"%1X",search_reg(operand[0]));
				if(strlen(operand) > 2)
					sprintf(object_code+3,"%1X",search_reg(operand[2]));
				else
					sprintf(object_code+3,"%1X",0);
			}

/*******************************************************************************/

			printf("T %06X %02X %s\n",locctr, strlen(object_code), object_code);

			locctr += instr_length;
			instr_length = 0;

			fgets(accept, 30, fptr);
			read(label, opcode, operand, accept);
        }
		printMrecord();
		printf("E %06X\n",start_loc);
		fclose(fptr);
    }
    else
    {
        printf("file not found\n");
    }

	//system("pause");
	return 0;	
}
