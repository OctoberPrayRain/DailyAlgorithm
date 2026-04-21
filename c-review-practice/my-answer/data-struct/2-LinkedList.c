#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

/* 带头结点的单链表
 * 头结点的 data 域存储链表长度（仅头结点有效）
 */
typedef struct LNode {
        ElemType data;
        struct LNode *next;
} LNode, *LinkedList;

bool InitList(LinkedList *L) {
        *L = (LNode *)malloc(sizeof(LNode));
        if (*L == NULL) {
                return false;
        }
        (*L)->data = 0;
        (*L)->next = NULL;
        return true;
}

bool IsEmpty(const LinkedList L) {
        return L == NULL || L->next == NULL;
}

int ListLength(const LinkedList L) {
        if (L == NULL) {
                return 0;
        }
        return L->data;
}

bool GetElem(const LinkedList L, int i, ElemType *e) {
        if (L == NULL || i < 1 || i > L->data) {
                return false;
        }
        LNode *p = L->next;
        for (int j = 1; j < i; j++) {
                p = p->next;
        }
        *e = p->data;
        return true;
}

int GetLocation(const LinkedList L, ElemType e) {
        if (L == NULL || L->data == 0) {
                return 0;    // 0 表示未找到
        }
        LNode *p = L->next;
        for (int i = 1; i <= L->data; i++) {
                if (p->data == e) {
                        return i;
                }
                p = p->next;
        }
        return 0;
}

bool InsertList(LinkedList *L, int i, ElemType e) {
        if (*L == NULL || i < 1 || i > (*L)->data + 1) {
                return false;
        }
        LNode *p = *L;
        for (int j = 1; j < i; j++) {
                p = p->next;
        }
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
                return false;
        }
        node->data = e;
        node->next = p->next;
        p->next = node;
        (*L)->data++;
        return true;
}

bool RemoveList(LinkedList *L, int i, ElemType *e) {
        if (*L == NULL || i < 1 || i > (*L)->data) {
                return false;
        }
        LNode *p = *L;
        for (int j = 1; j < i; j++) {
                p = p->next;
        }
        LNode *node = p->next;
        p->next = node->next;
        *e = node->data;
        free(node);
        (*L)->data--;
        return true;
}

void PrintList(const LinkedList L) {
        if (L == NULL || L->data == 0) {
                return;
        }
        LNode *p = L->next;
        for (int i = 1; i <= L->data; i++) {
                printf("%d ", p->data);
                p = p->next;
        }
        printf("\n");
}

bool DestroyList(LinkedList *L) {
        if (*L == NULL) {
                return true;
        }
        LNode *p = (*L)->next;
        while (p != NULL) {
                LNode *node = p;
                p = p->next;
                free(node);
        }
        free(*L);
        *L = NULL;
        return true;
}
