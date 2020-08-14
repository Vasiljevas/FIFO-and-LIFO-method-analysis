#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Stack
{
    int element;
    struct Stack *next;
} Stack;

int peek(struct Stack *top);
int isStackEmpty(struct Stack *top);
void push(int data, struct Stack **top);
void pop(struct Stack **top);
void destroy(struct Stack **top);


#endif
