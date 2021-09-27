# BIGINT +-*/%

Assumptions:

* Valid inputs: there are only number characters from '0' to '9'
* No negative numbers
* Simple Implementation



Basically, it is just simple simulating human actions.



Here are the codes.



~~~C++
class bigint :public string {
private:
	static int compare(const bigint& a, const bigint& b) {
		if (a.size() > b.size()) return 1;
		else if (a.size() < b.size()) return -1;
		else {
			for (int i = 0; a[i]; ++i) {
				if (a[i] > b[i]) return 1;
				else if (a[i] < b[i]) return -1;
			}
		}
		return 0;
	}

	static void __sub(bigint& ans, const bigint& a, const bigint& b) {
		for (int i = a.size() - 1, j = b.size() - 1, flag = 0; i >= 0 || j >= 0 || flag; --i, --j) {
			int x = i >= 0 ? a[i] - '0' : 0, y = j >= 0 ? b[j] - '0' : 0;
			int temp = x - y - flag;
			if (temp < 0) {
				temp = 10 - y + x - flag;
				flag = 1;
			}
			else {
				flag = 0;
			}
			ans.push_back(temp + '0');
		}
	}

public:
	bigint() :string() {}
	bigint(const string& num) :string(num) {}
	bigint(const char* num) :string(num) {}
	bigint(const bigint& num) :string(num) {}
	bigint(int size, char c) :string(size, c) {}
	//compares
	friend bool operator>(const bigint& a, const bigint& b) {
		return compare(a, b) == 1;
	}
	friend bool operator>=(const bigint& a, const bigint& b) {
		return compare(a, b) >= 0;
	}
	bool operator==(const bigint& b) {
		return compare(*this, b) == 0;
	}
	friend bool operator!=(const bigint& a, const bigint& b) {
		return compare(a, b) != 0;
	}
	friend bool operator<=(const bigint& a, const bigint& b) {
		return compare(a, b) <= 0;
	}
	friend bool operator<(const bigint& a, const bigint& b) {
		return compare(a, b) < 0;
	}

	friend bigint operator+(const bigint& a, const bigint& b) {
		bigint ans;
		for (int i = a.size() - 1, j = b.size() - 1, flag = 0; i >= 0 || j >= 0 || flag; --i, --j) {
			int x = i >= 0 ? a[i] - '0' : 0, y = j >= 0 ? b[i] - '0' : 0;
			int temp = x + y + flag;
			if (temp > 9) {
				temp -= 10;
				flag = 1;
			}
			else {
				flag = 0;
			}
			ans.push_back(temp + '0');
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}

	friend bigint operator-(const bigint& a, const bigint& b) {
		bigint ans;
		int flag = 0;
		if (a >= b) {
			__sub(ans, a, b);
		}
		else {
			__sub(ans, b, a);
			flag = 1;
		}
		reverse(ans.begin(), ans.end());
		auto start = ans.find_first_not_of("0");
		if (flag) return "-" + ans.substr(start);
		if (start != string::npos)	return ans.substr(start);
		return "0";
	}

	friend bigint operator*(const bigint& a, const bigint& b) {
		bigint ans(a.size() + b.size(), '0');
		for (int i = a.size() - 1; i >= 0; --i) {
			int flag = 0;
			for (int j = b.size() - 1; j >= 0; --j) {
				int temp = ans[i + j + 1] - '0' + (a[i] - '0') * (b[j] - '0') + flag;
				ans[i + j + 1] = temp % 10 + '0';
				flag = temp / 10;
			}
			ans[i] += flag;
		}
		auto start = ans.find_first_not_of("0");
		if (start != string::npos) return ans.substr(start);
		return "0";
	}

	friend bigint operator/(const bigint& a, const bigint& b) {
		if (a < b) return "0";
		bigint ans(a.size(), '0');
		bigint div;
		for (int i = 0; a[i]; ++i) {
			div.push_back(a[i]);
			if (div == b) {
				ans[i] = '1';
				div = "";
				continue;
			}
			int temp = 0;
			while (div > b) {
				div = div - b;
				++temp;
			}
			ans[i] = temp + '0';
		}
		auto start = ans.find_first_not_of("0");
		if (start != string::npos) return ans.substr(start);
		return "0";
	}

	friend bigint operator%(const bigint& a, const bigint& b) {
		if (a.size() == 1 && a[0] == '0') return "0";
		if (b.size() == 1 && b[0] == 0) return "";
		bigint div;
		for (int i = 0; a[i]; ++i) {
			div.push_back(a[i]);
			if (b > div) {
				continue;
			}
			auto start = div.find_first_not_of("0");
			if (start != string::npos) div = div.substr(start);
			else div = "";
			int flag = 0;
			while (div >= b) {
				div = div - b;
			}
		}
		if (div.size() == 0) div.push_back('0');
		return div;
	}
};
~~~

