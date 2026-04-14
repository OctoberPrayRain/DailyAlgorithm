#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 20

typedef int ElemType;

typedef struct {
        ElemType data[MAX_SIZE];
        int length;
} SqList;

void InitList(SqList *L) {
        L->length = 0;
}

bool IsEmpty(const SqList *L) {
        return L->length == 0;
}

int ListLength(const SqList *L) {
        return L->length;
}

ElemType GetElem(const SqList *L, int i) {
        if (i < 1 || i > L->length) {
                return -1;
        }
        return L->data[i-1];
}

int GetLocate(const SqList *L, const ElemType e) {
        for (int i = 0; i < L->length; i ++) {
                if (L->data[i] == e) {
                        return i + 1;
                }
        }

        return -1;
}

bool InsertList(SqList *L, const int i, const ElemType e) {
        if (L->length >= MAX_SIZE || i < 1 || i > L->length + 1) {
                return false;
        }

        for (int j = L->length - 1; j >= i - 1; j --) {
                L->data[j + 1] = L->data[j];
        }

        L->data[i-1] = e;
        L->length ++;
        return true;
}

bool RemoveList(SqList *L, const int i, ElemType *e) {
        if (i < 1 || i > L->length) {
                return false;
        }

        *e = L->data[i-1];

        for (int j = i - 1; j < L->length - 1; j ++) {
                L->data[j] = L->data[j + 1];
        }

        L->length --;

        return true;
}

void PrintList(const SqList *L) {
        for (int i = 0; i < L->length; i ++) {
                printf("%d ", L->data[i]);
        }

        printf("\n");
}

void test() {
        SqList L;
        ElemType e;

        InitList(&L);
        printf("初始化后顺序表长度：%d\n", L->length);

        if (IsEmpty(&L)) {
                printf("顺序表为空\n");
        } else {
                printf("顺序表不为空\n");
        }

        InsertList(&L, 1, 12);
        InsertList(&L, 1, 13);
        InsertList(&L, 3, 14);

        printf("当前顺序表为：");
        PrintList(&L);

        if (InsertList(&L, 5, 1)) {
                printf("插入成功\n");
        } else {
                printf("插入失败\n");
        }

        printf("%d元素的位置为：%d\n", 12, GetLocate(&L, 12));
        printf("%d元素的位置为：%d\n", 15, GetLocate(&L, 15));

        if (RemoveList(&L, 3, &e)) {
                printf("移除成功，现在的顺序表为：");
                PrintList(&L);
       } else {
                printf("移除失败\n");
       }

       printf("e 的值为：%d\n", e);
}

int main() {
        test();
        return 0;
}
