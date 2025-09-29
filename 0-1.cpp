#include <iostream>

int LowerBound(int* arr, int n, int req) {
	int l = 0, r = n;
	while (l < r) {
		int m = l + (r - l) / 2;
		if (arr[m] >= req) r = m;
		else l = m + 1;
	}
	return l;
}

int UpperBound(int* arr, int n, int req) {
	int l = 0, r = n;
	while (l < r) {
		int m = l + (r - l) / 2;
		if (arr[m] <= req) l = m + 1;
		else r = m;
	}
	return l;
}

int main()
{
	int n = 0;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) std::cin >> arr[i];

	int k = 0, req;
	std::cin >> k;

	for(int i = 0; i < k; i++) {
		std::cin >> req;
		int l = LowerBound(arr, n, req), u = UpperBound(arr, n, req);
		std::cout << (l == u ? 0: 1) << " " << l << " " << u << std::endl;
	}

	delete[] arr;
}