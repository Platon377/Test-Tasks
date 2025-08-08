#include <iostream>
#include <sstream>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::multimap;
using std::make_pair;
using std::getline;
using std::istringstream;

typedef long long ll;


class Order {
private:
	ll user_id;
	ll amount;
	ll price;
	bool side;

public:
	Order(ll user_id, ll amount, ll price, bool side) {
		this->user_id = user_id;
		this->amount = amount;
		this->price = price;
		this->side = side;
	}

	ll getUser() const { return this->user_id; }
	ll getAmount() const { return this->amount; }
	ll getPrice() const { return this->price; }
	bool getSide() const { return this->side; }

};

void OrderBook() {
	ll user_id, amount, price;
	bool side;
	multimap <ll, Order> sell = {};
	multimap <ll, Order> buy = {};
	cout << "Enter the data in format <user_id> <amount> <price> <side> with side = 1 if you're selling and 0 otherwise" << endl;
	string line;

	while (true) {
		getline(cin, line);

		if (line == "end" || line == "End") {
			cout << "Exiting the order book" << endl;
			break;
		}

		istringstream iss(line);

		if (!(iss >> user_id >> amount >> price >> side)) {
			cout << "Invalid input, try again" << endl;
			continue;
		}

		if (side) {
			sell.insert(make_pair(price, Order(user_id, amount, price, side)));
		}
		else {
			buy.insert(make_pair(price, Order(user_id, amount, price, side)));
		}
		if (sell.empty() || buy.empty() || sell.begin()->first > buy.rbegin()->first) {
			continue;
		}

		Order cur_sell = sell.begin()->second;
		sell.erase(sell.begin());
		Order cur_buy = buy.rbegin()->second;
		buy.erase(--buy.end());

		if (cur_sell.getAmount() == cur_buy.getAmount()) {
			cout << "The user " << cur_sell.getUser() << " sold " << cur_sell.getAmount() << "UAH" << endl;
			cout << "The user " << cur_buy.getUser() << " bought " << (double)cur_buy.getAmount() / cur_buy.getPrice() << "USD" << endl;
		}
		else if (cur_sell.getAmount() < cur_buy.getAmount()) {
			cout << "The user " << cur_sell.getUser() << " sold " << cur_sell.getAmount() << "UAH" << endl;
			cout << "The user " << cur_buy.getUser() << " bought " << (double)cur_sell.getAmount() / cur_buy.getPrice() << "USD" << endl;
			buy.insert(make_pair(cur_buy.getPrice(), Order(cur_buy.getUser(), (cur_buy.getAmount() - cur_sell.getAmount()), cur_buy.getPrice(), false)));
		}
		else if (cur_sell.getAmount() > cur_buy.getAmount()) {
			cout << "The user " << cur_sell.getUser() << " sold " << cur_buy.getAmount() << "UAH" << endl;
			cout << "The user " << cur_buy.getUser() << " bought " << (double)cur_buy.getAmount() / cur_buy.getPrice() << "USD" << endl;
			sell.insert(make_pair(cur_sell.getPrice(), Order(cur_sell.getUser(), (cur_sell.getAmount() - cur_buy.getAmount()), cur_sell.getPrice(), true)));
		}

	}
}

int main() {

	OrderBook();
	return 0;
}