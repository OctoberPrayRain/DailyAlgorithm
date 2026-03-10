#include <stdio.h>

static int is_vowel(char c)
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return 1;
	if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
		return 1;
	return 0;
}

int main(void)
{
	char s[5005];
	int i;
	int count = 0;

	if (!fgets(s, sizeof(s), stdin))
		return 0;

	for (i = 0; s[i] != '\0'; i++) {
		if (is_vowel(s[i]))
			count++;
	}

	printf("%d\n", count);
	return 0;
}
