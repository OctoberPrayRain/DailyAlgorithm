#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef struct Node {
	ElemType data;
	int next;
} Node;

typedef struct StaticList {
	Node nodes[MAX_SIZE];
	int head;
	int free;
} StaticList;

void InitList(StaticList *L) {
	L->head = -1;
	L->free = 0;

	for (int i = 0; i < MAX_SIZE - 1; i++) {
		L->nodes[i].next = i + 1;
	}

	L->nodes[MAX_SIZE - 1].next = -1;
}

int MallocNode(StaticList *L) {
	if (L->free == -1) {
		return -1;
	}

	int index = L->free;
	L->free = L->nodes[index].next;
	return index;
}

void FreeNode(StaticList *L, int index) {
	if (index < 0 || index >= MAX_SIZE) {
		return;
	}
	L->nodes[index].next = L->free;
	L->free = index;
}

bool ListEmpty(const StaticList *L) {
	return L->head == -1;
}

int ListLength(const StaticList *L) {
	int count = 0;
	int current = L->head;

	while (current != -1) {
		count++;
		current = L->nodes[current].next;
	}

	return count;
}

bool GetElem(const StaticList *L, int i, ElemType *e) {
	if (i < 1 || ListEmpty(L)) {
		return false;
	}

	int current = L->head;
	int count = 1;

	while (current != -1 && count < i) {
		current = L->nodes[current].next;
		count++;
	}

	if (current == -1) {
		return false;
	}

	*e = L->nodes[current].data;
	return true;
}

int LocateElem(const StaticList *L, ElemType e) {
	int current = L->head;
	int count = 1;

	while (current != -1) {
		if (L->nodes[current].data == e) {
			return count;
		}
		current = L->nodes[current].next;
		count++;
	}

	return -1;
}

bool ListInsert(StaticList *L, int i, ElemType e) {
	if (i < 1 || i > ListLength(L) + 1) {
		return false;
	}

	int index = MallocNode(L);
	if (index == -1) {
		return false;
	}

	L->nodes[index].data = e;

	if (i == 1) {
		L->nodes[index].next = L->head;
		L->head = index;
		return true;
	}

	int current = L->head;
	int count = 1;

	while (count < i - 1) {
		current = L->nodes[current].next;
		count++;
	}

	L->nodes[index].next = L->nodes[current].next;
	L->nodes[current].next = index;
	return true;
}

bool ListDelete(StaticList *L, int i, ElemType *e) {
	if (i < 1 || ListEmpty(L)) {
		return false;
	}

	if (i == 1) {
		int del = L->head;
		*e = L->nodes[del].data;
		L->head = L->nodes[del].next;
		FreeNode(L, del);
		return true;
	}

	int current = L->head;
	int count = 1;

	while (current != -1 && count < i - 1) {
		current = L->nodes[current].next;
		count++;
	}

	if (current == -1 || L->nodes[current].next == -1) {
		return false;
	}

	int del = L->nodes[current].next;
	*e = L->nodes[del].data;
	L->nodes[current].next = L->nodes[del].next;
	FreeNode(L, del);
	return true;
}

void PrintList(const StaticList *L) {
	int current = L->head;

	while (current != -1) {
		printf("%d ", L->nodes[current].data);
		current = L->nodes[current].next;
	}

	printf("\n");
}

int main() {
	StaticList list;
	InitList(&list);

	// 测试插入
	ListInsert(&list, 1, 10);
	ListInsert(&list, 1, 20);
	ListInsert(&list, 2, 30);
	ListInsert(&list, 4, 40);

	printf("链表内容: ");
	PrintList(&list);
	printf("长度: %d\n", ListLength(&list));
	printf("是否为空: %s\n", ListEmpty(&list) ? "是" : "否");

	// 测试查找
	int pos = LocateElem(&list, 30);
	printf("30 的位置: %d\n", pos);

	ElemType e;
	if (GetElem(&list, 3, &e)) {
		printf("第 3 个元素: %d\n", e);
	}

	// 测试删除
	if (ListDelete(&list, 2, &e)) {
		printf("删除第 2 个元素: %d\n", e);
	}
	printf("删除后: ");
	PrintList(&list);

	if (ListDelete(&list, 1, &e)) {
		printf("删除第 1 个元素: %d\n", e);
	}
	printf("删除后: ");
	PrintList(&list);

	return 0;
}
