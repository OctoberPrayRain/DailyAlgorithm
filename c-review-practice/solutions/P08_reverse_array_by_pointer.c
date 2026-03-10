#include <stdio.h>

int main(void)
{
	int n;
	int a[100005];
	int i;
	int *left;
	int *right;
	int tmp;

	if (scanf("%d", &n) != 1)
		return 0;
	if (n < 0 || n > 100000)
		return 0;

	for (i = 0; i < n; i++) {
		if (scanf("%d", &a[i]) != 1)
			return 0;
	}

	if (n <= 1) {
		if (n == 1)
			printf("%d\n", a[0]);
		else
			printf("\n");
		return 0;
	}

	left = &a[0];
	right = &a[n - 1];
	while (left < right) {
		tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}

	for (i = 0; i < n; i++) {
		if (i)
			printf(" ");
		printf("%d", a[i]);
	}
	printf("\n");
	return 0;
}
