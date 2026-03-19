#include <stdbool.h>
#include <stdio.h>
#define MaxSize 50

typedef int ElemType;

typedef struct {
  ElemType data[MaxSize];
  int Length;
} SqList;

void InitList(SqList *L) {
  L->Length = 0;
  return;
}

bool ListEmpty(SqList *L) {
  return L->Length == 0;
}

int GetLength(SqList *L) {
  return L->Length;
}

bool ListInsert(SqList *L, int i, ElemType e) {

  // 如果 i 大于 Length+1 或者 i 小于 1，超出索引范围，直接返回 false
  if (i > (L->Length+1) || i < 1) {
    printf("\nOut of indexing!\n");
    return false;
  }

  // 如果顺序表已经满了
  if (L -> Length == MaxSize) {
    printf("\nList is full!\n");
    return false;
  }

  // 先移动半个数组
  for (int j = L->Length; j >= i; j--) {
    L->data[j] = L->data[j-1];
  }

  L->data[i-1] = e;
  // 数组长度+1
  L->Length ++;

  return true;
}

bool ListDelete(SqList *L, int i) {

  if (i < 1 || i > L->Length) {
    printf("\nOut of indexing!\n");
    return false;
  }

  for (int j = i-1; j < L->Length-1; j++) {
    L->data[j] = L->data[j+1];
  }
  L->Length --;
  return true;
}

int LocateElem(SqList *L, ElemType e) {
  for (int i = 0; i < L->Length; i ++) {
    if (L->data[i] == e) {
      return i;
    }
  }

  // -1表示没查到
  return -1;
}

ElemType GetElem(SqList *L, int i) {
  return L->data[i - 1];
}

void PrintList(SqList *L) {
  for (int i = 0; i < L->Length; i++) {
    printf("%d ", L->data[i]);
  }
  return;
}

int main() {
  SqList L;
  InitList(&L);
  ListInsert(&L, 1, 12);
  ListInsert(&L, 2, 13);
  ListInsert(&L, 3, 15);
  ListInsert(&L, 2, 4);
  ListInsert(&L, 2, 4);
  ListInsert(&L, 49, 1);
  PrintList(&L);
}

