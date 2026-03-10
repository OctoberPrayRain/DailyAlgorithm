#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n;
	int i;
	long long sum = 0;
	int *arr;

	if (scanf("%d", &n) != 1)
		return 0;
	if (n <= 0)
		return 0;

	arr = malloc((size_t)n * sizeof(*arr));
	if (!arr)
		return 0;

	for (i = 0; i < n; i++) {
		if (scanf("%d", &arr[i]) != 1) {
			free(arr);
			return 0;
		}
		sum += arr[i];
	}

	printf("%.2f\n", (double)sum / n);
	free(arr);
	return 0;
}
