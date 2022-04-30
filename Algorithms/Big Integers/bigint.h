#ifndef __BIGINT_H_
#define __BIGINT_H_
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
// using namespace std;
class bigint {
 private:
  std::string value;
  char sign;

 private:
  int compare(const bigint &b) const;
  std::string __sub(const std::string &num1, const std::string &num2) const;

  // constructors
 public:
  bigint();
  bigint(const bigint &);
  bigint(bigint &&);
  bigint(const long long &);
  bigint(const std::string &);
  bigint(std::string &&);
  bigint(const char *);
  ~bigint();

  // operators
 public:
  // assignmenet operators
  bigint &operator=(const bigint &);
  bigint &operator=(bigint &&);
  bigint &operator=(const long long &);
  bigint &operator=(const std::string &);
  bigint &operator=(std::string &&);
  bigint &operator=(const char *);

  // unary arithmetic operators
  bigint operator+() const;
  bigint operator-() const;

  // other arithmetic operators
  bigint operator+(const bigint &) const;
  bigint operator-(const bigint &) const;
  bigint operator*(const bigint &) const;
  bigint operator/(const bigint &) const;
  bigint operator%(const bigint &) const;
  bigint operator+(const long long &) const;
  bigint operator-(const long long &) const;
  bigint operator*(const long long &) const;
  bigint operator/(const long long &) const;
  bigint operator%(const long long &) const;
  bigint operator+(const std::string &) const;
  bigint operator-(const std::string &) const;
  bigint operator*(const std::string &) const;
  bigint operator/(const std::string &) const;
  bigint operator%(const std::string &) const;
  bigint operator+(const char *) const;
  bigint operator-(const char *) const;
  bigint operator*(const char *) const;
  bigint operator/(const char *) const;
  bigint operator%(const char *) const;

  bigint &operator+=(const bigint &);
  bigint &operator-=(const bigint &);
  bigint &operator*=(const bigint &);
  bigint &operator/=(const bigint &);
  bigint &operator%=(const bigint &);
  bigint &operator+=(const long long &);
  bigint &operator-=(const long long &);
  bigint &operator*=(const long long &);
  bigint &operator/=(const long long &);
  bigint &operator%=(const long long &);
  bigint &operator+=(const std::string &);
  bigint &operator-=(const std::string &);
  bigint &operator*=(const std::string &);
  bigint &operator/=(const std::string &);
  bigint &operator%=(const std::string &);
  bigint &operator+=(const char *);
  bigint &operator-=(const char *);
  bigint &operator*=(const char *);
  bigint &operator/=(const char *);
  bigint &operator%=(const char *);

  // increment and decrement
  bigint &operator++();
  bigint &operator--();
  bigint operator++(int);
  bigint operator--(int);

  // comparison
  bool operator<(const bigint &) const;
  bool operator>(const bigint &) const;
  bool operator<=(const bigint &) const;
  bool operator>=(const bigint &) const;
  bool operator==(const bigint &) const;
  bool operator!=(const bigint &) const;
  bool operator<(const long long &) const;
  bool operator>(const long long &) const;
  bool operator<=(const long long &) const;
  bool operator>=(const long long &) const;
  bool operator==(const long long &) const;
  bool operator!=(const long long &) const;
  bool operator<(const std::string &) const;
  bool operator>(const std::string &) const;
  bool operator<=(const std::string &) const;
  bool operator>=(const std::string &) const;
  bool operator==(const std::string &) const;
  bool operator!=(const std::string &) const;
  bool operator<(const char *) const;
  bool operator>(const char *) const;
  bool operator<=(const char *) const;
  bool operator>=(const char *) const;
  bool operator==(const char *) const;
  bool operator!=(const char *) const;

  // I/O stream operators
  friend std::istream &operator>>(std::istream &in, bigint &);
  friend std::ostream &operator<<(std::ostream &, const bigint &);

 public:
  bool is_valid_digit(const std::string &);
  static bigint rand_generate();
  static bigint bigint_abs(const bigint &);
  void set_sign(char);
};
int bigint::compare(const bigint &b) const {
  const bigint &num = *this;
  if (num.sign == '-' && b.sign == '+') {
    return -1;
  } else if (num.sign == '+' && b.sign == '-') {
    return 1;
  } else if (num.sign == '+') {
    if (num.value.size() > b.value.size()) {
      return 1;
    } else if (num.value.size() < b.value.size()) {
      return -1;
    } else {
      for (int i = 0; i < num.value.size(); ++i) {
        if (num.value[i] > b.value[i])
          return 1;
        else if (num.value[i] < b.value[i])
          return -1;
      }
      return 0;
    }
  } else if (num.sign == '-') {
    if (num.value.size() > b.value.size()) {
      return -1;
    } else if (num.value.size() < b.value.size()) {
      return 1;
    } else {
      for (int i = 0; i < num.value.size(); ++i) {
        if (num.value[i] > b.value[i]) {
          return -1;
        } else if (num.value[i] < b.value[i]) {
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
}
std::string bigint::__sub(const std::string &a, const std::string &b) const {
  std::string ans;
  for (int i = a.size() - 1, j = b.size() - 1, flag = 0;
       i >= 0 || j >= 0 || flag; --i, --j) {
    int x = i >= 0 ? a[i] - '0' : 0, y = j >= 0 ? b[j] - '0' : 0;
    int temp = x - y - flag;
    if (temp < 0) {
      temp = 10 - y + x - flag;
      flag = 1;
    } else {
      flag = 0;
    }
    ans.push_back(temp + '0');
  }
  reverse(ans.begin(), ans.end());
  auto start = ans.find_first_not_of("0");
  if (start == 0) return ans;
  if (start != std::string::npos) {
    return ans.substr(start);
  }
  return "0";
}
void strip_leading_zeroes(std::string &s) {
  auto start = s.find_first_not_of("0");
  if (start == 0) return;
  if (start == std::string::npos) {
    s = "0";
    return;
  } else {
    s = std::move(s.substr(start));
  }
}
bigint::bigint() {
  value = "0";
  sign = '+';
}
bigint::bigint(const bigint &num) {
  value = num.value;
  sign = num.sign;
}
bigint::bigint(bigint &&num) {
  if (this == &num) {
    return;
  }
  *this = std::move(num);
}
bigint::bigint(const long long &num) {
  long long b = num;
  if (num < 0) {
    sign = '-';
    b = -b;
  } else {
    sign = '+';
  }
  value = std::move(std::to_string(b));
}
bigint::bigint(const std::string &num) {
  if (is_valid_digit(num)) {
    if (num[0] == '-') {
      sign = '-';
      value = std::move(num.substr(1));
    } else {
      sign = '+';
      value = num;
    }
  } else {
    std::cerr << "Not valid number!\n";
    value = "0";
    sign = '+';
    return;
  }
  strip_leading_zeroes(this->value);
}
bigint::bigint(std::string &&num) {
  if (is_valid_digit(num)) {
    value = std::exchange(num, "");
    if (num[0] == '-') {
      sign = value[0];
      value = value.substr(1);
    } else {
      sign = '+';
    }
  } else {
    std::cerr << "Not valid number! Original number was kept.\n";
  }
  strip_leading_zeroes(this->value);
}
bigint::bigint(const char *val) {
  std::string num = val;
  *this = std::move(bigint(num));
}
bigint::~bigint() {}

// operators
// assignmenet operators
bigint &bigint::operator=(const bigint &num) {
  value = num.value;
  sign = num.sign;
  return *this;
}
bigint &bigint::operator=(bigint &&num) {
  if (this == &num) {
    return *this;
  }
  value = std::exchange(num.value, "");
  sign = std::exchange(num.sign, 0);
  return *this;
}
bigint &bigint::operator=(const long long &val) {
  *this = std::move(bigint(val));
  return *this;
}
bigint &bigint::operator=(const std::string &num) {
  if (is_valid_digit(num)) {
    if (num[0] == '-') {
      sign = '-';
      value = std::move(num.substr(1));
    } else {
      sign = '+';
      value = num;
    }
  } else {
    std::cerr << "Not valid number! Original number is kept.\n";
  }
  strip_leading_zeroes(this->value);
  return *this;
}
bigint &bigint::operator=(std::string &&num) {
  if (is_valid_digit(num)) {
    value = std::exchange(num, "");
    if (num[0] == '-') {
      sign = value[0];
      value = value.substr(1);
    } else {
      sign = '+';
    }
  } else {
    std::cerr << "Not valid number! Original number was kept.\n";
  }
  strip_leading_zeroes(this->value);
  return *this;
}
bigint &bigint::operator=(const char *val) {
  std::string num = val;
  *this = num;
  return *this;
}

// unary arithmetic operators
bigint bigint::operator+() const { return *this; }
bigint bigint::operator-() const {
  bigint temp(*this);
  if (value != "0") {
    if (sign == '+') {
      temp.sign = '-';
    } else {
      temp.sign = '+';
    }
  }
  return temp;
}

// // other arithmetic operators
bigint bigint::operator+(const bigint &num) const {
  if (sign == '+' && num.sign == '-') {
    bigint temp = num;
    temp.sign = '+';
    return *this - temp;
  } else if (sign == '-' && num.sign == '+') {
    bigint temp = *this;
    temp.sign = '+';
    return num - temp;
  }
  const std::string &a = this->value, &b = num.value;
  std::string result;
  for (int i = a.size() - 1, j = b.size() - 1, flag = 0;
       i >= 0 || j >= 0 || flag; --i, --j) {
    int x = i >= 0 ? a[i] - '0' : 0, y = j >= 0 ? b[j] - '0' : 0;
    int temp = x + y + flag;
    if (temp > 9) {
      temp -= 10;
      flag = 1;
    } else {
      flag = 0;
    }
    result.push_back(temp + '0');
  }
  reverse(result.begin(), result.end());
  bigint ans(std::move(result));
  if (sign == '-') {
    ans.sign = '-';
  }
  return ans;
}
bigint bigint::operator-(const bigint &num) const {
  if (sign == '+' && num.sign == '-') {
    bigint temp(num);
    temp.sign = '+';
    return *this + temp;
  } else if (sign == '-' && num.sign == '+') {
    bigint temp = num;
    temp.sign = '-';
    return *this + temp;
  }
  bool negative = false;
  std::string result;
  if (compare(num) < 0) {
    negative = true;
    result = sign == '+' ? std::move(__sub(num.value, this->value))
                         : std::move(__sub(this->value, num.value));
  } else {
    result = sign == '+' ? std::move(__sub(this->value, num.value))
                         : std::move(__sub(num.value, this->value));
  }
  bigint ans(std::move(result));
  ans.sign = negative ? '-' : '+';
  return ans;
}
bigint bigint::operator*(const bigint &num) const {
  const std::string &a = this->value, &b = num.value;
  if (a == "0" || b == "0") return bigint();
  std::string result(a.size() + b.size(), '0');
  for (int i = a.size() - 1; i >= 0; --i) {
    int flag = 0;
    for (int j = b.size() - 1; j >= 0; --j) {
      int temp = result[i + j + 1] - '0' + (a[i] - '0') * (b[j] - '0') + flag;
      result[i + j + 1] = temp % 10 + '0';
      flag = temp / 10;
    }
    result[i] += flag;
  }
  strip_leading_zeroes(result);
  bigint ans(result);
  if (sign != num.sign) {
    ans.sign = '-';
  }
  return ans;
}
bigint bigint::operator/(const bigint &num) const {
  if (bigint_abs(*this) < bigint_abs(num)) return bigint();
  bigint ans, div;
  div.value.pop_back();
  bigint a(*this), b = (num);
  a.sign = b.sign = '+';
  ans.value = std::string(a.value.size(), '0');
  for (int i = 0; a.value[i]; ++i) {
    if (div.value == "0") div.value.pop_back();
    div.value.push_back(a.value[i]);
    if (div == b) {
      ans.value[i] = '1';
      div.value = "";
      continue;
    }
    int temp = 0;
    while (div >= b) {
      div -= b;
      ++temp;
    }
    ans.value[i] = temp + '0';
  }
  strip_leading_zeroes(ans.value);
  if (sign != num.sign) {
    ans.sign = '-';
  }
  return ans;
}
bigint bigint::operator%(const bigint &num) const {
  if (num.value == "0") {
    std::cerr << "Divisor can't be 0\n";
    return bigint();
  }
  if (this->value == "0") {
    return bigint();
  }
  bigint div;
  div.value.pop_back();
  bigint a(*this), b(num);
  a.sign = b.sign = '+';
  for (int i = 0; a.value[i]; ++i) {
    if (div.value == "0") div.value.pop_back();
    div.value.push_back(a.value[i]);
    if (b > div) {
      continue;
    }
    auto start = div.value.find_first_not_of("0");
    if (start != std::string::npos)
      div.value = div.value.substr(start);
    else
      div.value = "";
    int flag = 0;
    while (div >= b) {
      div -= b;
    }
  }
  if (div.value.size() == 0) div.value.push_back('0');
  if (div.value != "0" && sign != num.sign) {
    div -= b;
  }
  div.sign = '+';
  return div;
}
bigint bigint::operator+(const long long &num) const {
  return *this + bigint(num);
}
bigint bigint::operator-(const long long &num) const {
  return *this - bigint(num);
}
bigint bigint::operator*(const long long &num) const {
  return *this * bigint(num);
}
bigint bigint::operator/(const long long &num) const {
  return *this / bigint(num);
}
bigint bigint::operator%(const long long &num) const {
  return *this % bigint(num);
}
bigint bigint::operator+(const std::string &num) const {
  return *this + bigint(num);
}
bigint bigint::operator-(const std::string &num) const {
  return *this - bigint(num);
}
bigint bigint::operator*(const std::string &num) const {
  return *this * bigint(num);
}
bigint bigint::operator/(const std::string &num) const {
  return *this / bigint(num);
}
bigint bigint::operator%(const std::string &num) const {
  return *this % bigint(num);
}
bigint bigint::operator+(const char *num) const { return *this + bigint(num); }
bigint bigint::operator-(const char *num) const { return *this - bigint(num); }
bigint bigint::operator*(const char *num) const { return *this * bigint(num); }
bigint bigint::operator/(const char *num) const { return *this / bigint(num); }
bigint bigint::operator%(const char *num) const { return *this % bigint(num); }

bigint &bigint::operator+=(const bigint &num) { return *this = *this + num; }
bigint &bigint::operator-=(const bigint &num) { return *this = *this - num; }
bigint &bigint::operator*=(const bigint &num) { return *this = *this * num; }
bigint &bigint::operator/=(const bigint &num) { return *this = *this / num; }
bigint &bigint::operator%=(const bigint &num) { return *this = *this % num; }
bigint &bigint::operator+=(const long long &num) {
  return *this = *this + bigint(num);
}
bigint &bigint::operator-=(const long long &num) {
  return *this = *this - bigint(num);
}
bigint &bigint::operator*=(const long long &num) {
  return *this = *this * bigint(num);
}
bigint &bigint::operator/=(const long long &num) {
  return *this = *this / bigint(num);
}
bigint &bigint::operator%=(const long long &num) {
  return *this = *this % bigint(num);
}
bigint &bigint::operator+=(const std::string &num) {
  return *this = *this + bigint(num);
}
bigint &bigint::operator-=(const std::string &num) {
  return *this = *this - bigint(num);
}
bigint &bigint::operator*=(const std::string &num) {
  return *this = *this * bigint(num);
}
bigint &bigint::operator/=(const std::string &num) {
  return *this = *this / bigint(num);
}
bigint &bigint::operator%=(const std::string &num) {
  return *this = *this % bigint(num);
}
bigint &bigint::operator+=(const char *num) {
  return *this = *this + bigint(num);
}
bigint &bigint::operator-=(const char *num) {
  return *this = *this - bigint(num);
}
bigint &bigint::operator*=(const char *num) {
  return *this = *this * bigint(num);
}
bigint &bigint::operator/=(const char *num) {
  return *this = *this / bigint(num);
}
bigint &bigint::operator%=(const char *num) {
  return *this = *this % bigint(num);
}

// // increment and decrement
bigint &bigint::operator++() { *this += bigint("1"); }
bigint &bigint::operator--() { *this -= bigint("1"); }
bigint bigint::operator++(int) {
  bigint temp = *this + 1;
  *this = temp;
  return temp;
}
bigint bigint::operator--(int) {
  bigint temp = *this - 1;
  *this = temp;
  return temp;
}

// // comparison
bool bigint::operator<(const bigint &num) const { return compare(num) < 0; }
bool bigint::operator>(const bigint &num) const { return compare(num) > 0; }
bool bigint::operator<=(const bigint &num) const { return compare(num) <= 0; }
bool bigint::operator>=(const bigint &num) const { return compare(num) >= 0; }
bool bigint::operator==(const bigint &num) const { return compare(num) == 0; }
bool bigint::operator!=(const bigint &num) const { return compare(num) != 0; }
bool bigint::operator<(const long long &num) const {
  return compare(bigint(num)) < 0;
}
bool bigint::operator>(const long long &num) const {
  return compare(bigint(num)) > 0;
}
bool bigint::operator<=(const long long &num) const {
  return compare(bigint(num)) <= 0;
}
bool bigint::operator>=(const long long &num) const {
  return compare(bigint(num)) >= 0;
}
bool bigint::operator==(const long long &num) const {
  return compare(bigint(num)) == 0;
}
bool bigint::operator!=(const long long &num) const {
  return compare(bigint(num)) != 0;
}
bool bigint::operator<(const std::string &num) const {
  return compare(bigint(num)) < 0;
}
bool bigint::operator>(const std::string &num) const {
  return compare(bigint(num)) > 0;
}
bool bigint::operator<=(const std::string &num) const {
  return compare(bigint(num)) <= 0;
}
bool bigint::operator>=(const std::string &num) const {
  return compare(bigint(num)) >= 0;
}
bool bigint::operator==(const std::string &num) const {
  return compare(bigint(num)) == 0;
}
bool bigint::operator!=(const std::string &num) const {
  return compare(bigint(num)) != 0;
}
bool bigint::operator<(const char *num) const {
  return compare(bigint(num)) < 0;
}
bool bigint::operator>(const char *num) const {
  return compare(bigint(num)) > 0;
}
bool bigint::operator<=(const char *num) const {
  return compare(bigint(num)) <= 0;
}
bool bigint::operator>=(const char *num) const {
  return compare(bigint(num)) >= 0;
}
bool bigint::operator==(const char *num) const {
  return compare(bigint(num)) == 0;
}
bool bigint::operator!=(const char *num) const {
  return compare(bigint(num)) != 0;
}

// // I/O stream operators
std::istream &operator>>(std::istream &in, bigint &num) {
  std::string input;
  in >> input;
  num = std::move(bigint(std::move(input)));
  return in;
}
std::ostream &operator<<(std::ostream &out, const bigint &num) {
  if (num.sign == '-') {
    out << num.sign;
  }
  out << num.value;
  return out;
}

bool bigint::is_valid_digit(const std::string &num) {
  int i = 0;
  if (num[i] == '-') ++i;
  for (; i < num.size(); ++i) {
    if (!isdigit(num[i])) return false;
  }
  return true;
}
bigint bigint::rand_generate() { return bigint(); }
bigint bigint::bigint_abs(const bigint &a) {
  bigint ans(a);
  ans.set_sign('+');
  return ans;
}
void bigint::set_sign(char c) {
  if (c != '+' && c != '-') {
    std::cerr << "Wrong char, original char is kept\n";
    return;
  }
  this->sign = c;
}
#endif