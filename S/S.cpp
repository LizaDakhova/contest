#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

using namespace std;

class RationalDivisionByZero : logic_error {
public:
	RationalDivisionByZero();
};

RationalDivisionByZero::RationalDivisionByZero() : logic_error("Error") {}

class Rational{
private:
	int p;
	int q;
	void assign(const char *);
	void reduce();
	friend int comparator(const Rational &, const Rational &); // returns 1 if a > b, - 0 if a = b, -1 if a < b
public:
	Rational();
	Rational(const int p, const int q = 1);
	Rational(const char *);
	Rational(const Rational &);
	int getNumerator() const;
	int getDenominator() const;
	friend istream &operator >> (istream &, Rational &);
	friend ostream &operator<<(ostream &, const Rational &);
	friend Rational operator+(const Rational &, const Rational &);
	friend Rational operator+(const Rational &, const int &);
	friend Rational operator+(const int &, const Rational &);
	friend Rational operator-(const Rational &, const Rational &);
	friend Rational operator-(const Rational &, const int &);
	friend Rational operator-(const int &, const Rational &);
	friend Rational operator*(const Rational &, const Rational &);
	friend Rational operator*(const Rational &, const int &);
	friend Rational operator*(const int &, const Rational &);
	friend Rational operator/(const Rational &, const Rational &);
	friend Rational operator/(const Rational &, const int &);
	friend Rational operator/(const int &, const Rational &);
	Rational &operator=(const Rational &);
	Rational &operator=(const int &);
	Rational &operator+=(const Rational &);
	Rational &operator+=(const int &);
	Rational &operator-=(const Rational &);
	Rational &operator-=(const int &);
	Rational &operator*=(const Rational &);
	Rational &operator*=(const int &);
	Rational &operator/=(const Rational &);
	Rational &operator/=(const int &);
	friend bool operator>(const Rational &, const Rational &);
	friend bool operator>(const Rational &, const int &);
	friend bool operator>(const int &, const Rational &);
	friend bool operator>=(const Rational &, const Rational &);
	friend bool operator>=(const Rational &, const int &);
	friend bool operator>=(const int &, const Rational &);
	friend bool operator<(const Rational &, const Rational &);
	friend bool operator<(const Rational &, const int &);
	friend bool operator<(const int &, const Rational &);
	friend bool operator<=(const Rational &, const Rational &);
	friend bool operator<=(const Rational &, const int &);
	friend bool operator<=(const int &, const Rational &);
	friend bool operator==(const Rational &, const Rational &);
	friend bool operator==(const Rational &, const int &);
	friend bool operator==(const int &, const Rational &);
	friend bool operator!=(const Rational &, const Rational &);
	friend bool operator!=(const Rational &, const int &);
	friend bool operator!=(const int &, const Rational &);
	friend Rational operator-(const Rational &);
	friend Rational operator+(const Rational &);
	Rational &operator++();
	Rational operator++(int);
	Rational &operator--();
	Rational operator--(int);
};

void Rational::assign(const char *s) {
	int sign = 1;
	int i = 0;
	int nominator = 0;
	int denominator;
	if (s[0] == '-') {
		sign = -1;
		++i;
	}
	while (s[i] != '/' && i < strlen(s)) {
		nominator = nominator * 10 + s[i] - 48;
		++i;
	}
	nominator *= sign;
	if (i == strlen(s))
		denominator = 1;
	else {
		++i;
		denominator = 0;
		while (i < strlen(s)) {
			denominator = denominator * 10 + s[i] - 48;
			++i;
		}
	}
	p = nominator;
	q = denominator;
	reduce();
}

void Rational::reduce() {
	int p1 = abs(p);
	int q1 = q;
	while (p1 > 0 && q1 > 0) {
		if (p1 > q1)
			p1 = p1 % q1;
		else
			q1 = q1 % p1;
	}
	p /= (p1 + q1);
	q /= (p1 + q1);
}

int comparator(const Rational &a, const Rational &b) {
	if (a.p * b.q > a.q * b.p)
		return 1;
	else if (a.p * b.q == a.q * b.p)
		return 0;
	else
		return -1;
}

Rational::Rational() {}

Rational::Rational(const int p, const int q) {
	if (q < 0) {
		this->p = -p;
		this->q = -q;
	}
	else {
		this->p = p;
		this->q = q;
	}
	this->reduce();
}

Rational::Rational(const char *s) {
	assign(s);
}

Rational::Rational(const Rational &that) {
	this->p = that.p;
	this->q = that.q;
}

int Rational::getNumerator() const {
	return p;
}

int Rational::getDenominator() const {
	return q;
}

istream &operator>>(istream &in, Rational &rational) {
	char s[100];
	in >> s;
	rational.assign(s);
	return in;
}

ostream &operator<<(ostream &out, const Rational &rational) {
	if (rational.q == 1)
		out << rational.p;
	else
		out << rational.p << '/' << rational.q;
	return out;
}

Rational operator+(const Rational &a, const Rational &b) {
	Rational result;
	result.p = a.p * b.q + a.q * b.p;
	result.q = a.q * b.q;
	result.reduce();
	return result;
}

Rational operator+(const Rational &a, const int &b) {
	Rational result;
	result.p = a.p + a.q * b;
	result.q = a.q;
	result.reduce();
	return result;
}

Rational operator+(const int &b, const Rational &a) {
	Rational result;
	result.p = a.p + a.q * b;
	result.q = a.q;
	result.reduce();
	return result;
}

Rational operator-(const Rational &a, const Rational &b) {
	Rational result;
	result.p = a.p * b.q - a.q * b.p;
	result.q = a.q * b.q;
	result.reduce();
	return result;
}
Rational operator-(const Rational &a, const int &b) {
	Rational result;
	result.p = a.p - a.q * b;
	result.q = a.q;
	result.reduce();
	return result;
}
Rational operator-(const int &b, const Rational &a) {
	Rational result;
	result.p = a.p - a.q * b;
	result.q = a.q;
	result.reduce();
	return result;
}

Rational operator*(const Rational &a, const Rational &b) {
	Rational result;
	result.p = a.p * b.p;
	result.q = a.q * b.q;
	result.reduce();
	return result;
}

Rational operator*(const Rational &a, const int &b) {
	Rational result;
	result.p = a.p * b;
	result.q = a.q;
	result.reduce();
	return result;
}

Rational operator*(const int &b, const Rational &a) {
	Rational result;
	result.p = a.p * b;
	result.q = a.q;
	result.reduce();
	return result;
}

Rational operator/(const Rational &a, const Rational &b) {
	if (b.p == 0) 
		throw RationalDivisionByZero();
	Rational result;
	int sign = b.p / abs(b.p);
	result.p = a.p * b.q * sign;
	result.q = a.q * abs(b.p);
	result.reduce();
	return result;
}

Rational operator/(const Rational &a, const int &b) {
	if (b == 0) 
		throw RationalDivisionByZero();
	Rational result;
	int sign = b / abs(b);
	result.p = a.p * sign;
	result.q = a.q * abs(b);
	result.reduce();
	return result;
}

Rational operator/(const int &b, const Rational &a) {
	if (a.p == 0) 
		throw RationalDivisionByZero();
	Rational result;
	int sign = a.p / abs(a.p);
	result.p = b * a.q * sign;
	result.q = abs(a.p);
	result.reduce();
	return result;
}

Rational &Rational::operator=(const Rational &that) {
	this->p = that.p;
	this->q = that.q;
	return *this;
}

Rational &Rational::operator=(const int &that) {
	this->p = that;
	this->q = 1;
	return *this;
}

Rational &Rational::operator+=(const Rational &that) {
	*this = *this + that;
	return *this;
}

Rational &Rational::operator+=(const int &that) {
	*this = *this + that;
	return *this;
}

Rational &Rational::operator-=(const Rational &that) {
	*this = *this - that;
	return *this;
}

Rational &Rational::operator-=(const int &that) {
	*this = *this - that;
	return *this;
}

Rational &Rational::operator*=(const Rational &that) {
	*this = *this * that;
	return *this;
}

Rational &Rational::operator*=(const int &that) {
	*this = *this * that;
	return *this;
}

Rational &Rational::operator/=(const Rational &that) {
	*this = *this / that;
	return *this;
}

Rational &Rational::operator/=(const int &that) {
	*this = *this / that;
	return *this;
}

bool operator>(const Rational &a, const Rational &b) {
	if (comparator(a, b) == 1)
		return true;
	else
		return false;
}

bool operator>(const Rational &a, const int &b) {
	if (comparator(a, Rational(b)) == 1)
		return true;
	else
		return false;
}

bool operator>(const int &b, const Rational &a) {
	if (comparator(Rational(b), a) == 1)
		return true;
	else
		return false;
}

bool operator>=(const Rational &a, const Rational &b) {
	if (comparator(a, b) >= 0)
		return true;
	else
		return false;
}

bool operator>=(const Rational &a, const int &b) {
	if (comparator(a, Rational(b)) >= 0)
		return true;
	else
		return false;
}

bool operator>=(const int &b, const Rational &a) {
	if (comparator(Rational(b), a) >= 0)
		return true;
	else
		return false;
}

bool operator<(const Rational &a, const Rational &b) {
	if (comparator(a, b) == -1)
		return true;
	else
		return false;
}

bool operator<(const Rational &a, const int &b) {
	if (comparator(a, Rational(b)) == -1)
		return true;
	else
		return false;
}

bool operator<(const int &b, const Rational &a) {
	if (comparator(Rational(b), a) == -1)
		return true;
	else
		return false;
}

bool operator<=(const Rational &a, const Rational &b) {
	if (comparator(a, b) <= 0)
		return true;
	else
		return false;
}

bool operator<=(const Rational &a, const int &b) {
	if (comparator(a, Rational(b)) <= 0)
		return true;
	else
		return false;
}

bool operator<=(const int &b, const Rational &a) {
	if (comparator(Rational(b), a) <= 0)
		return true;
	else
		return false;
}

bool operator==(const Rational &a, const Rational &b) {
	if (comparator(a, b) == 0)
		return true;
	else
		return false;
}

bool operator==(const Rational &a, const int &b) {
	if (comparator(a, Rational(b)) == 0)
		return true;
	else
		return false;
}

bool operator==(const int &b, const Rational &a) {
	if (comparator(Rational(b), a) == 0)
		return true;
	else
		return false;
}

bool operator!=(const Rational &a, const Rational &b) {
	if (a == b)
		return false;
	else
		return true;
}

bool operator!=(const Rational &a, const int &b) {
	if (a == b)
		return false;
	else
		return true;
}

bool operator!=(const int &b, const Rational &a) {
	if (a == b)
		return false;
	else
		return true;
}

Rational operator-(const Rational &a) {
	Rational result(a);
	result.p = -a.p;
	return result;
}

Rational operator+(const Rational &a) {
	Rational result(a);
	return result;
}

Rational &Rational::operator++() {
	this->p += this->q;
	return *this;
}

Rational Rational::operator++(int) {
	Rational temp = *this;
	++*this;
	return temp;
}

Rational &Rational::operator--() {
	this->p -= this->q;
	return *this;
}

Rational Rational::operator--(int) {
	Rational temp = *this;
	--*this;
	return temp;
}

int main() {
	int a;
	cin >> a;

	int p, q;
	cin >> p >> q;
	const Rational rc(p, q); // q != 0 is guaranteed by author of tests
	cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

	Rational r1, r2;
	cin >> r1 >> r2;

	cout << r1 << endl;
	cout << r2 << endl;

	try {
		cout << 1 / r1 << endl;
	}
	catch (const RationalDivisionByZero& ex) {
		cout << "Cannot get reciprocal of r1." << endl;
	}

	try {
		cout << rc / r2 << endl;
	}
	catch (const RationalDivisionByZero& ex) {
		cout << "Cannot divide by r2." << endl;
	}

	cout << (r1 < r2) << endl;
	cout << (r1 <= r2) << endl;
	cout << (r1 > r2) << endl;
	cout << (r1 >= r2) << endl;
	cout << (r1 == r2) << endl;
	cout << (r1 != r2) << endl;

	cout << (r1 < a) << endl;
	cout << (r1 <= a) << endl;
	cout << (r1 > a) << endl;
	cout << (r1 >= a) << endl;
	cout << (r1 == a) << endl;
	cout << (r1 != a) << endl;

	cout << (a < r2) << endl;
	cout << (a <= r2) << endl;
	cout << (a > r2) << endl;
	cout << (a >= r2) << endl;
	cout << (a == r2) << endl;
	cout << (a != r2) << endl;

	cout << rc + a << endl
		<< a + rc << endl
		<< -rc * r1 << endl
		<< (+r1 - r2 * rc) * a << endl;

	cout << ++r1 << endl;
	cout << r1 << endl;
	cout << r1++ << endl;
	cout << r1 << endl;
	cout << --r1 << endl;
	cout << r1 << endl;
	cout << r1-- << endl;
	cout << r1 << endl;
	cout << ++++r1 << endl;
	cout << r1 << endl;

	cout << ((((r1 += r2) /= Rational(-5, 3)) -= rc) *= a) << endl;
	cout << (r1 += r2 /= 3) << endl;
	cout << r1 << endl;
	cout << r2 << endl;

	//system("pause");
	return 0;
}