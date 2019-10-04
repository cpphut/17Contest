#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#define ll long long
#define MAX 1001
using namespace std;
int a[MAX][2], n, k, tot, f[MAX], ans = 1;
struct edge {
	double dis;
	int u, v;
}s[MAX * MAX];
bool cmp(edge x, edge y) {
	return x.dis < y.dis;
}
int getf(int x) {
	if (f[x] == x)
		return x;
	return f[x] = getf(f[x]);
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		scanf("%d%d", &a[i][0], &a[i][1]);
		for (int j = i - 1; j >= 1; j--) {
			tot++;
			s[tot].u = j;
			s[tot].v = i;
			s[tot].dis = sqrt((double)((a[i][0] - a[j][0]) * (a[i][0] - a[j][0]) + (a[i][1] - a[j][1]) * (a[i][1] - a[j][1])));
		}
	}
	sort(s + 1, s + 1 + tot, cmp);
	k = n - k;
	for (int i = 1; i <= k; i++) {
		while (getf(s[i].u) == getf(s[i].v))
			ans++;
		f[getf(s[i].v)] = getf(s[i].u);
		ans++;
	}
	printf("%.2lf", s[ans].dis);
	return 0;
}