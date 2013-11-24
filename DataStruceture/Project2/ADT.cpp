#include "ADT.h"

Queue::Queue(void)
{
    max_size = 100;
    front = rear = size = 0;
}
bool Queue::IsFull(void)
{
    return ((size == max_size)? true : false);
}
bool Queue::IsEmpty (void)
{
    return ((size == 0)? true : false);
}
void Queue::Add(int in)
{
    if(!IsFull()){
        data[front] = in;
        front = (front + 1) % max_size;
        size++;
    }
}
int Queue::Delete(void)
{
    if(!IsEmpty()){
        int output = data[rear];
        rear = (rear + 1) % max_size;
        size--;
        return output;
    }
    return 0;
}

Stack::Stack()
{
    max_size = 100;
    top = 0;
}

bool Stack::IsEmpty(void)
{
    return ((top == 0)? true : false);
}
bool Stack::IsFull(void)
{
    return ((top == max_size)? true : false);
}
int Stack::Pop(void)
{
    if(!IsEmpty()){
        return data[(top--)-1];
    }
    return 0;
}
void Stack::Push(int in)
{
    if(!IsFull()){
        data[top++] = in;
    }
}
int Stack::Top(void)
{
    if(!IsEmpty()){
        return data[top - 1];
    }
    return 0;
}
int* new_set_of_cards(int times)
{
    static bool rand_time = true;
    if(rand_time){
        srand(time(NULL)); 
        rand_time = false;
    }
    int *in = (int *) malloc (sizeof(int) * 52);
    int i , a , b , t;
    if(times == 1){
        for(i = 0 ; i < 52 ; i++ ){
            in[i] = i + 1;
        }
    }
    else if(times == 2){
        for(i = 0 ; i < 52 ; i++ ){
            in[i] = 52 - i;
        }
    }
    else if(times == 3){
        int temp[52] = {36,32,24,10,8,51,30,46,13,40,42,37,50,1,11,39,43,47,23,19,21,7,12,25,29,15,45,34,41,52,33,14,5,48,38,3,17,27,22,4,31,28,6,16,2,49,9,35,20,26,44,18};
        //int temp[52] = {21,16,6,46,34,35,5,26,25,17,42,8,15,4,49,39,36,9,7,32,3,10,18,50,13,11,52,47,41,45,33,30,28,12,37,40,14,27,44,43,22,20,29,1,19,2,24,23,31,38,48,51};
		for(i = 0 ; i < 52 ; i++ ){
            in[i] = temp[i];
        }
    }    
    else{
        for(i = 0 ; i < 52 ; i++ ){
            in[i] = i+1;
        }
        for(i = 0 ; i < 100 ; i++ ){
            a = rand() % 52;
            b = rand() % 52;
            t = in[a];
            in[a] = in[b];
            in[b] = t;
        }
    }
    return in;
}