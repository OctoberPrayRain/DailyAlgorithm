#include <stdio.h>

int main(void)
{
	int n;
	int q;
	long long a[200005];
	long long prefix[200005];
	int i;

	if (scanf("%d%d", &n, &q) != 2)
		return 0;
	if (n <= 0 || n > 200000)
		return 0;

	for (i = 0; i < n; i++) {
		if (scanf("%lld", &a[i]) != 1)
			return 0;
	}

	prefix[0] = 0;
	for (i = 1; i <= n; i++)
		prefix[i] = prefix[i - 1] + a[i - 1];

	for (i = 0; i < q; i++) {
		int l;
		int r;
		long long ans;

		if (scanf("%d%d", &l, &r) != 2)
			return 0;
		if (l < 0 || r >= n || l > r)
			return 0;

		ans = prefix[r + 1] - prefix[l];
		printf("%lld\n", ans);
	}

	return 0;
}
