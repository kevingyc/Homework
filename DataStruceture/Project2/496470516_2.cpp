#include "ADT.h"												// 如要使用ADT裡面的Queue和Stack , 就要include ADT.h
#include <stdio.h>
#define SIZE 13

typedef struct number
{
	int sheets;														  // 張數
	int fstcardno,cardno;											  // 最上面的牌&最下面的牌
	int fst,nth;													  // 最上面的數字&最下面的數字
} Number;

int main(void)
{
	int *data;														  // 用來接收一副牌的資料
    int times = 1,total = 0;										  
	int faceu[SIZE][7] = {0};										  // 7 plies of face-up cards

	Queue stockcards;											      // storage facedown stock cards
	Stack wastecards;									              // storage face-up waste plie cards
	Stack faced[7];												      // 7 piles of facedown cards
	int Spade, Heart, Diamond, Club;						          // output plies
	Number num[7] = {0};											  // record faceu's status

    while(times <= 100)
	{
		int i = 0, j = 0, k = 0, action = 0;						  // counter, action是動作計數器
		int counter = 0;											  // 判斷步驟用的變數
		int score = -52;											  // 分數
		Club = Diamond = Heart = Spade = 0;							  // output plies initial
        data = new_set_of_cards(times);								  // 要一副洗好的牌資料 , times為100次中的第幾次

		for(i = 1; i <= 28 ;)										  // 發牌到下面七個row裡
		{
			for(j = k; j < 7; j++ ,i++)
			{
				faced[j].Push(data[i-1]);
				num[j].fst = num[j].nth = (data[i-1] - 1) % 13;
				num[j].fstcardno = num[j].cardno = data[i-1];
			}
			k++;
		}

		for(i = 28 ; i < 52 ; i++)									  // 發剩下的牌到牌堆裡
		{
			stockcards.Add(data[i]);
		}

		for(i = 0 ; i < 7 ; i++)									  // 翻開playing plie最下面的牌
		{
			faceu[0][i] = faced[i].Pop();	
			num[i].sheets = 1;
		}

		wastecards.Push(stockcards.Delete());						  // 從牌堆翻一張牌到waste plie

		while(counter == 0)
		{
			counter = 1;			
//(a)從wasteplie和playing plie把最上方的牌移至output區                      ( counter = 1 )
//   如果wasteplie空了，就從牌堆翻開一張牌放到wasteplie	
/*-------------------------------------------------------------------------------------------------------*/		
			while(counter == 1)
			{	 /*----------wastecards part----------*/
				if((wastecards.Top() - 1) == (13 * 0) + Spade   ||(wastecards.Top() - 1) == (13 * 1) + Heart 
				 ||(wastecards.Top() - 1) == (13 * 2) + Diamond ||(wastecards.Top() - 1) == (13 * 3) + Club)
				{/*----------可以放上去的狀況---------*/
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
					{/*-------可以放上去的狀況-------*/
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
//(b)從wasteplie移動最上方的牌到playing plie，可以移動的話以最左邊為主             ( counter = 2 )
//   如果wasteplie空了，就從牌堆翻一張牌到wasteplie						
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
/*(c)從最左邊找已經faceup的playing plie，是否可以移動至其他playing plie              ( counter = 3 )
   此移動為所有同一個playing plie下所有faceup的牌一起移動					*/
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
//(e)如果(a).(b).(c)都不能移動的話，從牌堆翻開一張牌放到wasteplie，然後從(a)步驟重新判斷 ( counter = 4 )
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
			for(i = 0 ; i < 7 ; i++) // 檢查playing plie 裡面是不是還有可以放在output裡的牌, waste plie裡是否
			{						 // 可以放在playing plie裡以及playing plie 是否還可以移動, 若可移動則action++
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
			{                                  // 檢查waste plie裡面是不是還有可以放在output裡的牌, 若有則action++
				action++;
			}

			if(stockcards.IsEmpty()	&& action == 0) // 牌堆沒牌以及所有牌不可再移動時結束遊戲
			{  
				break;
			}
			action = 0;

		}    //play finish

		total += score;
		printf("%3d times score = %3d\n", times, score); //print score and times
		printf("\n");
/*---------------------------清空資料動作---------------------------*/
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
        free(data); // 釋放記憶體
        times++;    // 次數增加準備執行下一次
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

(a)從wasteplie和playing plie把最上方的牌移至output區
   如果wasteplie空了，就從牌堆翻開一張牌放到wasteplie

(b)從wasteplie移動最上方的牌到playing plie，可以移動的話以最左邊為主
   如果wasteplie空了，就從牌堆翻一張牌到wasteplie

(c)從最左邊找已經faceup的playing plie，是否可以移動至其他playing plie
   此移動為所有同一個playing plie下所有faceup的牌一起移動

(d)依序嘗試(a).(b).(c)步驟，當任何移動發生的時候，跳回(a)步驟重新判斷

(e)如果(a).(b).(c)都不能移動的話，從牌堆翻開一張牌放到wasteplie，然後從(a)步驟重新判斷

*/
