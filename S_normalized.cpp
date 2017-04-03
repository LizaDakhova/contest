#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

using namespace std;

class RationalDivisionByZero : logic_error {
public:
	RationalDivisionByZero();
};

class Rational {
private:
	int p;
	int q;
	void assign(const char *);
	void reduce();
	friend int comparator(const Rational &, const Rational &); // returns 1 if a > b, - 0 if a = b, -1 if a < b
public:
	Rational() { p = 0; q = 1; }
	Rational(const int p, const int q = 1);
	Rational(const char *);
	Rational(const Rational &);
	int getNumerator() const { return p; };
	int getDenominator() const { return q; };
	friend istream &operator >> (istream & is, Rational &);
	friend ostream& operator << (ostream & os, const Rational &);
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

RationalDivisionByZero::RationalDivisionByZero() : logic_error("Error") {}

void Rational::reduce() {
	int p1 = abs(p);
	int q1 = q;
	while (p1 && q1) {
		if (p1 > q1)
			p1 = p1 % q1;
		else
			q1 = q1 % p1;
	}
	p /= (p1 + q1);
	q /= (p1 + q1);
}

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

void Rational::assign(const char *str) {
	int sign = 1;
	int i = 0;
	int nominator = 0;
	int denominator;
	if (str[0] == '-') {
		sign = -1;
		++i;
	}
	int x = strlen(str);
	while (str[i] != '/' && i < x) {
		nominator = nominator * 10 + str[i] - (int)'0';
		++i;
	}
	if (i == x)
		denominator = 1;
	else {
		++i;
		if (str[i] == '-') {
			sign = -1;
			++i;
		}
		denominator = 0;
		while (i < x) {
			denominator = denominator * 10 + str[i] - (int)'0';
			++i;
		}
	}
	nominator *= sign;
	p = nominator;
	q = denominator;
	reduce();
}

Rational::Rational(const char *str) {
	assign(str);
}

Rational::Rational(const Rational &other) {
	this->p = other.p;
	this->q = other.q;
}

istream &operator >> (istream &is, Rational &rational) {
	char s[100];
	is >> s;
	rational.assign(s);
	return is;
}

ostream &operator << (ostream &os, const Rational &rational) {
	if (rational.q == 1)
		os << rational.p;
	else
		os << rational.p << '/' << rational.q;
	return os;
}

Rational operator + (const Rational &a, const Rational &b) {
	Rational res;
	res.p = a.p * b.q + a.q * b.p;
	res.q = a.q * b.q;
	res.reduce();
	return res;
}

Rational operator + (const Rational &a, const int &b) {
	return a + Rational(b);
}

Rational operator + (const int &a, const Rational &b) {
	return Rational(a) + b;
}

Rational operator - (const Rational &a, const Rational &b) {
	Rational res;
	res.p = a.p * b.q - a.q * b.p;
	res.q = a.q * b.q;
	res.reduce();
	return res;
}

Rational operator - (const Rational &a, const int &b) {
	return a - Rational(b);
}

Rational operator-(const int &a, const Rational &b) {
	return Rational(a) - b;
}

Rational operator * (const Rational &a, const Rational &b) {
	Rational res;
	res.p = a.p * b.p;
	res.q = a.q * b.q;
	res.reduce();
	return res;
}

Rational operator * (const Rational &a, const int &b) {
	return a * Rational(b);
}

Rational operator * (const int &a, const Rational &b) {
	return Rational(a) * b;
}

Rational operator / (const Rational &a, const Rational &b) {
	if (!b.p)
		throw RationalDivisionByZero();
	Rational res;
	int sign = b.p / abs(b.p);
	res.p = a.p * b.q * sign;
	res.q = a.q * abs(b.p);
	res.reduce();
	return res;
}

Rational operator / (const Rational &a, const int &b) {
	return a / Rational(b);
}

Rational operator / (const int &a, const Rational &b) {
	return Rational(a) / b;
}

Rational &Rational::operator = (const Rational &other) {
	this->p = other.p;
	this->q = other.q;
	return *this;
}

Rational &Rational::operator = (const int &other) {
	this->p = other;
	this->q = 1;
	return *this;
}

Rational &Rational::operator += (const Rational &other) {
	*this = *this + other;
	return *this;
}

Rational &Rational::operator += (const int &other) {
	*this = *this + other;
	return *this;
}

Rational &Rational::operator -= (const Rational &other) {
	*this = *this - other;
	return *this;
}

Rational &Rational::operator -= (const int &other) {
	*this = *this - other;
	return *this;
}

Rational &Rational::operator *= (const Rational &other) {
	*this = *this * other;
	return *this;
}

Rational &Rational::operator *= (const int &other) {
	*this = *this * other;
	return *this;
}

Rational &Rational::operator /= (const Rational &other) {
	*this = *this / other;
	return *this;
}

Rational &Rational::operator /= (const int &other) {
	*this = *this / other;
	return *this;
}

int comparator(const Rational &a, const Rational &b) {
	if (a.p * b.q > a.q * b.p)
		return 1;
	else if (a.p * b.q == a.q * b.p)
		return 0;
	else
		return -1;
}

bool operator > (const Rational &a, const Rational &b) {
	return comparator(a, b) == 1;
}

bool operator > (const Rational &a, const int &b) {
	return comparator(a, Rational(b)) == 1;
}

bool operator > (const int &a, const Rational &b) {
	return comparator(Rational(a), b) == 1;
}

bool operator >= (const Rational &a, const Rational &b) {
	return comparator(a, b) >= 0;
}

bool operator >= (const Rational &a, const int &b) {
	return comparator(a, Rational(b)) >= 0;
}

bool operator >= (const int &a, const Rational &b) {
	return comparator(Rational(a), b) >= 0;
}

bool operator < (const Rational &a, const Rational &b) {
	return comparator(a, b) == -1;
}

bool operator < (const Rational &a, const int &b) {
	return comparator(a, Rational(b)) == -1;
}

bool operator < (const int &a, const Rational &b) {
	return comparator(Rational(a), b) == -1;
}

bool operator <= (const Rational &a, const Rational &b) {
	return comparator(a, b) <= 0;
}

bool operator <= (const Rational &a, const int &b) {
	return comparator(a, Rational(b)) <= 0;
}

bool operator <= (const int &a, const Rational &b) {
	return comparator(Rational(a), b) <= 0;
}

bool operator == (const Rational &a, const Rational &b) {
	return !comparator(a, b);
}

bool operator == (const Rational &a, const int &b) {
	return !comparator(a, Rational(b));
}

bool operator == (const int &a, const Rational &b) {
	return !comparator(Rational(a), b);
}

bool operator != (const Rational &a, const Rational &b) {
	return comparator(b, a);
}

bool operator != (const Rational &a, const int &b) {
	return comparator(Rational(b), a);
}

bool operator != (const int &a, const Rational &b) {
	return comparator(Rational(a), b);
}


Rational operator - (const Rational &a) {
	Rational result(a);
	result.p = -a.p;
	return result;
}

Rational operator + (const Rational &a) {
	Rational result(a);
	return result;
}

Rational &Rational::operator ++ () {
	p += q;
	return *this;
}

Rational Rational::operator ++ (int) {
	Rational temp = *this;
	++*this;
	return temp;
}

Rational &Rational::operator -- () {
	p -= q;
	return *this;
}

Rational Rational::operator -- (int) {
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
	return 0;
}