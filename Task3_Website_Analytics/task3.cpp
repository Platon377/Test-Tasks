#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;
using std::unordered_map;
using std::ifstream;
using std::stringstream;
using std::getline;


typedef unordered_set<string> pages;
typedef unordered_map<string, pages> data;

data read_csv(const string& filename) {
	data data_read;
	ifstream file(filename);
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string user, product, timestamp;

		getline(ss, user, ';');
		getline(ss, product, ';');
		getline(ss, timestamp, ';');

		data_read[user].insert(product);
	}

	return data_read;
}

bool differ(const pages& p1, const pages& p2) { // O(n) -> O(1)
	for (const auto& page : p2) {
		if (p1.find(page) == p1.end()) { // expected O(1)
			return true;
		}
	}
	return false;
}


int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage:  <fileName1.csv> <fileName2.csv>";
		return 1;
	}
	
	data set1 = read_csv(argv[1]); // O(m)
	data set2 = read_csv(argv[2]); // O(n)

	for (const auto& elem: set2) { // O(n)
		const string& user = elem.first;
		const auto& products_d2 = elem.second;

		auto found = set1.find(user); // expected O(1)
		if (found != set1.end()) {
			const auto& products_d1 = found->second;
			if (differ(products_d1, products_d2)) { // O(n) -> O(1)
				cout << user << endl;
			}
		}
		
	}

	return 0;
}
// general O(n^2 + m) (but only in the worst-case when each user whatches every page on both days)
// O(n + m) in a more realistic scenario