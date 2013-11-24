#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* new_set_of_cards(int times);

struct Queue{
public:
    Queue();
    void Add(int);      // 加入資料到Queue裡
    int Delete(void);   // 從Queue裡拿出資料並從Queue裡刪除
    bool IsEmpty(void); // 詢問Queue是否為空
    bool IsFull(void);  // 詢問Queue是否為滿
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
    int Pop(void);      // 從Stack裡踢出一個資料
    void Push(int);     // 塞一個資料到Stack裡
    int Top(void);      // 可以偷看最上面的資料但不取出
    bool IsEmpty(void); // 詢問Stack是否為空
    bool IsFull(void);  // 詢問Stack是否為滿
private:
    int data[100];
    int max_size;
    int top;
};

