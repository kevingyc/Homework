#include "ADT.h"    // �p�n�ϥ�ADT�̭���Queue�MStack , �N�ninclude ADT.h
#include <stdio.h>

void test(Stack in)
{
    while(!in.IsEmpty())
        in.Pop();
}
int main(void)
{
    int *data;  // �Ψӱ����@�ƵP�����
    int times = 1;
    while(times < 10){
        data = new_set_of_cards(times); // �n�@�Ƭ~�n���P��� , times��100�������ĴX��
        Stack s;  // �ŧi�X�@�� Stack �s�� s
        int i;    // counter
        for(i = 0 ; i < 52 ; i++ ){ // ��ڭ̭��~�n���Ʀr��� s ��
            s.Push(data[i]);
        }      
        test(s);
        for(i = 0 ; i < 52 ; i++ ){ // �A��ڭ̭���� s �̪��Ʀr�@�ӭӽ�X��
            printf("%d,",s.Pop());  // �ڭ̷|�o�{��X�Ӫ����Ǹ��i�h�����Ƿ|�ۤ�
        }
        printf("\n");
        free(data); // ����O����
        times++;    // ���ƼW�[�ǳư���U�@��
    }
    return 0;
}
