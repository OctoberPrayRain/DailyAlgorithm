#include <stdio.h>

int main(void)
{
	int n;
	int i;
	long long x;
	long long min_val;
	long long max_val;

	if (scanf("%d", &n) != 1 || n <= 0)
		return 0;

	if (scanf("%lld", &x) != 1)
		return 0;

	min_val = x;
	max_val = x;

	for (i = 1; i < n; i++) {
		if (scanf("%lld", &x) != 1)
			return 0;
		if (x < min_val)
			min_val = x;
		if (x > max_val)
			max_val = x;
	}

	printf("%lld\n", max_val - min_val);
	return 0;
}
