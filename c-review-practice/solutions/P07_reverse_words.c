#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[5005];
	int left;
	int right;
	char tmp;
	int len;

	if (!fgets(s, sizeof(s), stdin))
		return 0;

	len = (int)strlen(s);
	if (len > 0 && s[len - 1] == '\n') {
		s[len - 1] = '\0';
		len--;
	}

	left = 0;
	right = len - 1;
	while (left < right) {
		tmp = s[left];
		s[left] = s[right];
		s[right] = tmp;
		left++;
		right--;
	}

	printf("%s\n", s);
	return 0;
}
