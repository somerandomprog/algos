#include <iostream>
#include <vector>
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;
const int MAX_N = 1e6;

ll ModuloPower(ll base, ll exp) {
	ll res = 1;
	base %= MOD;
	while (exp > 0) {
		if ((exp & 1) == 1) res = (res * base) % MOD;
		base = (base * base) % MOD;
		exp >>= 1;
	}
	return res;
}

int main()
{	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	vector<ll> fact(MAX_N + 1, 1);
	for (int i = 1; i <= MAX_N; i++) fact[i] = (fact[i - 1] * i) % MOD;

	ll numerator = fact[n];
	ll denominator = (fact[k] * fact[n - k]) % MOD;
	cout << ((numerator * ModuloPower(denominator, MOD - 2)) % MOD) << endl;
}