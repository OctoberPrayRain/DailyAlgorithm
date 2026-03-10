#include <stdio.h>

static unsigned long long factorial(unsigned int n)
{
	if (n <= 1)
		return 1ULL;
	return n * factorial(n - 1);
}

int main(void)
{
	unsigned int n;

	if (scanf("%u", &n) != 1)
		return 0;

	if (n > 20U)
		return 0;

	printf("%llu\n", factorial(n));
	return 0;
}
