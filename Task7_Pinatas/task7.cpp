#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;

int step(vector<int>& pinatas, int l, int r, vector<vector<int>>& dp) {
	if (l > r) {
		return 0;
	}
	if (dp[l][r] != -1) {
		return dp[l][r];
	}

	dp[l][r] = 0;
	for (int i = l; i <= r; i++) {
		int win = pinatas[l - 1] * pinatas[i] * pinatas[r + 1];
		win += step(pinatas, l, i - 1, dp) + step(pinatas, i + 1, r, dp);
		dp[l][r] = max(dp[l][r], win);
	}
	return dp[l][r];
}

int maxCandies(vector<int> data) {
	int n = data.size();
	vector<int> pinatas(n + 2, 1);
	for (int i = 0; i < n; i++) {
		pinatas[i + 1] = data[i];
	}

	vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
	return step(pinatas, 1, n, dp);
}

int main() {
	vector<int> inp = {};
	int n;
	cout << "Enter the size of an array" << endl;
	cin >> n;
	cout << "Enter the capacities of pinatas" << endl;

	int elem;
	for (int i = 0; i < n; i++) {
		cin >> elem;
		inp.push_back(elem);
	}
	cout << "The maximal amount of candies won is " << maxCandies(inp);
	return 0;
}