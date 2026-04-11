# C 语言输入函数总结

这份笔记用于整理 C 语言里常见的输入函数，重点放在：

- 它们从哪里读取数据
- 适合什么场景
- 基本用法怎么写
- 常见坑有哪些

---

## 1. 总览

| 函数 | 读取来源 | 典型用途 | 是否常用 |
| --- | --- | --- | --- |
| `scanf` | 标准输入 `stdin` | 按格式读数字、字符、单词 | 很常用 |
| `fscanf` | 文件流 | 从文件按格式读取 | 常用 |
| `sscanf` | 字符串 | 从一行文本中按格式解析数据 | 很常用 |
| `fgets` | 文件流或 `stdin` | 读取一整行文本 | 很常用 |
| `getchar` | 标准输入 `stdin` | 逐字符读取 | 常用 |
| `fgetc` | 文件流 | 从文件或标准输入逐字符读取 | 常用 |
| `fread` | 文件流 | 读取二进制数据块 | 特定场景常用 |
| `gets` | 标准输入 `stdin` | 已废弃，不应使用 | 不要用 |

---

## 2. 格式化输入函数

这类函数的特点是：根据格式控制字符串解析输入内容。

### 2.1 `scanf`

作用：
- 从标准输入读取数据
- 适合规则明确的输入，比如整数、浮点数、空白分隔的字符串

基本写法：

```c
int a;
scanf("%d", &a);
```

读取多个值：

```c
int a, b;
scanf("%d %d", &a, &b);
```

读取浮点数：

```c
float x;
scanf("%f", &x);
```

读取字符串：

```c
char s[10];
scanf("%9s", s);
```

注意点：
- 读取数值时必须传地址，如 `&a`
- `%s` 遇到空格、制表符、换行就停止
- `%s` 要限制最大宽度，避免数组越界
- `scanf` 对格式要求严格，输入不符合预期时容易出问题
- 它会跳过前导空白字符，但 `%c` 是例外

`%c` 的坑：

```c
char ch;
scanf("%c", &ch);
```

如果前面刚输入过数字，缓冲区里可能还留着换行，这时 `%c` 可能直接读到 `'\n'`。

更稳妥的写法：

```c
char ch;
scanf(" %c", &ch);
```

前面的空格表示先跳过空白字符。

适用场景：
- 刷题
- 输入格式稳定且简单
- 只需要快速读出数字或单词

---

### 2.2 `fscanf`

作用：
- 从指定文件流按格式读取数据

示例：

```c
FILE *fp = fopen("data.txt", "r");
int x;

fscanf(fp, "%d", &x);
fclose(fp);
```

适用场景：
- 从文件中读取结构化文本
- 用法和 `scanf` 很接近，只是数据来源不是键盘，而是文件

---

### 2.3 `sscanf`

作用：
- 从字符串中按格式解析数据

示例：

```c
char buf[] = "123 45.6";
int a;
float b;

sscanf(buf, "%d %f", &a, &b);
```

适用场景：
- 先用 `fgets` 读一整行
- 再从这一行里提取整数、浮点数、单词等内容

这是实际开发里很常见的组合：

```c
char buf[100];
int a, b;

fgets(buf, sizeof(buf), stdin);
sscanf(buf, "%d %d", &a, &b);
```

优点：
- 不直接依赖标准输入
- 更容易控制错误处理
- 适合“先读取，再解析”的写法

---

## 3. 按行读取函数

### `fgets`

作用：
- 从文件流中读取一整行文本
- 常用于从标准输入读取一整行

基本写法：

```c
char buf[100];
fgets(buf, sizeof(buf), stdin);
```

特点：
- 最多读取 `sizeof(buf) - 1` 个字符
- 会自动在末尾补 `'\0'`
- 如果读到了换行符，换行符通常会保留下来

示例：

```c
char buf[100];
fgets(buf, sizeof(buf), stdin);
printf("%s", buf);
```

如果想去掉结尾换行：

```c
buf[strcspn(buf, "\n")] = '\0';
```

这通常需要包含头文件：

```c
#include <string.h>
```

适用场景：
- 读取带空格的一整行文本
- 用户输入的内容长度需要限制
- 想先读取原始文本，再自己解析

优点：
- 比 `gets` 安全
- 比直接用 `scanf("%s")` 更适合读整行
- 适合做健壮输入处理

注意点：
- 读完后可能带换行
- 如果输入行太长，当前缓冲区只能读到其中一部分

---

## 4. 单字符输入函数

### 4.1 `getchar`

作用：
- 从标准输入读取一个字符

示例：

```c
int ch = getchar();
```

为什么建议用 `int` 接收：
- 因为它除了返回普通字符，还可能返回 `EOF`

逐字符读取示例：

```c
int ch;
while ((ch = getchar()) != '\n' && ch != EOF) {
    putchar(ch);
}
```

适用场景：
- 菜单输入
- 跳过字符
- 自己逐字符处理字符串

---

### 4.2 `fgetc`

作用：
- 从指定文件流读取一个字符

示例：

```c
int ch = fgetc(stdin);
```

从文件读取：

```c
FILE *fp = fopen("data.txt", "r");
int ch;

while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
}

fclose(fp);
```

适用场景：
- 从文件逐字符读取
- 写字符级别的解析逻辑

---

## 5. 二进制输入函数

### `fread`

作用：
- 按字节块读取数据
- 常用于二进制文件，而不是普通文本输入

基本写法：

```c
int arr[10];
fread(arr, sizeof(int), 10, fp);
```

含义：
- 从文件流 `fp` 读取 10 个 `int`
- 每个元素大小是 `sizeof(int)`

适用场景：
- 读取二进制数组
- 读取结构体
- 读取图像、音频、序列化数据等

注意点：
- 不适合直接拿来做普通键盘文本交互
- 返回值表示成功读取的元素个数，最好检查

示例：

```c
size_t n = fread(arr, sizeof(int), 10, fp);
```

---

## 6. 不要使用的函数

### `gets`

这个函数已经废弃，不应该再使用。

原因：
- 不检查缓冲区大小
- 很容易造成缓冲区溢出
- 在现代 C 标准中已经被移除

错误示意：

```c
char buf[10];
gets(buf);
```

替代方案：
- 用 `fgets`

---

## 7. 更稳妥的数字输入方式

如果只是简单刷题，`scanf` 很方便。

但如果你想更稳妥地处理用户输入，推荐：

- `fgets` 读取一整行
- `strtol` / `strtod` 解析数字

示例：

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char buf[100];
    char *end;
    long x;

    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 1;

    x = strtol(buf, &end, 10);
    printf("%ld\n", x);
    return 0;
}
```

优点：
- 先拿到完整输入
- 更容易检查非法字符
- 错误处理更清晰

适合场景：
- 交互式程序
- 需要严格判断输入是否合法
- 不希望 `scanf` 因异常输入导致流程混乱

---

## 8. 常见搭配

### 8.1 `fgets + sscanf`

先读取一整行，再按格式提取内容。

```c
char buf[100];
int a, b;

if (fgets(buf, sizeof(buf), stdin) != NULL) {
    if (sscanf(buf, "%d %d", &a, &b) == 2) {
        printf("%d %d\n", a, b);
    }
}
```

适合：
- 一行中有多个字段
- 想保留原始输入
- 想自己控制解析成功或失败

### 8.2 `fgets + strtol`

```c
char buf[100];
char *end;
long value;

if (fgets(buf, sizeof(buf), stdin) != NULL) {
    value = strtol(buf, &end, 10);
}
```

适合：
- 专门解析整数
- 需要做更细的合法性判断

---

## 9. 常见坑总结

### 9.1 `scanf` 读完数字后，换行还留在缓冲区

例如：

```c
int n;
char ch;

scanf("%d", &n);
scanf("%c", &ch);
```

这里第二个 `scanf("%c", &ch)` 很可能读到上一次输入后留下的换行。

解决方式：

```c
scanf(" %c", &ch);
```

或者直接改成按行读取。

### 9.2 `scanf("%s", s)` 不能读取带空格的句子

例如输入：

```text
hello world
```

`%s` 只能读到 `hello`。

如果要读整句，应该使用：

```c
fgets(buf, sizeof(buf), stdin);
```

### 9.3 `fgets` 会保留换行符

输入：

```text
abc
```

读到的字符串可能实际上是：

```text
"abc\n"
```

所以经常需要手动去掉换行。

### 9.4 `gets` 不安全

结论很简单：

- 不要再使用 `gets`

---

## 10. 怎么选

可以按下面这个思路快速选择：

- 只想快速读整数、浮点数、单词：`scanf`
- 要读一整行文本：`fgets`
- 要从一行字符串中再提取字段：`sscanf`
- 要逐字符处理：`getchar` / `fgetc`
- 要从文件按格式读取：`fscanf`
- 要处理二进制文件：`fread`
- 要做更稳妥的数字输入：`fgets + strtol`

---

## 11. 复习建议

建议你把这部分记成下面几条：

1. 刷题时最常用的是 `scanf`
2. 读整行时优先想到 `fgets`
3. 解析字符串时优先想到 `sscanf`
4. 需要安全处理数字输入时优先想到 `strtol`
5. `gets` 已废弃，不能使用

---

## 12. 一句话总结

`scanf` 适合规则输入，`fgets` 适合整行输入，`sscanf` 适合从字符串中解析，`getchar` 适合逐字符处理，`fread` 适合二进制输入，而 `gets` 不应该使用。
