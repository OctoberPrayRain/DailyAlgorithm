#include <stdio.h>

int main(void)
{
	unsigned int x;
	int count = 0;

	if (scanf("%u", &x) != 1)
		return 0;

	while (x) {
		x &= (x - 1);
		count++;
	}

	printf("%d\n", count);
	return 0;
}
