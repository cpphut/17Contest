#include<cstdio>
#include<cstring>
using namespace std;
int n, rt = 1, tmp[10001], voi[10001];
struct no {
	int dat, use, sz;
	int ls = 0, rs = 0;
}node[10001];
void add(int cur, int x) {
	node[cur].sz += 1;
	if (node[cur].ls == 0 && node[cur].rs == 0) {
		node[cur].dat = x;
		node[cur].ls = 2 * cur;
		node[cur].rs = 2 * cur + 1;
		node[cur].use = 1;
		return;
	}
	if (x < node[cur].dat) {
		add(node[cur].ls, x);
	}
	else {
		add(node[cur].rs, x);
	}
}
int querylv(int cur, int x) {
	if (node[cur].dat == x) {
		return 1;
	}
	if (node[cur].dat < x) {
		return node[node[cur].ls].sz + 1 + querylv(node[cur].rs, x);
	}
	return querylv(node[cur].ls, x);
}
int queryx(int cur, int x) {
	if (x == node[node[cur].ls].sz + 1) {
		return node[cur].dat;
	}
	if (x < node[node[cur].ls].sz + 1) {
		return queryx(node[cur].ls, x);
	}
	return queryx(node[cur].rs, x);
}
int bef(int cur, int x) {
	if (node[cur].dat == x) {
		int cur1 = node[cur].ls;
		while (node[cur1].rs != 0) {
			cur1 = node[cur1].rs;
		}
		return node[cur1].dat;
	}
	if (x < node[cur].dat) {
		return bef(node[cur].ls, x);
	}
	return bef(node[cur].rs, x);
}
int aft(int cur, int x) {
	if (node[cur].dat == x) {
		int cur1 = node[cur].rs;
		while (node[cur1].ls != 0) {
			cur1 = node[cur1].ls;
		}
		return node[cur1].dat;
	}
	if (x < node[cur].dat) {
		return aft(node[cur].ls, x);
	}
	return aft(node[cur].rs, x);
}
void rebuild(int cur) {
	int mid = node[cur].sz >> 1;
	if (node[cur].use == 1) {
		rebuild(node[cur].ls);
		tmp[++tmp[0]] = node[cur].dat;
		rebuild(node[cur].rs);
	}
	//else{
		//voi[++tmp[0]] = cur;
	//}
}
void build(int l, int r) {
	int mid = (l + r) >> 1;
	if (l == r) {
		node[mid].ls = 0;
		node[mid].rs = 0;
		//node[mid].dat = tmp[mid];
		node[mid].sz = 1;
		return;
	}
	if (l < mid) {
		build(l, mid - 1);
		node[mid].ls = (l + mid - 1) >> 1;
	}
	else {
		node[mid].ls = 0;
	}
	build(mid + 1, r);
	node[mid].rs = (r + mid + 1) >> 1;
	node[mid].sz = node[node[mid].ls].sz + node[node[mid].rs].sz + 1;
}
void del(int cur, int x) {
	if (node[cur].dat == x) {
		node[cur].use = 0;
		memset(tmp, 0, sizeof(tmp));
		//memset(voi, 0, sizeof(voi));
		rebuild(rt);
		rt = (node[cur].sz >> 1);
		build(1, tmp[0]);
	}
	if (x < node[cur].dat) {
		del(node[cur].ls, x);
	}
	del(node[cur].rs, x);
}
int main() {
	scanf("%d", &n);
	for (int i = 1, typ, x; i <= n; i++) {
		scanf("%d%d", &typ, &x);
		if (typ == 1) {
			add(rt, x);
		}
		if (typ == 3) {
			printf("%d\n", querylv(rt, x));
		}
		if (typ == 4) {
			printf("%d\n", queryx(rt, x));
		}
		if (typ == 5) {
			printf("%d\n", bef(rt, x));
		}
		if (typ == 6) {
			printf("%d\n", aft(rt, x));
		}
		if (typ == 2) {
			del(rt, x);
		}
	}
	return 0;
}