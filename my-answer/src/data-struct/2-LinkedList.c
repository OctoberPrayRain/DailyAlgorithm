#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct LNode {
        ElemType data;
        struct LNode *next;
} LNode, * LinkedList;

bool InitList(LinkedList *L) {
        *L = (LNode *)malloc(sizeof(LNode));
        if (*L == NULL) {
                return false;
        }
        (*L)->next = NULL;
        return true;
}

bool IsEmpty(const LinkedList L) {
        if (L == NULL || L->next == NULL) {
                return true;
        }

        return false;
}

int ListLength(const LinkedList L) {
        if (L == NULL) {
                return 0;
        }

        int i = 0;
        LinkedList p = L;
        
        while (p->next != NULL) {
                i ++;
                p = p->next;
        }

        return i;
}

bool GetElem(const LinkedList L, const int i, ElemType *e) {
        if (L == NULL || i < 1 || i > ListLength(L)) {
                return false;
        }

        LinkedList p = L;
        for (int j = 0; j < i; j ++) {
                p = p->next;
        }

        *e = p->data;
        return true;
}

int GetLocate(const LinkedList L, const ElemType e) {
        if (L == NULL || L->next == NULL) {
                return 0;
        }

        LinkedList p = L->next;
        int i = 1;

        while (p != NULL) {
                if (p->data == e) {
                        return i;
                }
                p = p->next;
                i ++;
        }

        return 0;
}

bool InsertList(LinkedList *L, const int i, const ElemType e) {
        if (*L == NULL || i < 1 || i > ListLength(*L) + 1) {
                return false;
        }

        LinkedList node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
                return false;
        }

        node->data = e;

        LinkedList p = *L;
        int j = 0;

        while (j != i - 1) {
                p = p->next;
                j ++;
        }

        node->next = p->next;
        p->next = node;
        return true;
}

bool RemoveList(LinkedList *L, const int i, ElemType *e) {
        if ((*L) == NULL || (*L)->next == NULL || i < 1 || i > ListLength(*L)) {
                return false;
        }

        LinkedList p = *L;
        int j = 0;
        while (j != i - 1) {
                j ++;
                p = p->next;
        }

        LinkedList node = p->next;
        p->next = p->next->next;

        *e = node->data;
        free(node);

        return true;
}

void PrintList(const LinkedList L) {
        if (L == NULL || L->next == NULL) {
                return;
        }

        LinkedList p = L->next;

        while (p != NULL) {
                printf("%d ", p->data);
                p = p->next;
        }

        printf("\n");
        return;
}

void DestroyList(LinkedList *L) {
        if (*L == NULL) {
                return;
        }

        if ((*L)->next == NULL) {
                free(*L);
                *L = NULL;
                return;
        }

        LinkedList p = (*L)->next, node = NULL;
        while (p->next != NULL) {
                node = p;
                p = p->next;
                free(node);
        }

        free(p);
        free(*L);
        *L = NULL;
        return;
}
