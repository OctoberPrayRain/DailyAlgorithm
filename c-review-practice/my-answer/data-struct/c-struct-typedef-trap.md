# C 结构体 typedef 指针类型警告陷阱

## 现象

在单链表复习代码 `LinkedList-review.c` 中，编译器对 `p = p->next` 给出类型不兼容的警告；但在 `2-LinkedList.c` 中完全相同的代码却没有警告。

## 原因

问题出在结构体的定义方式不同。

### 有警告的写法（匿名结构体 + 前向声明）

```c
typedef struct {
        ElemType data;
        struct LNode *next;  // 这里只是对 struct LNode 的前向声明
} LNode, *LinkedList;
```

在这个写法里：
- `LNode` 是**匿名结构体**的别名。
- `struct LNode` 是另一个独立的、不完全的结构体类型（前向声明）。

对编译器来说，`LNode *` 和 `struct LNode *` 是**两种不同的指针类型**。因此当执行：

```c
LinkedList p = L;
p = p->next;  // p 是 LNode *，p->next 是 struct LNode *
```

编译器会发出类型不兼容的警告。

### 无警告的写法（有名结构体）

```c
typedef struct LNode {
        ElemType data;
        struct LNode *next;  // struct LNode 就是当前结构体本身
} LNode, *LinkedList;
```

在这个写法里：
- `struct LNode` 和 `LNode` 是**同一个结构体**的有名声明和 `typedef` 别名。
- 因此 `struct LNode *` 和 `LNode *` 完全等价，不会有任何警告。

## 修复方法

把匿名结构体改成有名结构体即可：

```c
// 修改前
typedef struct {
        ElemType data;
        struct LNode *next;
} LNode, *LinkedList;

// 修改后
typedef struct LNode {
        ElemType data;
        struct LNode *next;
} LNode, *LinkedList;
```

## 一句话总结

> `typedef struct { ... } LNode` 会让 `LNode` 和 `struct LNode` 变成两个不同的类型；只有 `typedef struct LNode { ... } LNode` 才能确保它们是同一个类型。
