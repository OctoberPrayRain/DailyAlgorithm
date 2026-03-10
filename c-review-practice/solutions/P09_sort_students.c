#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	char name[64];
	int score;
};

static int cmp_student(const void *lhs, const void *rhs)
{
	const struct student *a = lhs;
	const struct student *b = rhs;

	if (a->score != b->score)
		return b->score - a->score;
	return strcmp(a->name, b->name);
}

int main(void)
{
	int n;
	struct student st[1005];
	int i;

	if (scanf("%d", &n) != 1)
		return 0;
	if (n < 0 || n > 1000)
		return 0;

	for (i = 0; i < n; i++) {
		if (scanf("%63s%d", st[i].name, &st[i].score) != 2)
			return 0;
	}

	qsort(st, n, sizeof(st[0]), cmp_student);

	for (i = 0; i < n; i++)
		printf("%s %d\n", st[i].name, st[i].score);

	return 0;
}
