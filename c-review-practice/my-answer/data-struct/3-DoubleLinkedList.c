#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct DLNode {
        ElemType data;
        struct DLNode *prev;
        struct DLNode *next;
} DLNode, *DLinkedList;

bool InitList(DLinkedList *L) {
        *L = (DLNode *)malloc(sizeof(DLNode));

        if (*L == NULL) {
                return false;
        }

        (*L)->data = 0;
        (*L)->next = NULL;
        (*L)->prev = NULL;    // 对于双链表，记得 prev 这个指针域

        return true;
}

bool IsEmpty(const DLinkedList L) {
        return L == NULL || L->next == NULL;
}

int ListLength(const DLinkedList L) {
        if (L == NULL) {
                return 0;
        }

        return L->data;
}

bool GetElem(const DLinkedList L, int i, ElemType *e) {
        if (L == NULL || i < 1 || i > L->data) {
                return false;
        }


        // 这样做是安全的，因为当 i > L->data 的时候已经被拦截在上一个判断语句
        DLNode *p = L->next;

        for (int j = 1; j < i; j ++) {
                p = p->next;
        }

        *e = p->data;

        return true;
}

void PrintList(const DLinkedList L) {
        if (L == NULL || L->next == NULL) {
                printf("链表为空\n");
                return;
        }

        DLNode *p = L->next;
        for (int i = 1; i <= L->data; i ++) {
                printf("%d ", p->data);
                p = p->next;
        }


        printf("\n");

        return;
}

int GetLocation(const DLinkedList L, ElemType elem) {
        if (L == NULL) {
                return 0;    // 0代表没找到
        }

        DLNode *p = L;

        for (int i = 0; i < L->data; i ++) {
                p = p->next;

                if (p->data == elem) {
                        return i + 1;
                }
        }

        return 0;
}

bool ListInsert(DLinkedList *L, int i, ElemType e){
        if (*L == NULL || i < 1 || i > (*L)->data + 1) {
                return false;
        }

        DLNode *p = *L;
        DLNode *node = (DLNode *)malloc(sizeof(DLNode));
        if (node == NULL) {
                return false;
        }

        node->data = e;

        for (int j = 1; j < i; j ++) {
                p = p->next;
        }

        node->next = p->next;
        node->prev = p;
        if (p->next != NULL) {
                p->next->prev = node;
        }
        p->next = node;

        (*L)->data ++;

        return true;
}

bool RemoveList(DLinkedList *L, int i, ElemType *e) {
        if (*L == NULL || i < 1 || i > (*L)->data) {
                return false;
        }

        DLNode *p = *L;
        for (int j = 1; j < i; j ++) {
                p = p->next;
        }

        DLNode *node = p->next;
        p->next = node->next;
        if (p->next != NULL) {
                p->next->prev = p;
        }

        *e = node->data;
        free(node);

        (*L)->data --;

        return true;
}

bool DestroyList(DLinkedList *L) {
        if (*L == NULL) {
                return true;
        }

        DLNode *p = (*L)->next;

        for (int i = 1; i <= (*L)->data; i ++) {
                DLNode *node = p;
                p = p->next;
                free(node);
        }

        free(*L);
        *L = NULL;
        return true;
}

int main() {
        DLinkedList L;
        InitList(&L);

        // 测试插入（含空链表插入、尾插）
        ListInsert(&L, 1, 10);
        ListInsert(&L, 2, 20);
        ListInsert(&L, 3, 30);
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
        ListInsert(&L, 1, 5);
        printf("头插后: ");
        PrintList(L);                    // 5 10 30

        // 测试销毁
        DestroyList(&L);
        printf("销毁后 L == NULL: %s\n", L == NULL ? "是" : "否");

        return 0;
}
