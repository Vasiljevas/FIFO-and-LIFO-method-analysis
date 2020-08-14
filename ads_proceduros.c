#include "ads_proceduros.h"
#include <stdio.h>
#include <stdlib.h>

int peek(struct Stack *top)
{
    if (isStackEmpty(top)==0)
    {
        return top->element;
    }
    else exit(EXIT_FAILURE);
}

int isStackEmpty(struct Stack *top)
{
    return top == NULL;                 //true - grazina 1, false - grazina 0
}

void push(int data, struct Stack **top)
{
    Stack *first = (Stack*)malloc(sizeof(Stack));    //isskiria tiek bitu, kiek uzima nurodytas tipas

    first->element = data;          //priskiriam duomenis sukurtam elementui
    first->next = *top;             //nurodome, kad sukurto elemento rodykle rodytu i steko virsune
    *top = first;                   //steko virsune - naujai sukurtas elementas
}

void pop(struct Stack **top)
{
    Stack *temp;

    if(*top!=NULL)
    {  
         temp = *top;               //priskiriam steko virsune
         *top = (*top)->next;       //steko virsune priskiriam sekanciam elementui

         free(temp);
    }
    else exit(EXIT_FAILURE);

}

void destroy(struct Stack **top)
{
    Stack *current = *top;
    Stack *next;

    while (current != NULL)    //kol stekas netuscias
    {
        next = current->next;    //priskiriam sekanciam
        free(current);           
        current = next;
    }
    *top = NULL;
}

