#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef int ElemType;

typedef struct {
        ElemType data[MAX_SIZE];
        int Length;
} SqList;

void InitList(SqList *L) {
        L->Length = 0;
}

bool IsEmpty(const SqList *L) {
        return L->Length == 0;
}

int ListLength(const SqList *L) {
        return L->Length;
}

bool GetElem(const SqList *L, const int i, ElemType *e) {
        if (i < 1 || i > L->Length || e == NULL) {
                return false;
        }

        *e = L->data[i-1];
        return true;
}


int GetLocate(const SqList *L, const ElemType e) {
        for (int i = 0; i < L->Length; i ++) {
                if (L->data[i] == e) {
                        return i + 1;
                }
        }

        return 0;
}

bool InsertList(SqList *L, const int i, const ElemType e) {
        if (i < 1 || i > L->Length + 1 || L->Length == MAX_SIZE) {
            return false;
        }

        for (int j = L->Length - 1; j >= i - 1; j ++) {
                L->data[j + 1] = L->data[j];
        }

        L->data[i - 1] = e;
        L->Length ++;
        return true;
}

bool RemoveList(SqList *L, const int i, ElemType *e) {
        if (L->Length == 0 || i > L->Length || i < 1 || e == NULL) {
                return false;
        }

        *e = L->data[i - 1];

        for (int j = i; j < L->Length; j ++) {
                L->data[j - 1] = L->data[j];
        }

        L->Length --;
        return true;
}

void PrintList(const SqList *L) {
        for (int i = 0; i < L->Length; i ++) {
                printf("%d ", L->data[i]);
        }

        printf("\n");
}
