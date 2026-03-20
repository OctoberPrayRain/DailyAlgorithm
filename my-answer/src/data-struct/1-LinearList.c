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
    if (i > L->length || i < 1) {
        return false;
    }

    *e = L->data[i];
    return true;
}

bool ListInsert(SqList *L, unsigned i, ElemType e) {
    if (L->length == MAX_SIZE || i < 1 || i > L->length + 1) {
        return false;
    }

    for (int j = L->length; j > i-1; j--) {
        L->data[j] = L->data[j-1];
    }

    L->data[i-1] = e;
    L->length ++;
    return true;
}

unsigned LocateElem(const SqList *L, ElemType e) {
    for (int i = 0; i < L->length; i ++) {
        if (e == L->data[i]) {
            return i + 1;
        }
    }

    return 0;
}

void PrintList(const SqList *L) {
    for (int i = 0; i < L->length; i ++) {
        printf("%d ", L->data[i]);
    }
}

bool ListDelete(SqList *L, unsigned i, ElemType *e) {
    if (i < 1 || i > L->length) {
        return false;
    }

    *e = L->data[i - 1];

    for (int j = i - 1; j <= L->length - 1; j ++) {
        L->data[j] = L->data[j+1];
    }

    L->length --;
    return true;
}

int main(void) {
    SqList L;
    ElemType value;

    InitList(&L);

    ListInsert(&L, 1, 12);
    ListInsert(&L, 2, 13);
    ListInsert(&L, 3, 15);
    ListInsert(&L, 2, 4);
    ListInsert(&L, 2, 8);

    printf("当前顺序表: ");
    PrintList(&L);

    if (GetElem(&L, 3, &value)) {
        printf("第 3 个元素是: %d\n", value);
    }

    printf("元素 13 的位序是: %d\n", LocateElem(&L, 13));

    if (ListDelete(&L, 2, &value)) {
        printf("删除的元素是: %d\n", value);
    }

    printf("删除后的顺序表: ");
    PrintList(&L);

    return 0;
}
