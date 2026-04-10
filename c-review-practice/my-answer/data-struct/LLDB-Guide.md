# LLDB 使用笔记

这份文档面向 C 初学者，目标不是把 `lldb` 所有功能讲全，而是帮你先学会最常用的调试流程。

适合你现在这种场景：

- 调试顺序表、链表、栈、队列
- 查空指针、越界、死循环
- 看变量、指针、函数调用过程

在 macOS 上，`lldb` 一般比 `gdb` 更稳定，也更适合直接调试 `clang/cc` 编译出来的程序。

## 1. 编译时加调试信息

调试时建议这样编译：

```bash
cc -g -O0 2-LinkedList.c -o linkedlist
```

参数说明：

- `-g`：加入调试信息
- `-O0`：关闭优化，避免调试时代码行和执行过程对不上

如果你是调当前项目里的文件，也可以这样：

```bash
cc -g -O0 my-answer/src/data-struct/2-LinkedList.c -o linkedlist
```

## 2. 启动 lldb

```bash
lldb ./linkedlist
```

进入后会看到 `(lldb)` 提示符，接下来就在里面输入命令。

## 3. 最小调试流程

你先只练这 6 个命令：

```lldb
breakpoint set --name main
run
next
step
print 变量名
quit
```

含义：

- `breakpoint set --name main`：在 `main` 函数入口打断点
- `run`：运行程序
- `next`：执行下一行，但不进入函数内部
- `step`：执行下一行，会进入函数内部
- `print 变量名`：打印变量值
- `quit`：退出 `lldb`

## 4. 最常用命令表

### 断点

```lldb
breakpoint set --name main
breakpoint set --name ListInsert
breakpoint set --line 74
breakpoint set --file 2-LinkedList.c --line 74
breakpoint list
breakpoint delete 1
breakpoint clear
```

说明：

- `breakpoint set --name main`：在 `main` 打断点
- `breakpoint set --name ListInsert`：在函数入口打断点
- `breakpoint set --line 74`：在当前文件第 74 行打断点
- `breakpoint set --file 2-LinkedList.c --line 74`：在指定文件指定行打断点
- `breakpoint list`：查看所有断点
- `breakpoint delete 1`：删除编号为 1 的断点
- `breakpoint clear`：清空所有断点

### 运行控制

```lldb
run
continue
next
step
finish
thread until 80
```

说明：

- `run`：开始运行
- `continue`：继续运行到下一个断点
- `next`：下一行，不进入函数
- `step`：下一行，进入函数
- `finish`：直接运行到当前函数返回
- `thread until 80`：运行到第 80 行，适合跳过循环或中间过程

### 查看代码和位置

```lldb
list
list 40
frame info
bt
```

说明：

- `list`：查看当前位置附近代码
- `list 40`：查看第 40 行附近代码
- `frame info`：看当前栈帧信息
- `bt`：查看函数调用栈，程序崩溃时非常重要

### 查看变量

```lldb
print i
print e
print L
print *L
print L->next
print *(L->next)
frame variable
frame variable p
```

说明：

- `print x`：打印变量
- `print *p`：打印指针 `p` 指向的内容
- `print L->next`：看链表指针
- `frame variable`：查看当前函数里的局部变量
- `frame variable p`：查看变量 `p`

## 5. 调试链表时怎么用

链表最容易出问题的地方：

- `L` 是不是 `NULL`
- `L->next` 是不是 `NULL`
- 插入前后 `next` 是否连对
- 遍历时指针有没有更新
- 删除时有没有断链或释放错结点

### 例子：调试 `ListInsert`

先编译：

```bash
cc -g -O0 my-answer/src/data-struct/2-LinkedList.c -o linkedlist
lldb ./linkedlist
```

在 `lldb` 里输入：

```lldb
breakpoint set --name ListInsert
run
print i
print e
print L
print *L
next
next
step
```

你可以重点观察：

- 插入位置 `i` 是否正确
- 当前结点 `L` 是不是前驱结点
- 新结点 `p` 是否申请成功
- `p->next = L->next` 和 `L->next = p` 后，链是否接对

### 例子：看链表某个结点

```lldb
print p
print *p
print p->data
print p->next
```

如果 `p == 0x0`，说明它已经是空指针了。

## 6. 程序崩溃时怎么查

如果程序段错误，不要慌，第一反应就是：

```lldb
run
bt
```

`bt` 会告诉你：

- 崩在哪个函数
- 崩在哪一行
- 谁调用了它

然后继续查当前变量：

```lldb
frame select 0
list
print p
print L
print i
```

很大一部分 bug 都能这样直接定位。

## 7. 调试顺序表时怎么用

顺序表最常见的问题：

- `i` 和 `i - 1` 写错
- 插入时搬移边界错
- 删除时循环越界
- `length` 更新时机不对

### 例子：调试 `ListDelete`

```lldb
breakpoint set --name ListDelete
run
print i
print L->length
next
print *e
next
next
```

重点看：

- 删除前 `i` 是否合法
- 被删元素是不是 `data[i - 1]`
- 循环结束后数组内容是否正确
- `length` 是否减一

## 8. 推荐你现在就练的命令组合

如果你只想先练到能用，记住下面这组就够了：

```lldb
breakpoint set --name main
run
next
step
print 变量名
bt
continue
quit
```

这套已经能解决大部分初学阶段的问题。

## 9. 一个完整练习

假设你要调当前的链表代码：

```bash
cc -g -O0 my-answer/src/data-struct/2-LinkedList.c -o linkedlist
lldb ./linkedlist
```

进入 `lldb` 后：

```lldb
breakpoint set --name main
run
next
next
next
step
breakpoint set --name ListInsert
continue
print i
print e
print L
print *L
next
next
continue
quit
```

你不需要一次记住全部命令，先能跟着这套流程走就够了。

## 10. 学习建议

不要一边写代码一边完全靠眼睛猜 bug。你现在学数据结构，最值钱的习惯是：

1. 先自己写
2. 出问题后用 `lldb` 定位
3. 把 bug 记成“边界条件错误”还是“指针错误”
4. 下次写类似函数前先检查一次

这样进步会很快。

## 11. 常见报错理解

### `Segmentation fault`

通常是：

- 空指针解引用
- 野指针
- 数组越界

先用：

```lldb
run
bt
print 相关指针
```

### 变量值看起来不对

通常检查：

- 下标是不是错了一位
- 循环是否多走或少走一次
- 修改变量前后有没有重新赋值

## 12. 你接下来可以怎么练

建议你用下面顺序练习：

1. 调顺序表 `GetElem`
2. 调顺序表 `ListDelete`
3. 调链表 `ListInsert`
4. 调链表 `PrintList`
5. 调你以后写的 `ListDelete`

这几类都是最典型的调试场景。

## 13. 一句话总结

你现阶段学 `lldb`，核心不是背命令，而是养成下面这个习惯：

```text
出错 -> 打断点 -> 单步执行 -> 看变量 -> 找到具体哪一行开始不对
```

只要这个流程熟了，后面学数据结构会轻松很多。
