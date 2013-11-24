#include "ADT.h"    // 如要使用ADT裡面的Queue和Stack , 就要include ADT.h
#include <stdio.h>

void test(Stack in)
{
    while(!in.IsEmpty())
        in.Pop();
}
int main(void)
{
    int *data;  // 用來接收一副牌的資料
    int times = 1;
    while(times < 10){
        data = new_set_of_cards(times); // 要一副洗好的牌資料 , times為100次中的第幾次
        Stack s;  // 宣告出一個 Stack 叫做 s
        int i;    // counter
        for(i = 0 ; i < 52 ; i++ ){ // 把我們剛剛洗好的數字丟到 s 裡
            s.Push(data[i]);
        }      
        test(s);
        for(i = 0 ; i < 52 ; i++ ){ // 再把我們剛剛丟到 s 裡的數字一個個踢出來
            printf("%d,",s.Pop());  // 我們會發現踢出來的順序跟放進去的順序會相反
        }
        printf("\n");
        free(data); // 釋放記憶體
        times++;    // 次數增加準備執行下一次
    }
    return 0;
}
