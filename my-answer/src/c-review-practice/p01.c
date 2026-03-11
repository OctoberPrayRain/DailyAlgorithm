#include <stdio.h>

int main() {
    // 这一道题 long 已经足够，不需要使用 long long 类型
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld", a + b);
    return 0;
}