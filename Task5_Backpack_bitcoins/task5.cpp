#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::getline;
using std::stoi;
using std::sort;
using namespace::std::chrono;

const int max_size = 1000000;

struct Transaction {
	int tx_id;
	int tx_size;
	int tx_fee;
	double cost;

	Transaction(int id, int size, int fee) {
		tx_id = id;
		tx_size = size;
		tx_fee = fee;
		cost = (double)tx_fee / tx_size;
	}
};

bool my_comparator(const Transaction& a, const Transaction& b) {
	return a.cost > b.cost;
}

vector<Transaction> read_csv(const string& filename) {

	vector<Transaction> data_read;
	ifstream file(filename);
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string id_str, size_str, fee_str;

		getline(ss, id_str, ';');
		getline(ss, size_str, ';');
		getline(ss, fee_str, ';');

		int id = stoi(id_str);
		int size = stoi(size_str);
		int fee = stoi(fee_str);

		data_read.emplace_back(id, size, fee);

	}

	return data_read;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage:  <fileName.csv>";
		return 1;
	}
	auto start = high_resolution_clock::now();
	vector<Transaction> data = read_csv(argv[1]);

	sort(data.begin(), data.end(), my_comparator);

	vector<int> selected;
	int block_size = 0;
	int value = 0;

	for (const auto& tx : data) {
		if (block_size + tx.tx_size <= max_size) {
			block_size += tx.tx_size;
			value += tx.tx_fee;
			selected.push_back(tx.tx_id);
		}
	}

	auto duration = high_resolution_clock::now() - start;

	cout << "Constructed block: " << endl;
	for (const int& id : selected) {
		cout << id << endl;
	}

	cout << "Amount of transactions " << selected.size() << endl;
	cout << "The block size " << block_size << " bytes" << endl;
	cout << "The total extracted value " << value << endl;
	cout << "Construction time " << duration.count() << " miliseconds" << endl;
	cout << "The memory dedicated for storing calculations " << sizeof(Transaction) * data.size() << " bytes" << endl;

	return 0;
}
// general O(n^2 + m) (but only in the worst-case when each user whatches every page on both days)
// O(n + m) in a more realistic scenario