#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::max;
using std::stoi;
using std::ostream;
using std::to_string;
using std::pair;

typedef long long ll;


class BigInt {
	static const int base = 100'000'000;
	static const int width = 8;
	vector<int> digits;
	bool negative = false;
	friend ostream& operator << (ostream& o, const BigInt& num);
	friend bool abs_comp(const BigInt& a, const BigInt& b);


public:

	BigInt& operator = (ll num) {
		digits.clear();
		if (num < 0) {
			negative = true;
			num = -num;
		}
		else {
			negative = false;
		}

		do {
			digits.push_back(num % base);
			num /= base;
		} while (num > 0);
		return *this;
	}

	BigInt& operator = (const string s) {
		digits.clear();
		negative = false;
		int len = s.length();
		int start = 0;

		if (s[0] == '-') {
			negative = true;
			start = 1;
		}

		for (int i = len; i > start; i -= width) {
			int begin = max(start, i - width);
			digits.push_back(stoi(s.substr(begin, i - begin)));
		}
		del_leading_zeros();
		return *this;
	}

	void del_leading_zeros() {
		while (!digits.empty() && digits.back() == 0) {
			digits.pop_back();
		}
		if (digits.empty()) {
			negative = false;
		}
	}

	BigInt(ll num = 0) {
		*this = num;
	}
	BigInt(const string& s) {
		*this = s;
	}

	BigInt abs() const {
		BigInt res = *this;
		res.negative = false;
		return res;
	}

	bool operator == (const BigInt& o) const {
		return negative == o.negative && digits == o.digits;
	}
	bool operator != (const BigInt& o) const {
		return !(*this == o);
	}
	bool operator < (const BigInt& o) const {
		if (negative != o.negative) {
			return negative;
		}

		bool less = abs_comp(*this, o);
		return negative ? !less && *this != o : less;		
	}
	bool operator <= (const BigInt& o) const {
		return *this < o || *this == o;
	}
	bool operator > (const BigInt& o) const {
		return !(*this <= o);
	}
	bool operator >= (const BigInt& o) const {
		return !(*this < o);
	}

	string getString() const {
		if (digits.empty()) {
			return "0";
		}

		string res;
		if (negative && !(digits.size() == 1 && digits[0] == 0)) {
			res.push_back('-');
		}
		res += to_string(digits.back());
		for (int i = digits.size() - 2; i >= 0; i--) {
			string block = to_string(digits[i]);
			res += string(width - block.length(), '0') + block;
		}
		return res;
	}

	ll getInt() const {
		ll res = 0;
		for (int i = digits.size() - 1; i >= 0; i--) {
			res = res * base + digits[i];
		}
		return negative ? -res : res;
	}

	BigInt operator + (const BigInt& o) const {
		if (negative != o.negative) {
			if (negative) {
				return o - this->abs();
			}
			else {
				return *this - o.abs();
			}
		}
		BigInt res;
		res.digits.clear();
		res.negative = negative;
		int carry = 0;
		for (int i = 0; i < max(digits.size(), o.digits.size()) || carry; i++) {
			int sum = carry;
			if (i < digits.size()) { sum += digits[i]; }
			if (i < o.digits.size()) { sum += o.digits[i]; }

			res.digits.push_back(sum % base);
			carry = sum / base;
		}

		res.del_leading_zeros();
		return res;		
	}

	BigInt operator - (const BigInt& o) const {
		if (negative != o.negative) {
			return *this + o.abs();
		}
		if (abs_comp(*this, o)) {
			BigInt res = o - *this;
			res.negative = !negative;
			return res;
		}
		BigInt res = *this;
		int borrow = 0;
		for (int i = 0; i < o.digits.size() || borrow; i++) {
			int dif = res.digits[i] - borrow - (i < o.digits.size() ? o.digits[i] : 0);
			
			borrow = 0;
			if (dif < 0) {
				dif += base;
				borrow = 1;
			}

			res.digits[i] = dif;
		}

		res.del_leading_zeros();
		return res;
	}

	BigInt operator * (const BigInt& o) const {
		BigInt res;
		res.digits.assign(digits.size() + o.digits.size(), 0);
		res.negative = (negative != o.negative);

		for (int i = 0; i < digits.size(); i++) {
			ll carry = 0;
			for (int j = 0; j < o.digits.size(); j++) {
				ll cur = res.digits[i + j] + 1LL * digits[i] * o.digits[j] + carry;
				res.digits[i + j] = int(cur % base);
				carry = cur / base;
			}
			res.digits[i + o.digits.size()] += carry;
		}

		res.del_leading_zeros();
		if (res.digits.empty()) {
			res.negative = false;
		}
		return res;
	}

	pair<BigInt,BigInt> divide (const BigInt& divisor_sgn) const {
		if (divisor_sgn == BigInt(0)) {
			throw "Division by zero";
		}

		BigInt dividend = this->abs();
		BigInt divisor = divisor_sgn.abs();

		BigInt quotient;
		quotient.digits.resize(dividend.digits.size(), 0);

		BigInt remainder;
		for (int i = dividend.digits.size() - 1; i >= 0; i--) {
			remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
			remainder.del_leading_zeros();

			int l = 0;
			int r = base - 1;
			int digit = 0;
			while (l <= r) {
				int mid = (l + r)/2;
				BigInt mid_val = divisor * BigInt(mid);
				if (mid_val <= remainder) {
					digit = mid;
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}

			quotient.digits[i] = digit;
			remainder = remainder - divisor * BigInt(digit);
		}

		quotient.del_leading_zeros();
		remainder.del_leading_zeros();

		quotient.negative = (negative != divisor_sgn.negative) && !quotient.digits.empty();
		remainder.negative = negative && !remainder.digits.empty();
		return { quotient, remainder };
	}

	BigInt operator / (const BigInt& o) {
		return (this->divide(o)).first;
	}
	BigInt operator % (const BigInt& o) {
		return (this->divide(o)).second;
	}
	
};

ostream& operator << (ostream& o, const BigInt& num) {
	o << num.getString();
	return o;
}

bool abs_comp(const BigInt& a, const BigInt& b) {
	if (a.digits.size() != b.digits.size()) {
		return a.digits.size() < b.digits.size();
	}

	for (int i = a.digits.size() - 1; i >= 0; i--) {
		if (a.digits[i] != b.digits[i]) {
			return a.digits[i] < b.digits[i];
		}
	}

	return false;
}

int main() {
	BigInt b = BigInt("10000000000000");
	BigInt a = BigInt(12);
	assert(a + b == BigInt("10000000000012"));
	assert(a - BigInt(0) == BigInt("12"));
	assert(a < b);
	assert(b > a);
	assert(b != a);
	assert(a * b == BigInt("120000000000000"));
	assert(b * BigInt("0") == BigInt("0"));
	assert(b / BigInt("10000") == BigInt("1000000000"));

	return 0;
}