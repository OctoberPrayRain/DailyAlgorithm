#include <stdio.h>
#include <stdlib.h>

int main() {
        char s[2005];
        int count = 0;
        int i;

        if (!fgets(s, sizeof(s), stdin)) {
                return 0;
        }

        for (i = 0; s[i] != '\0'; i ++) {
                if (s[i] >= '0' && s[i] <= 9) {
                        count ++;
                }
        }

        printf("%d\n", count);
        return 0;
}
