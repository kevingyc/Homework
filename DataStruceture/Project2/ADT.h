#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* new_set_of_cards(int times);

struct Queue{
public:
    Queue();
    void Add(int);      // �[�J��ƨ�Queue��
    int Delete(void);   // �qQueue�̮��X��ƨñqQueue�̧R��
    bool IsEmpty(void); // �߰�Queue�O�_����
    bool IsFull(void);  // �߰�Queue�O�_����
private:
    int data[100];
    int max_size;
    int size;
    int front;
    int rear;
};
struct Stack{
public:
    Stack();
    int Pop(void);      // �qStack�̽�X�@�Ӹ��
    void Push(int);     // ��@�Ӹ�ƨ�Stack��
    int Top(void);      // �i�H���ݳ̤W������Ʀ������X
    bool IsEmpty(void); // �߰�Stack�O�_����
    bool IsFull(void);  // �߰�Stack�O�_����
private:
    int data[100];
    int max_size;
    int top;
};

