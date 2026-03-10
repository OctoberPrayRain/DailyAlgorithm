#include <stdio.h>
#include <string.h>

static int is_vowel(char c)
{
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
	       c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int main(void)
{
	char s[200005];
	int k;
	int len;
	int i;
	int window = 0;
	int best = 0;

	if (scanf("%200000s", s) != 1)
		return 0;
	if (scanf("%d", &k) != 1)
		return 0;

	len = (int)strlen(s);
	if (k <= 0 || k > len)
		return 0;

	for (i = 0; i < k; i++)
		window += is_vowel(s[i]);
	best = window;

	for (i = k; i < len; i++) {
		window += is_vowel(s[i]);
		window -= is_vowel(s[i - k]);
		if (window > best)
			best = window;
	}

	printf("%d\n", best);
	return 0;
}
