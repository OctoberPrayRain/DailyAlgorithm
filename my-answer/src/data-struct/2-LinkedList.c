#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct LNode {
        ElemType data;
        struct LNode* next;
} LNode, *LinkedList;    // LinkedList 等价于 LNode*

bool InitList(LinkedList *L) {
        *L = (LNode *)malloc(sizeof(LNode));
        if (*L == NULL) {
                return false;
        }
        (*L)->next = NULL;
        return true;
}

bool ListEmpty(const LinkedList L) {
        return L == NULL || L->next == NULL;
}

int ListLength(const LinkedList L) {
        int length = 0;
        LinkedList p = L;

        if (p == NULL) {
                return 0;
        }
        
        while (p->next != NULL) {
                length ++;
                p = p->next;
        }

        return length;
}

bool GetElem(const LinkedList L, int i, ElemType *e) {
        if (i < 1 || L == NULL || i > ListLength(L)) {
                return false;
        }

        LinkedList p = L;
        int n = 0;

        while (n != i) {
                p = p->next;
                n ++;
        }

        *e = p->data;
        return true;
}

int LocateElem(const LinkedList L, ElemType e) {
        if (L == NULL || L->next == NULL) {
                return 0;
        }

        LinkedList p = L->next;
        int locate = 1;

        while (p != NULL && p->data != e) {
                p = p->next;
                locate ++;
        }

        return p == NULL ? 0 : locate;
}

bool ListInsert(LinkedList L, int i, ElemType e) {
        if (i < 1 || L == NULL || i > ListLength(L) + 1) {
                return false;
        }

        int n = 0;

        while (n != i-1) {
                L = L->next;
                n ++;
        }

        LinkedList p = (LNode *)malloc(sizeof(LNode));

        if (p == NULL) {
                return false;
        }
        
        p->data = e;
        p->next = L->next;
        L->next = p;
        return true;
}


void PrintList(const LinkedList L) {
        if (L == NULL) {
                printf("链表头结点为空\n");
                return;
        }
        
        LinkedList p = L->next;

        while (p != NULL) {
                printf("%d ", p->data);
                p = p->next;
        }

        printf("\n");

}

void DestroyList(LinkedList *L) {
        if (*L == NULL) {
                return;
        }
        
        LinkedList p = *L;

        while(p != NULL) {
                LinkedList temp = p;
                p = p -> next;
                free(temp);
        }

        *L = NULL;
}

