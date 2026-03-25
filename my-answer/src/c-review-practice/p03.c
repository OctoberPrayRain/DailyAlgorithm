#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
        if (n < 1 || n > 20) {
                printf("Out of range!");
                return 0;
        }

        if (n == 1) {
                return 1;
        }

        if (n == 2) {
                return 2;
        }

        return n * factorial(n-1);
}

int main() {
        int n;

        if (!scanf("%d", &n)) {
                return 1;
        }

        long result = factorial(n);
        printf("%ld", result);
}
