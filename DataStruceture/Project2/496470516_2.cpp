#include "ADT.h"												// �p�n�ϥ�ADT�̭���Queue�MStack , �N�ninclude ADT.h
#include <stdio.h>
#define SIZE 13

typedef struct number
{
	int sheets;														  // �i��
	int fstcardno,cardno;											  // �̤W�����P&�̤U�����P
	int fst,nth;													  // �̤W�����Ʀr&�̤U�����Ʀr
} Number;

int main(void)
{
	int *data;														  // �Ψӱ����@�ƵP�����
    int times = 1,total = 0;										  
	int faceu[SIZE][7] = {0};										  // 7 plies of face-up cards

	Queue stockcards;											      // storage facedown stock cards
	Stack wastecards;									              // storage face-up waste plie cards
	Stack faced[7];												      // 7 piles of facedown cards
	int Spade, Heart, Diamond, Club;						          // output plies
	Number num[7] = {0};											  // record faceu's status

    while(times <= 100)
	{
		int i = 0, j = 0, k = 0, action = 0;						  // counter, action�O�ʧ@�p�ƾ�
		int counter = 0;											  // �P�_�B�J�Ϊ��ܼ�
		int score = -52;											  // ����
		Club = Diamond = Heart = Spade = 0;							  // output plies initial
        data = new_set_of_cards(times);								  // �n�@�Ƭ~�n���P��� , times��100�������ĴX��

		for(i = 1; i <= 28 ;)										  // �o�P��U���C��row��
		{
			for(j = k; j < 7; j++ ,i++)
			{
				faced[j].Push(data[i-1]);
				num[j].fst = num[j].nth = (data[i-1] - 1) % 13;
				num[j].fstcardno = num[j].cardno = data[i-1];
			}
			k++;
		}

		for(i = 28 ; i < 52 ; i++)									  // �o�ѤU���P��P���
		{
			stockcards.Add(data[i]);
		}

		for(i = 0 ; i < 7 ; i++)									  // ½�}playing plie�̤U�����P
		{
			faceu[0][i] = faced[i].Pop();	
			num[i].sheets = 1;
		}

		wastecards.Push(stockcards.Delete());						  // �q�P��½�@�i�P��waste plie

		while(counter == 0)
		{
			counter = 1;			
//(a)�qwasteplie�Mplaying plie��̤W�誺�P����output��                      ( counter = 1 )
//   �p�Gwasteplie�ŤF�A�N�q�P��½�}�@�i�P���wasteplie	
/*-------------------------------------------------------------------------------------------------------*/		
			while(counter == 1)
			{	 /*----------wastecards part----------*/
				if((wastecards.Top() - 1) == (13 * 0) + Spade   ||(wastecards.Top() - 1) == (13 * 1) + Heart 
				 ||(wastecards.Top() - 1) == (13 * 2) + Diamond ||(wastecards.Top() - 1) == (13 * 3) + Club)
				{/*----------�i�H��W�h�����p---------*/
					score += 5;
					switch((wastecards.Top() - 1) / 13)
					{
						case 0:
							Spade++;
							break;
						case 1:
							Heart++;
							break;
						case 2:
							Diamond++;
							break;
						case 3:
							Club++;
							break;
					}
					wastecards.Pop();
					
					action++;
					if(wastecards.IsEmpty())
					{
						wastecards.Push(stockcards.Delete());
					}
					counter = 0;
					break;
				}	
				/*------playing plies part-------*/
				for(i = 0 ; i < 7 ; i++)
				{
					if((num[i].cardno - 1) == (13 * 0) + Spade   || (num[i].cardno - 1) == (13 * 1) + Heart 
				    || (num[i].cardno - 1) == (13 * 2) + Diamond || (num[i].cardno - 1) == (13 * 3) + Club)
					{/*-------�i�H��W�h�����p-------*/
						score += 5;
						switch((num[i].cardno - 1) / 13)
						{
							case 0:
								Spade++;
								break;
							case 1:
								Heart++;
								break;
							case 2:
								Diamond++;
								break;
							case 3:
								Club++;
								break;
						}
						num[i].sheets--;
						faceu[num[i].sheets][i] = 0;
						num[i].nth++;
						action++;

						if(num[i].sheets != 0) // faceu non-empty
						{
							num[i].cardno = faceu[num[i].sheets-1][i];
						}
						else // faceu empty
						{
							if(!faced[i].IsEmpty()) // faced non-empty
							{
								faceu[0][i] = faced[i].Pop();
								num[i].fstcardno = num[i].cardno = faceu[0][i];
								num[i].nth = num[i].fst = (faceu[0][i]-1) % 13;
								num[i].sheets = 1;
							}
							else// faced empty
							{
								num[i].sheets = num[i].fstcardno = num[i].cardno = num[i].nth = num[i].fst = 0;
							}
						}
						counter = 0;
						break;
					}
					else // have no action
					{
						counter = 2; // jump to step(b)
					}
				}	
			}
/*-------------------------------------------------------------------------------------------------------*/		
//(b)�qwasteplie���ʳ̤W�誺�P��playing plie�A�i�H���ʪ��ܥH�̥��䬰�D             ( counter = 2 )
//   �p�Gwasteplie�ŤF�A�N�q�P��½�@�i�P��wasteplie						
/*-------------------------------------------------------------------------------------------------------*/		
			while(counter == 2)
			{
				for(i = 0 ; i < 7 ; i++)
				{
					if(num[i].sheets != 0)  // faceu non-empty
					{
						if( (wastecards.Top() - 1) / 13 + (num[i].cardno - 1) / 13 != 3 && 
							(wastecards.Top() - 1) / 13 != (num[i].cardno- 1) / 13) // different color
						{
							if((wastecards.Top() - 1) % 13 == num[i].nth - 1) // point continue
							{
								num[i].nth--;
								num[i].cardno = wastecards.Pop();	
								faceu[num[i].sheets][i] = num[i].cardno;
								num[i].sheets++;
								action++;
	
								if(wastecards.IsEmpty())
								{		
									wastecards.Push(stockcards.Delete());
								}

								break;
							}
						}

					}
					else// faceu empty
					{
						if(wastecards.Top() % 13 == 0 && wastecards.Top() != 0) // K
						{
							num[i].fstcardno = num[i].cardno = faceu[num[i].sheets][i] = wastecards.Pop();	
							num[i].fst = num[i].nth = 12;
							num[i].sheets = 1;
							action++;

							if(wastecards.IsEmpty())
							{
								wastecards.Push(stockcards.Delete());
							}

						break;
						}
					}
				}
				if(action != 0)  // have action
				{
					counter = 0; // jump to step(a)
				}
				else // have no action
				{
					counter = 3; // jump to step(c)
				}
			}
/*-------------------------------------------------------------------------------------------------------*/		
/*(c)�q�̥����w�gfaceup��playing plie�A�O�_�i�H���ʦܨ�Lplaying plie              ( counter = 3 )
   �����ʬ��Ҧ��P�@��playing plie�U�Ҧ�faceup���P�@�_����					*/
/*-------------------------------------------------------------------------------------------------------*/		
			while(counter == 3)
			{
				for(i = 0 ; i < 7 ; i++)
				{	
					if(action != 0)     // have action
					{
						break;			
					}
					for(j = 0 ; j < 7 ; j++)
					{							
						int k = 0;     // program counter		
						if(num[i].sheets != 0 && i != j)// faceu non empty (source)
						{
							if(num[j].sheets != 0)// faceu non empty (target)
							{
								if( (num[i].fstcardno - 1) / 13 + (num[j].cardno - 1) / 13 != 3 && 
									(num[i].fstcardno - 1) / 13 != (num[j].cardno - 1) / 13) // different color
								{									
									if(num[i].fst == num[j].nth - 1) // point continue
									{
										while(k < num[i].sheets)
										{
											num[j].cardno = faceu[num[j].sheets][j] = faceu[k][i];
											faceu[k][i] = 0;
											num[j].sheets++;
											num[j].nth = (num[j].cardno - 1) % 13;
											k++;
										}
										action++;
										num[i].sheets = num[i].fstcardno = num[i].cardno = num[i].nth = num[i].fst = 0; // null, after move

										if(!faced[i].IsEmpty())
										{
											faceu[0][i] = faced[i].Pop();
											num[i].fstcardno = num[i].cardno = faceu[0][i];
											num[i].nth = num[i].fst = (faceu[0][i]-1)%13;
											num[i].sheets = 1;
										}
									}
								}
							}
							else// faceu empty
							{
								if((num[i].fst) == 12 && !faced[i].IsEmpty()) // K
								{
									num[j].fst = num[j].nth = 12;
									num[j].fstcardno = num[i].fstcardno;

									while(k < num[i].sheets)
									{
										num[j].cardno = faceu[num[j].sheets][j] = faceu[k][i];
										faceu[k][i] = 0;
										num[j].sheets++;
										num[j].nth = (num[j].cardno - 1) % 13;
										k++;
									}
									action++;
									num[i].sheets = num[i].fstcardno = num[i].cardno = num[i].nth = num[i].fst = 0;

									if(!faced[i].IsEmpty())
									{
										faceu[0][i] = faced[i].Pop();
										num[i].fstcardno = num[i].cardno = faceu[0][i];
										num[i].nth = num[i].fst = (faceu[0][i]-1)%13;
										num[i].sheets = 1;
									}
								}
							}
						}

						if(action != 0)
						{
							break;			
						}

					}
				}

				if(action != 0)    // have action
				{
					counter = 0;   // jump to step (a)
				}
				else               // have no action
				{
					counter = 4;   // jump to step (e)
				}	
			}
/*-------------------------------------------------------------------------------------------------------*/		
//(e)�p�G(a).(b).(c)�����ಾ�ʪ��ܡA�q�P��½�}�@�i�P���wasteplie�A�M��q(a)�B�J���s�P�_ ( counter = 4 )
/*-------------------------------------------------------------------------------------------------------*/		
			while(counter == 4)
			{
				if(!stockcards.IsEmpty())
				{
					wastecards.Push(stockcards.Delete());
				}
				counter = 0;					 // jump to step (a)
			}
/*-------------------------------------------------------------------------------------------------------*/			
			for(i = 0 ; i < 7 ; i++) // �ˬdplaying plie �̭��O���O�٦��i�H��boutput�̪��P, waste plie�̬O�_
			{						 // �i�H��bplaying plie�̥H��playing plie �O�_�٥i�H����, �Y�i���ʫhaction++
				if((num[i].cardno - 1) == (13 * 0) + Spade   || (num[i].cardno - 1) == (13 * 1) + Heart 
				 ||(num[i].cardno - 1) == (13 * 2) + Diamond || (num[i].cardno - 1) == (13 * 3) + Club)
				{
					action++;
				}
				if( (wastecards.Top() - 1) / 13 + (num[i].cardno - 1) / 13 != 3 && 
				    (wastecards.Top() - 1) / 13 != (num[i].cardno- 1) / 13) // different color
				{
					if((wastecards.Top() - 1) % 13 == num[i].nth - 1) // point continue
					{
						action++;
					}
				}
				for(j = 0 ; j < 7 ; j++)
				{											
					if(num[i].sheets != 0 && i != j)// faceu non empty (source)
					{
						if(num[j].sheets != 0)// faceu non empty (target)
						{
							if( (num[i].fstcardno - 1) / 13 + (num[j].cardno - 1) / 13 != 3 && 
								(num[i].fstcardno - 1) / 13 != (num[j].cardno - 1) / 13) // different color
							{									
								if(num[i].fst == num[j].nth - 1) // point continue
								{
									action++;
								}
							}
						}
					
						else
						{
							if((num[i].fst) == 12 && !faced[i].IsEmpty()) // K
							{
								action++;
							}
						}
					}
				}
			}
			if((wastecards.Top() - 1) == (13 * 0) + Spade  || (wastecards.Top() - 1) == (13 * 1) + Heart 
			||(wastecards.Top() - 1) == (13 * 2) + Diamond || (wastecards.Top() - 1) == (13 * 3) + Club)
			{                                  // �ˬdwaste plie�̭��O���O�٦��i�H��boutput�̪��P, �Y���haction++
				action++;
			}

			if(stockcards.IsEmpty()	&& action == 0) // �P��S�P�H�ΩҦ��P���i�A���ʮɵ����C��
			{  
				break;
			}
			action = 0;

		}    //play finish

		total += score;
		printf("%3d times score = %3d\n", times, score); //print score and times
		printf("\n");
/*---------------------------�M�Ÿ�ưʧ@---------------------------*/
		for(i = 0 ; i < 7 ; i++)
		{
			while(!faced[i].IsEmpty())
			{
				faced[i].Pop();
			}

			num[i].sheets = num[i].fstcardno = num[i].cardno = num[i].nth = num[i].fst = 0;

			for(j = 0 ; j < SIZE ; j++)
			{
				faceu[j][i] = 0;
			}
		}
		while(stockcards.IsEmpty() && wastecards.IsEmpty())
		{
			stockcards.Delete();
			wastecards.Pop();
		}
        free(data); // ����O����
        times++;    // ���ƼW�[�ǳư���U�@��
	}
	printf("        total = %5d\n",total);		//print total score
    return 0;
}

/*

1 ~ 13 : Spade (A, 2, 3, ..., J, Q, K) 
14 ~ 26 : Heart (A, 2, 3, ..., J, Q, K) 
27 ~ 39 : Diamond (A, 2, 3, ..., J, Q, K) 
40 ~ 52 : Club (A, 2, 3, ..., J, Q, K) 

--------------------------
  1  2  3  4  5  6  7
     8  9 10 11 12 13
       14 15 16 17 18
          19 20 21 22
             23 24 25
                26 27
                   28

(a)�qwasteplie�Mplaying plie��̤W�誺�P����output��
   �p�Gwasteplie�ŤF�A�N�q�P��½�}�@�i�P���wasteplie

(b)�qwasteplie���ʳ̤W�誺�P��playing plie�A�i�H���ʪ��ܥH�̥��䬰�D
   �p�Gwasteplie�ŤF�A�N�q�P��½�@�i�P��wasteplie

(c)�q�̥����w�gfaceup��playing plie�A�O�_�i�H���ʦܨ�Lplaying plie
   �����ʬ��Ҧ��P�@��playing plie�U�Ҧ�faceup���P�@�_����

(d)�̧ǹ���(a).(b).(c)�B�J�A����󲾰ʵo�ͪ��ɭԡA���^(a)�B�J���s�P�_

(e)�p�G(a).(b).(c)�����ಾ�ʪ��ܡA�q�P��½�}�@�i�P���wasteplie�A�M��q(a)�B�J���s�P�_

*/
