#ifndef queue_h
#define queue_h

#include <stdio.h>


typedef struct node{	
int value;
struct node* next;
}node;

typedef struct queue{
	node* head;
	node* tail;
	int size;

}queue;

void printQueue(queue*);
queue* makeQueue();
node* deQueue(queue*,int*);
queue* enQueue(int , queue*);
node* findLastElement(queue*);
int isQueueEmpty(queue*);
queue* deleteQueue(queue*,int*);
int isFull();
int getHead(queue*);
int getSize(queue*);
#endif