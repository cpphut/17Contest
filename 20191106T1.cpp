#include<cstdio>
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
int k, len, cur;
long long mul[51], ans;
string s;
stack<int> lv;
int main() {
	cin >> k >> s;
	len = s.length();
	len = min(len, 200);
	k = min(k, 50);
	mul[0] = 1;
	for (int i = 1; i <= 50; i++) {
		mul[i] = mul[i - 1] * 4;
	}
	lv.push(k);
	for (int i = 0; i < len; i++) {
		cur = lv.top();
		lv.pop();
		if (s[i] == '0') {
			ans += mul[cur];
		}
		if (s[i] == '2') {
			lv.push(cur - 1);
			lv.push(cur - 1);
			lv.push(cur - 1);
			lv.push(cur - 1);
		}
	}
	cout << ans;
	return 0;
}