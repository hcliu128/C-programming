#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 1024

typedef struct Stack_t{
    int arr[MAX_STACK_SIZE];
    int top;
}Stack;

void push(Stack* stack, int num){
    if(stack->top == MAX_STACK_SIZE - 1){
        printf("Stack Overflow\n");
        return;
    }
    stack->top++;
    stack->arr[stack->top] = num;  
    printf("Push %d into stack\n", stack->top);  
}

void pop(Stack* stack){
    if(stack->top == -1){
        printf("Stack Underflow\n");
        return;
    }
    printf("%d is popped\n", stack->top--);
}

int main(){
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1; // set top to -1
    pop(stack);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    printf("Numbers in Stack stack: %d\n", stack->top + 1); // top = -1 at beggining, so top will equal to count - 1
    for (int i = stack->top; i >= 0; i--){
        pop(stack);
    }
}