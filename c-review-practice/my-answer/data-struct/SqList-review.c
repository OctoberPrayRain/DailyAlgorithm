#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 20

typedef int ElemType;

typedef struct SqList {
        int length;
        ElemType data[MAX_SIZE];
} SqList;

bool InitList(SqList *L) {
        if (L==NULL) {
                return false;
        }

        L->length = 0;
        return true;
}

bool IsEmpty(const SqList *L) {
        return (L == NULL || L->length == 0);
}

bool InsertList(SqList *L, int i, ElemType e) {
        if (L == NULL || i < 1 || L->length >= MAX_SIZE || i > L->length + 1) {
                return false;
        }

        for (int j = L->length; j >= i; j --) {
                L->data[j] = L->data[j - 1];
        }

        L->data[i-1] = e;
        L->length ++;
        
        return true;
}

bool RemoveList(SqList *L, int i, ElemType *e) {
        if (L == NULL || e == NULL || i < 1 || i > L->length) {
                return false;
        }

        *e = L->data[i - 1];

        for (int j = i; j < L->length; j ++) {
                L->data[j - 1] = L->data[j];
        }

        L->length --;

        return true;
}

int GetLength(const SqList *L) {
        if (L == NULL) {
                return 0;
        }

        return L->length;
}

int GetLocation(const SqList *L, ElemType e) {
        if (L == NULL) {
                return 0;
        }    // 0表示没找到

        for (int i = 1; i <= L->length; i ++) {
                if (L->data[i-1] == e) {
                        return i;
                }
        }

        return 0;
}

void PrintList(const SqList *L) {
        if (L == NULL || L->length == 0) {
                printf("List empty!\n");
                return;
        }

        for (int i = 0; i < L->length; i ++) {
                printf("%d ", L->data[i]);
        }
        printf("\n");

        return;
}

void test() {
        SqList L;
        ElemType e;

        InitList(&L);
        printf("初始化后顺序表长度：%d\n", GetLength(&L));

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

        printf("%d元素的位置为：%d\n", 12, GetLocation(&L, 12));
        printf("%d元素的位置为：%d\n", 15, GetLocation(&L, 15));

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
