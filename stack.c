#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct stack{
  int top;
  int* a;
}stack;

bool isempty(struct stack s){
if(s.top ==0){
	return true;
}
return false;
}

void is(struct stack s) //initiate stack
{
  s.top=1;
  s.a=malloc(1*sizeof(int));
  return ;
}

void push(struct stack* s , int k){
  s->top++;
  s->a=realloc(s->a ,s->top*sizeof(int));
  s->a[s->top-1]=k;
  return ;
}

void display(struct stack s){
  int i=0;
  printf("elements in given stack are :\n");
  while(i<s.top){
    printf(" %d ",s.a[i]);
    i++;
  }
  printf("\n");
}

int pop(struct stack *s){
    int out;
    out = s->a[s->top-1];
    s->top--;
    s->a=realloc(s->a,(s->top)*sizeof(int));
    return out;
}

bool isInStack(struct stack s, int tofind){
    int i=0;
    while(i<s.top){
        if(s.a[i]==tofind) return true;
        i++;
    }
    return false;
}

