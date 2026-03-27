#include <stdio.h>

static long long factorial(unsigned int n) {
        if (n == 1) {
                return 1;
        }

        return n * factorial(n-1);
}

int main() {
        unsigned int n;

        if (!scanf("%d", &n)) {
                printf("\n输入错误！\n");
                return 0;
        }

        if (n < 1 || n > 20) {
                printf("Out of range!");
                return 0;
        }

        long result = factorial(n);
        printf("%ld", result);
        return 0;
}
