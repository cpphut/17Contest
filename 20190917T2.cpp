#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
#define N 1000001
using namespace std;
int n, d[N], f[N], k, Q;
deque <int> q;
bool judge(int x, int y) {
	if (f[y] < f[x])
		return true;
	if (f[y] == f[x] && d[y] >= d[x])
		return true;
	return false;
}
void add(int y) {
	if (q.empty())
		q.push_back(y);
	else {
		while (judge(q.back(), y)) {
			q.pop_back();
			if (q.empty())
				break;
		}
		q.push_back(y);
	}
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
			while (q.front() < i - k) {
				q.pop_front();
				if (q.empty())
					break;
			}
			if (d[i] >= d[q.front()]) {
				f[i] = f[q.front()] + 1;
			}
			else
			{
				f[i] = f[q.front()];
			}
			add(i);
		}
		printf("%d\n", f[n]);
	}
}