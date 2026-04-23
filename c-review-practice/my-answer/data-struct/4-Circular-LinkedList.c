#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct CLNode {
        ElemType data;
        struct CLNode *next;
}CLNode, *CLinkedList;

bool InitList(CLinkedList *L) {
        *L = (CLNode *)malloc(sizeof(CLNode));
        if (*L == NULL) {
                return false;
        }    // 检查一下内存是否分配正确

        (*L)->data = 0;
        (*L)->next = *L;

        return true;
}

bool IsEmpty(const CLinkedList L) {
        return L == NULL || L->next == L;    // L->next == L 是边界条件
}

int ListLength(const CLinkedList L) {
        if (L == NULL) {
                return 0;
        }

        return L->data;
}

bool GetElem(const CLinkedList L, int i, ElemType *e) {
        if (L == NULL || i < 1 || i > L->data) {
                return false;
        }

        CLNode *p = L->next;
        for (int j = 1; j < i; j ++) {
                p = p->next;
        }

        *e = p->data;

        return true;
}

int GetLocation(const CLinkedList L, ElemType e) {
        if (L == NULL || L->next == L) {
                return 0;
        }

        CLNode *p = L->next;
        int i = 1;

        while (p->next != L) {
                if (p->data == e) {
                        return i;
                }

                p = p->next;
                i ++;
        }

        if (p->data == e) {
                return i;
        }

        return 0;
}

void PrintList(const CLinkedList L) {
        if (L == NULL || L->next == L) {
                printf("链表为空\n");
                return;
        }

        CLNode *p = L->next;
        while (p->next != L) {
                printf("%d ", p->data);
                p = p->next;
        }

        printf("%d\n", p->data);

        return;
}

bool InsertList(CLinkedList *L, int i, ElemType e) {
        if (*L == NULL || i < 1 || i > (*L)->data + 1) {
                return false;
        }

        CLNode *node = (CLNode *)malloc(sizeof(CLNode));
        if (node == NULL) {
                return false;
        }

        CLNode *p = *L;
        for (int j = 1; j < i; j ++) {
                p = p->next;
        }

        node->data = e;
        node->next = p->next;
        p->next = node;
        (*L)->data ++;

        return true;
}

bool RemoveList(CLinkedList *L, int i, ElemType *e) {
        if ((*L) == NULL || i < 1 || i > (*L)->data) {
                return false;
        }

        CLNode *p = *L;

        for (int j = 1; j < i; j ++) {
                p = p->next;
        }

        CLNode *node = p->next;
        p->next = p->next->next;
        *e = node->data;
        free(node);
        (*L)->data --;
        return true;
}

bool DestroyList(CLinkedList *L) {
        if (*L == NULL) {
                return true;
        }

        CLNode *p = (*L)->next;
        while (p != *L) {
                CLNode *node = p;
                p = p->next;
                free(node);
        }

        free(*L);
        *L = NULL;
        return true;
}

int main() {
        CLinkedList L;
        InitList(&L);

        // 测试空链表插入
        InsertList(&L, 1, 10);
        InsertList(&L, 2, 20);
        InsertList(&L, 3, 30);
        printf("插入后: ");
        PrintList(L);                    // 10 20 30

        // 测试按位查找
        ElemType e;
        GetElem(L, 2, &e);
        printf("第2个元素: %d\n", e);    // 20

        // 测试按值查找
        printf("30的位置: %d\n", GetLocation(L, 30));  // 3

        // 测试删除并获取被删元素
        RemoveList(&L, 2, &e);
        printf("删除的元素: %d\n", e);   // 20
        printf("删除后: ");
        PrintList(L);                    // 10 30

        // 测试头插
        InsertList(&L, 1, 5);
        printf("头插后: ");
        PrintList(L);                    // 5 10 30

        // 测试销毁
        DestroyList(&L);
        printf("销毁后 L == NULL: %s\n", L == NULL ? "是" : "否");

        return 0;
}
