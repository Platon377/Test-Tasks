#include <iostream>
#include <vector>
#include <queue>


using std::vector;
using std::priority_queue;
using std::greater;
using std::pair;
using std::cin;
using std::cout;
using std::endl;


int main() {
	int c, n, k;
	cout << "Input c (starting capital), N (max. laptops that we manage to fix) and K (#laptops)" << endl;
	cin >> c >> n >> k;
	int cur;
	vector<int>gain, price;
	cout << "Input K elements of the gain array" << endl;
	for (int i = 0; i < k; i++) { cin >> cur; gain.push_back(cur); }
	cout << "Input K elements of the price array" << endl;
	for (int i = 0; i < k; i++) { cin >> cur; price.push_back(cur); }
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> a;

	for (int i = 0; i < k; i++) {
		a.emplace(price[i], gain[i]);
	}

	priority_queue<pair<int, int>> b;
	vector<pair<int, int>> bought;
	int items = 0;
	while (items < n) {
		while (!a.empty() && a.top().first <= c) {
			b.emplace(a.top().second, a.top().first);
			a.pop();
		}
		if (b.empty()) { break; }
		if (b.top().first >= b.top().second) {
			c += (b.top().first - b.top().second);
			bought.emplace_back(b.top().second, b.top().first);
			items++;
		}
		b.pop();
	}

	cout << "The max capital after the summer is " << c << endl;
	cout << "The laptops to be chosen" << endl;
	for (auto elem : bought) {
		cout << elem.first << " " << elem.second << endl;
	}
	return 0;
}