/*
        一个顺序栈，只有 push 和 pop 是在同一个口，并且栈内存放的元素只为 int
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 20

typedef int ElemType;

typedef struct SqStack {
        ElemType data[MAX_SIZE];
        int top;
} SqStack;

void InitStack(SqStack *S) {
        S->top = 0;
}

bool StackEmpty(const SqStack *S) {
        return S->top <= 0;
}

int StackLength(const SqStack *S) {
        return S->top;
}

bool Push(SqStack *S, ElemType e) {
        if (S->top >= MAX_SIZE) {
                // 栈满了
                return false;
        }

        S->data[S->top] = e;

        S->top ++;
        
        return true;
}

bool Pop(SqStack *S, ElemType *e) {
        if (S -> top <= 0) {
                // 如果栈内本身就没有内容，直接返回 false
                return false;
        }

        *e = S->data[S->top - 1];

        S->top --;

        return true;
}

void PrintStack(const SqStack *S) {
        if (StackEmpty(S)) {
                printf("Stack is Empty now.\n");
                return;
        }

        for (int i = 0; i < S->top; i ++) {
                printf("%d ", S->data[i]);
        }

        printf("\n");
}

int main() {
        SqStack s;
        ElemType e;
        InitStack(&s);
        PrintStack(&s);
        Push(&s, 12);
        Push(&s, 13);
        Push(&s, 14);
        PrintStack(&s);
        printf("%d\n", StackLength(&s));

        Pop(&s, &e);
        printf("%d\n", e);

        Pop(&s, &e);
        printf("%d\n", e);

        Pop(&s, &e);
        printf("%d\n", e);

        PrintStack(&s);
        printf("%d\n", StackLength(&s));

        return 0;
}
