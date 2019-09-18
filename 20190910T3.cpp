#include <cstdio>
#include <algorithm>
#define N 200001
#define X 1000001
#define ll long long
using namespace std;
int h[N], a[N], n, m, mh, l, r;
ll f[X];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &h[i], &a[i]);
		if (h[i] > mh)
			mh = h[i];
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		l = max(1, h[i] - m);
		r = min(h[i] + m, mh);
		ll* j = max_element(f + l, f + r + 1);
		f[h[i]] = *j + a[i];
		if (ans < f[h[i]]) {                                                  c                                                                                                                                                                                                                                                                                                                                12
			ans = f[h[i]];
		}
	}
	printf("%lld\n", ans);
	return 0;
}