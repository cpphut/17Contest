#include<cstdio>
#include<algorithm>
#define N 100001
#define M 300001
#define INF 0x3f3f3f3f
#define ll long long
using namespace std;
ll n, m, tot = 0, head[N], bz[N][19], ma[N][19], mi[N][19], depth[N], F[N];
bool Y[M << 1];
struct edge {
	ll u, v, d;
	ll next;
}G[N << 1], X[M << 1];
void addedge(ll u, ll v, ll d)
{
	G[++tot].u = u, G[tot].v = v, G[tot].d = d, G[tot].next = head[u], head[u] = tot;
	G[++tot].u = v, G[tot].v = u, G[tot].d = d, G[tot].next = head[v], head[v] = tot;
}
void dfs(ll u, ll fa)
{
	bz[u][0] = fa;
	for (ll i = head[u]; i; i = G[i].next)
	{
		ll v = G[i].v;
		if (v == fa)
			continue;
		depth[v] = depth[u] + 1ll;
		ma[v][0] = G[i].d;
		mi[v][0] = -INF;
		dfs(v, u);
	}
}
void calc()
{
	for (ll i = 1; i <= 18; i++)
		for (ll j = 1; j <= n; ++j)
		{
			bz[j][i] = bz[bz[j][i - 1]][i - 1];
			ma[j][i] = max(ma[j][i - 1], ma[bz[j][i - 1]][i - 1]);
			mi[j][i] = max(mi[j][i - 1], mi[bz[j][i - 1]][i - 1]);
			if (ma[j][i - 1] > ma[bz[j][i - 1]][i - 1])
				mi[j][i] = max(mi[j][i], ma[bz[j][i - 1]][i - 1]);
			else
				if (ma[j][i - 1] < ma[bz[j][i - 1]][i - 1])
					mi[j][i] = max(mi[j][i], ma[j][i - 1]);
		}
}
ll getlca(ll x, ll y)
{
	if (depth[x] < depth[y])swap(x, y);
	for (ll i = 18; i >= 0; i--)
		if (depth[bz[x][i]] >= depth[y])
			x = bz[x][i];
	if (x == y)return x;
	for (ll i = 18; i >= 0; i--)
		if (bz[x][i] ^ bz[y][i])
			x = bz[x][i], y = bz[y][i];
	return bz[x][0];
}
ll qmax(ll u, ll v, ll maxx)
{
	ll ans = -INF;
	for (ll i = 18; i >= 0; i--)
	{
		if (depth[bz[u][i]] >= depth[v])
		{
			if (maxx != ma[u][i])ans = max(ans, ma[u][i]);
			else ans = max(ans, mi[u][i]);
			u = bz[u][i];
		}
	}
	return ans;
}
bool cmp(edge x, edge y)
{
	return x.d < y.d;
}
ll getf(ll x)
{
	return (x == F[x]) ? x : F[x] = getf(F[x]);
}
int main()
{
	scanf("%lld%lld", &n, &m);
	for (ll i = 1; i <= m; i++)
	{
		scanf("%lld%lld%lld", &X[i].u, &X[i].v, &X[i].d);
	}
	sort(X + 1, X + m + 1, cmp);
	for (ll i = 1; i <= n; i++) {
		F[i] = i;
	}
	ll cnt = 0;
	for (ll i = 1; i <= m; i++)
	{
		ll Father_u = getf(X[i].u);
		ll Father_v = getf(X[i].v);
		if (Father_u != Father_v)
		{
			cnt += X[i].d;
			F[Father_u] = Father_v;
			addedge(X[i].u, X[i].v, X[i].d);
			Y[i] = true;
		}
	}
	mi[1][0] = -INF;
	depth[1] = 1;
	dfs(1, -1);
	calc();
	ll ans = INF;
	for (ll i = 1; i <= m; i++)
	{
		if (!Y[i])
		{
			ll u = X[i].u;
			ll v = X[i].v;
			ll d = X[i].d;
			ll lca = getlca(u, v);
			ll maxu = qmax(u, lca, d);
			ll maxv = qmax(v, lca, d);
			ans = min(ans, cnt - max(maxu, maxv) + d);
		}
	}
	printf("%lld", ans);
	return 0;
}