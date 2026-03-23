#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 50

typedef int ElemType;

typedef struct{
    ElemType data[MAX_SIZE];
    unsigned length;
} SqList;

void InitList(SqList *L) {
    L->length = 0;
}

bool ListEmpty(const SqList *L) {
    return L->length == 0;
}

unsigned ListLength(const SqList *L) {
    return L->length;
}

bool GetElem(const SqList *L, unsigned i, ElemType *e) {
    if (i == 0 || i > L->length) {
        return false;
    }

    *e = L->data[i - 1];
    return true;
}

bool ListInsert(SqList *L, unsigned i, ElemType e) {
    if (L->length == MAX_SIZE || i == 0 || i > L->length + 1) {
        return false;
    }

    for (unsigned j = L->length; j > i - 1; j--) {
        L->data[j] = L->data[j-1];
    }

    L->data[i-1] = e;
    L->length ++;
    return true;
}

unsigned LocateElem(const SqList *L, ElemType e) {
    for (unsigned i = 0; i < L->length; i ++) {
        if (e == L->data[i]) {
            return i + 1;
        }
    }

    return 0;
}

void PrintList(const SqList *L) {
    for (unsigned i = 0; i < L->length; i ++) {
        printf("%d ", L->data[i]);
    }
}

bool ListDelete(SqList *L, unsigned i, ElemType *e) {
    if (i == 0 || i > L->length) {
        return false;
    }

    *e = L->data[i - 1];

    for (unsigned j = i - 1; j < L->length - 1; j ++) {
        L->data[j] = L->data[j+1];
    }

    L->length --;
    return true;
}
