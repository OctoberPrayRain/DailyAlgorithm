#include <stdio.h>

int main(void)
{
	long long a;
	long long b;

	if (scanf("%lld%lld", &a, &b) != 2)
		return 0;

	printf("%lld\n", a + b);
	return 0;
}
