#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue* makeQueue(){
	queue* aqueue=(queue*) malloc(sizeof(queue));
	aqueue->head=NULL;
	aqueue->tail=NULL;
	aqueue->size=0;
	return aqueue;
}

void printQueue(queue* que){
	if(isQueueEmpty(que)==1){
		printf("queue is empty\n");
		return;
	}
	node* current=NULL;
	current=que->head;
	while(current!=NULL){
		printf("%d\n",current->value);
		current=current->next;
	}
}
node* deQueue(queue* que,int *empty){
	if(isQueueEmpty(que)==1){
		printf("Queue is empty\n");
		*empty=1;
		return que->head;
	}

	node* current=(node*) malloc(sizeof(node));
	current=que->head;
	current=current->next;
	free(que->head);
	if(que->size==1) {
		que->head=NULL;
		que->tail=NULL;
		que->size--;
		*empty=1;
		return que->head;
	}
	que->head=current;
	que->size--;
	*empty=0;
	return que->head;
}

queue* enQueue(int number,queue* que){
	if(isFull()==1){
		return que;
	}
	node* anode = (node*) malloc(sizeof(node));
	anode->next=NULL;
	anode->value=number;
		if(que->tail==NULL){
			que->head=anode;
			que->tail=anode;
			que->size++;
			return que;
		}
		else{
			que->tail->next=anode;
			que->tail=anode;
			que->size++;
			return que;
		}
}

node* findLastElement(queue* que){
	if(que->size==0)
		return NULL;
	else
	return que->tail;
}

int isQueueEmpty(queue* que){
	if(que->size==0){
		return 1;
	}
	else return 0;
}

int isFull(){
node* test=(node*) malloc(sizeof(node));
	if(test==NULL){
		free(test);
		return 1;
	}
	free(test);
	return 0;

}

queue* deleteQueue(queue* que, int *empty){
	do{
		que->head=deQueue(que,empty);
	}while(que->head!=NULL);
	return que;
}

int getSize(queue* que){
	return que->size;
}

int getHead(queue* que){
	if(getSize(que)==0){
		printf("Queue is empty \n");
		return -1;
	}
	return que->head->value;
}

