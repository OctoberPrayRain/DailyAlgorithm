# 顺序表标准答案与解析

下面给出一个更规范的顺序表实现，统一使用“位序从 1 开始”的规则，并补上越界判断、删除时返回被删元素等常见教材要求。

## 标准代码

```c
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 50

typedef int ElemType;

typedef struct {
    ElemType data[MAX_SIZE];
    int length;
} SqList;

void InitList(SqList *L) {
    L->length = 0;
}

bool ListEmpty(const SqList *L) {
    return L->length == 0;
}

int ListLength(const SqList *L) {
    return L->length;
}

bool GetElem(const SqList *L, int i, ElemType *e) {
    if (i < 1 || i > L->length) {
        return false;
    }

    *e = L->data[i - 1];
    return true;
}

int LocateElem(const SqList *L, ElemType e) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == e) {
            return i + 1;
        }
    }

    return 0;
}

bool ListInsert(SqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length + 1) {
        return false;
    }

    if (L->length >= MAX_SIZE) {
        return false;
    }

    for (int j = L->length; j >= i; j--) {
        L->data[j] = L->data[j - 1];
    }

    L->data[i - 1] = e;
    L->length++;
    return true;
}

bool ListDelete(SqList *L, int i, ElemType *e) {
    if (i < 1 || i > L->length) {
        return false;
    }

    *e = L->data[i - 1];

    for (int j = i; j < L->length; j++) {
        L->data[j - 1] = L->data[j];
    }

    L->length--;
    return true;
}

void PrintList(const SqList *L) {
    for (int i = 0; i < L->length; i++) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

int main(void) {
    SqList L;
    ElemType value;

    InitList(&L);

    ListInsert(&L, 1, 12);
    ListInsert(&L, 2, 13);
    ListInsert(&L, 3, 15);
    ListInsert(&L, 2, 4);
    ListInsert(&L, 2, 8);

    printf("当前顺序表: ");
    PrintList(&L);

    if (GetElem(&L, 3, &value)) {
        printf("第 3 个元素是: %d\n", value);
    }

    printf("元素 13 的位序是: %d\n", LocateElem(&L, 13));

    if (ListDelete(&L, 2, &value)) {
        printf("删除的元素是: %d\n", value);
    }

    printf("删除后的顺序表: ");
    PrintList(&L);

    return 0;
}
```

## 结构解析

`SqList` 是顺序表结构体，核心只有两个成员：

- `data[MAX_SIZE]`：静态数组，真正存放元素
- `length`：当前线性表中有效元素个数

这就是顺序表最典型的存储方式：用一段连续空间存数据，再单独记录当前长度。

## 关键函数解析

### 1. 初始化

```c
void InitList(SqList *L) {
    L->length = 0;
}
```

初始化的本质就是把表长设为 0，表示当前没有元素。

### 2. 按位查找 `GetElem`

```c
bool GetElem(const SqList *L, int i, ElemType *e)
```

这里有两个关键点：

- 位序 `i` 按教材习惯从 1 开始
- 查找前必须先判断 `i` 是否越界

如果合法，就把第 `i` 个元素放到 `*e` 里，并返回 `true`。

### 3. 按值查找 `LocateElem`

```c
int LocateElem(const SqList *L, ElemType e)
```

顺序扫描整个表，找到第一个值等于 `e` 的元素就返回它的位序。

- 找到：返回 `i + 1`
- 找不到：返回 `0`

返回 `0` 很常见，因为位序从 1 开始，所以 `0` 可以自然表示“查找失败”。

### 4. 插入 `ListInsert`

```c
bool ListInsert(SqList *L, int i, ElemType e)
```

插入前要检查两件事：

- 插入位置是否合法
- 顺序表是否已满

插入的核心思想是：从后往前移动元素，给新元素腾出位置。

例如在第 2 个位置插入元素：

```text
原表: 12 13 15
插入:    4
结果: 12 4 13 15
```

如果从前往后移动，会覆盖原数据，所以必须从后往前移动。

### 5. 删除 `ListDelete`

```c
bool ListDelete(SqList *L, int i, ElemType *e)
```

删除时先把被删元素保存到 `*e` 中，再把后面的元素依次左移。

例如删除第 2 个元素：

```text
原表: 12 4 13 15
结果: 12 13 15
```

删除完成后，表长减 1。

## 这份标准答案比原代码更规范的地方

- `#include`、宏名、结构体成员命名都更符合 C 的常见规范
- 所有“按位操作”统一用 1 基位序，接口风格一致
- `GetElem` 增加了越界判断，不会直接访问非法内存
- `LocateElem` 返回位序而不是数组下标，更符合教材习惯
- `ListDelete` 把被删元素通过参数带回，这是常见标准写法
- 数据结构函数只返回结果，不直接输出错误信息，接口更清晰
- `main` 用 `int main(void)`，更规范

## 复杂度分析

- 初始化：`O(1)`
- 判空：`O(1)`
- 求表长：`O(1)`
- 按位查找：`O(1)`
- 按值查找：`O(n)`
- 插入：最坏 `O(n)`
- 删除：最坏 `O(n)`

顺序表的特点就是：

- 查找指定位置快
- 中间插入、删除时需要移动元素，代价较高

## 一句话记忆

顺序表 = 连续存储 + 随机访问快 + 插删要移动元素。
