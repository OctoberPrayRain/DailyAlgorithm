# 单链表标准答案与解析

下面给出一个更规范的带头结点单链表实现，统一使用“位序从 1 开始”的规则，并补上初始化、判空、求长度、按位查找、按值查找、插入、删除、打印、销毁等常见教材要求。

## 标准代码

```c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkedList;

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
        length++;
        p = p->next;
    }

    return length;
}

bool GetElem(const LinkedList L, int i, ElemType *e) {
    if (L == NULL || i < 1 || i > ListLength(L)) {
        return false;
    }

    LinkedList p = L;
    int n = 0;

    while (n != i) {
        p = p->next;
        n++;
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
        locate++;
    }

    return p == NULL ? 0 : locate;
}

bool ListInsert(LinkedList L, int i, ElemType e) {
    if (L == NULL || i < 1 || i > ListLength(L) + 1) {
        return false;
    }

    int n = 0;
    while (n != i - 1) {
        L = L->next;
        n++;
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

bool ListDelete(LinkedList L, int i, ElemType *e) {
    if (L == NULL || i < 1 || i > ListLength(L)) {
        return false;
    }

    int n = 0;
    while (n != i - 1) {
        L = L->next;
        n++;
    }

    LinkedList p = L->next;
    *e = p->data;
    L->next = p->next;
    free(p);
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
    while (p != NULL) {
        LinkedList temp = p;
        p = p->next;
        free(temp);
    }

    *L = NULL;
}

int main(void) {
    LinkedList L = NULL;
    ElemType value;

    if (!InitList(&L)) {
        printf("InitList failed\n");
        return 1;
    }

    ListInsert(L, 1, 10);
    ListInsert(L, 2, 20);
    ListInsert(L, 2, 15);

    printf("当前链表: ");
    PrintList(L);

    if (GetElem(L, 2, &value)) {
        printf("第 2 个元素是: %d\n", value);
    }

    printf("元素 20 的位序是: %d\n", LocateElem(L, 20));

    if (ListDelete(L, 2, &value)) {
        printf("删除的元素是: %d\n", value);
    }

    printf("删除后的链表: ");
    PrintList(L);

    DestroyList(&L);
    return 0;
}
```

## 结构解析

`LNode` 是单链表的结点类型，核心有两个成员：

- `data`：存放数据元素
- `next`：指向下一个结点

`LinkedList` 本质上是 `LNode *`，也就是结点指针类型。

这份代码采用的是“带头结点单链表”：

- 头结点本身不存有效数据
- 真正的数据结点从 `L->next` 开始

这样做的好处是，插入和删除第一个元素时，逻辑更统一，不需要额外分类讨论。

## 关键函数解析

### 1. 初始化

```c
bool InitList(LinkedList *L)
```

初始化时要动态申请一个头结点，并让 `next = NULL`。

这里必须使用二级指针 `LinkedList *L`，因为函数内部需要修改调用者手里的头指针。

### 2. 判空

```c
bool ListEmpty(const LinkedList L)
```

如果：

- `L == NULL`
- 或者 `L->next == NULL`

都可以认为当前链表为空。

### 3. 求长度

```c
int ListLength(const LinkedList L)
```

从头结点开始往后走，只统计数据结点个数，不统计头结点本身。

### 4. 按位查找 `GetElem`

```c
bool GetElem(const LinkedList L, int i, ElemType *e)
```

这里的位序 `i` 从 1 开始：

- 第 1 个元素是第一个数据结点
- 第 2 个元素是第二个数据结点

查找前要先判断位置是否合法。合法后，从头结点出发走 `i` 步，就能到达第 `i` 个数据结点。

### 5. 按值查找 `LocateElem`

```c
int LocateElem(const LinkedList L, ElemType e)
```

从第一个数据结点开始顺序扫描：

- 找到第一个值等于 `e` 的结点，就返回其位序
- 如果扫到 `NULL` 还没找到，就返回 `0`

返回 `0` 的原因和顺序表一样，因为位序从 1 开始，所以 `0` 可以自然表示“查找失败”。

### 6. 插入 `ListInsert`

```c
bool ListInsert(LinkedList L, int i, ElemType e)
```

在带头结点单链表中，要在第 `i` 个位置插入元素，本质上是：

1. 先找到第 `i - 1` 个位置对应的前驱结点
2. 申请新结点
3. 改两次指针

核心代码是：

```c
p->next = L->next;
L->next = p;
```

这两句不能颠倒。先让新结点接上后面的链，再让前驱结点指向新结点。

### 7. 删除 `ListDelete`

```c
bool ListDelete(LinkedList L, int i, ElemType *e)
```

删除第 `i` 个元素时，也要先找到它的前驱结点，然后：

1. 用 `p` 暂存待删结点
2. 保存 `p->data`
3. 让前驱结点越过 `p`
4. 释放 `p`

核心代码：

```c
LinkedList p = L->next;
*e = p->data;
L->next = p->next;
free(p);
```

### 8. 打印与销毁

`PrintList` 从 `L->next` 开始遍历输出。  
`DestroyList` 则把整个链表包括头结点在内全部释放，并把头指针设为 `NULL`。

## 链表插入和删除示意

### 插入

例如原链表：

```text
头 -> 10 -> 20 -> NULL
```

在第 2 个位置插入 `15` 后：

```text
头 -> 10 -> 15 -> 20 -> NULL
```

### 删除

删除第 2 个元素后：

```text
头 -> 10 -> 20 -> NULL
```

## 这份标准答案比原代码更规范的地方

- 使用带头结点单链表，插入删除逻辑更统一
- 初始化使用二级指针，能真正修改头指针
- 对 `NULL` 链表和非法位序做了基本保护
- `LocateElem` 能正确处理“找不到元素”的情况
- 插入时检查了 `malloc` 是否成功
- 删除时返回被删元素，并释放对应结点
- 提供了 `PrintList` 和 `DestroyList`，便于测试和收尾

## 复杂度分析

- 初始化：`O(1)`
- 判空：`O(1)`
- 求长度：`O(n)`
- 按位查找：`O(n)`
- 按值查找：`O(n)`
- 插入：最坏 `O(n)`
- 删除：最坏 `O(n)`

单链表的特点是：

- 插入删除时不需要整体搬移元素
- 但不能像顺序表那样按下标随机访问

## 一句话记忆

单链表 = 非连续存储 + 插删方便 + 查找靠遍历。
