#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Stack {
  int top;
  unsigned capacity;
  char* array;
};


struct Stack* createStack(unsigned capacity)
{
  struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (char*)malloc(stack->capacity * sizeof(int));
  return stack;
}

bool isFull(struct Stack* stack)
{
  return stack->top == stack->capacity - 1;
}

bool isEmpty(struct Stack* stack)
{
  return (stack->top == -1);
}

bool isntEmpty(struct Stack* stack)
{
  return !(stack->top == -1);
}


void push(struct Stack* stack, char item)
{
  if (isFull(stack))
    return;
  stack->array[++stack->top] = item;
}

char pop(struct Stack* stack)
{
  if (isEmpty(stack))
    return 'q';
  return stack->array[stack->top--];
}

char peek(struct Stack* stack)
{
  if (isEmpty(stack))
    return 'q';
  return stack->array[stack->top];
}

bool symcheck(char* in, int i){
  if (in[i] == '+'||in[i] == '-'||in[i] == '*'||
      in[i] == '/'||in[i] == '^'||in[i] == '!'||
      in[i] == '('||in[i] == ')'){return true;}
  else {return false;}}

bool opcheck(char in){
  if (in == '+'||in == '-'||in == '*'||
      in == '/'||in == '^'||in == '!'){return true;}
  else {return false;}}

int priority (char a){ // For an operator, prints its precedence value //
  int ai;
  int bi;
  if (a=='+'){ai = 0;} else if (a=='-'){ai = 1;} else if (a=='*'){ai = 2;}
  else if (a=='/'){ai = 3;} else if (a=='^'){ai = 4;} else if (a=='!'){ai = 5;}
  return ai;}

void append (char* s, char c){
  int len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';
}

char* order(char* in){ 
  int n = strlen(in);
  int j = 0;
  char *out = malloc(10000*sizeof(char));
  struct Stack* stack = createStack(n+1);
  
  for (int i=0; i <= n; i++){
    if (opcheck(in[i])){
      while (opcheck(peek(stack)) && priority(in[i]) < priority(peek(stack))){
        append(out,pop(stack));append(out,',');
      };push(stack, in[i]);
    }
    else if (in[i] == '('){push(stack, in[i]);}
    else if (in[i] == ')'){
      while (peek(stack) != '('){append(out, pop(stack));append(out,',');}pop(stack);}
    else if (in[i] == ' ');
    else if (isdigit(in[i])){ 
      while(isdigit(in[i])){
        append(out, in[i]);i++;}i--;append(out,',');}
    }
    while(!isEmpty(stack)){append(out,pop(stack));append(out,',');}
    if (out[strlen(out)-1] == ','){out[strlen(out)-1] = '\0';}
  
  return out;
}


int main(int argc, char **argv){

  char* input;

  scanf("%s", input);

  printf("%s\n", order(input));
  return 0;
}

