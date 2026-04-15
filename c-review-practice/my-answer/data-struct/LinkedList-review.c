#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkedList;

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
	if (L == NULL || L->data == 0) {
		return true;
	}

	return false;
}

int ListLength(const LinkedList L) {
	if (L == NULL) {
		return 0;
	}

	return L->data;
}

bool GetElem(const LinkedList L, const int i, ElemType *e) {
	if (i < 1 || L == NULL || i > L->data) {
		return false;
	}

	LinkedList p = L;

	for (int j = 0; j < i; j ++) {
		p = p->next;
	}

	*e = p->data;

	return true;
}

int GetLocation(const LinkedList L, const ElemType e) {
	if (L == NULL || L->data == 0) {
		return 0;
	}

	LinkedList p = L->next;

	for (int i = 1; i <= L->data; i ++) {
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

	LinkedList node = (LNode *)malloc(sizeof(LNode));

	if (node == NULL) {
		return false;
	}

	node->data = e;

	LinkedList p = *L;

	for (int j = 0; j < i - 1; j ++) {
		p = p->next;
	}

	node->next = p->next;
	p->next = node;

	(*L)->data ++;

	return true;
}

bool RemoveList(LinkedList *L, const int i, ElemType *e) {
	if (i < 1 || *L == NULL || i > (*L)->data) {
		return false;
	}

	LinkedList p = *L;

	for (int j = 0; j < i - 1; j ++) {
		p = p->next;
	}

	LinkedList node = p->next;
	*e = node->data;
	p->next = node->next;
	free(node);

	(*L)->data --;
	return true;
}

void PrintList(const LinkedList L) {
	if (L == NULL || L->data == 0) {
		return;
	}

	LinkedList p = L->next;

	for (int i = 0; i < L->data; i ++) {
		printf("%d ", p->data);
		p = p->next;
	}

	printf("\n");
}

bool DestroyList(LinkedList *L) {
	if (L == NULL || *L == NULL) {
		return true;
	}

	LinkedList p = (*L)->next;
	while (p != NULL) {
		LinkedList node = p;
		p = p->next;
		free(node);
	}

	free(*L);
	*L = NULL;
	return true;
}

void test() {
	ElemType elem;
	LinkedList list;

	InitList(&list);

	printf("当前链表长度为: %d\n", ListLength(list));

	InsertList(&list, 1, 12);
	InsertList(&list, 1, 11);
	InsertList(&list, 3, 13);

	printf("LinkedList: ");
	PrintList(list);

	printf("此时链表长度为: %d\n", ListLength(list));

	RemoveList(&list, 2, &elem);
	printf("LinkedList: ");
	PrintList(list);
	printf("此时链表长度为：%d\n", ListLength(list));

	DestroyList(&list);
}


int main() {
	test();
	return 0;
}
