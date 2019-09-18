#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
#define N 1000001
using namespace std;
int n, d[N], f[N], k, Q;
deque <int> q;
bool judge(int x, int y) {
	if (x < y - k)
		return true;
	if (f[y] < f[x])
		return true;
	if (f[y] == f[x] && d[y] >= d[x])
		return true;
	return false;
}
void add(int y) {
	if (q.empty())
		q.push_back(y);
	else if (judge(q.back(), y)) {
		while ((!q.empty()) && judge(q.back(), y)) {
			q.pop_back();
		}
		q.push_back(y);
	}
	else
		q.push_back(y);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
	}
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d", &k);
		while (!q.empty()) {
			q.pop_back();
		}
		memset(f, 0, sizeof(f));
		add(1);
		for (int i = 2; i <= n; i++) {
			if (d[i] >= d[q.back()]) {
				f[i] = f[q.back()] + 1;
			}
			else
			{
				f[i] = f[q.back()];
			}
			add(i);
		}
		printf("%d\n", f[n]);
	}
}