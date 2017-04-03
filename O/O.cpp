#include <cstdlib>
#include <cstring>
#include <iostream>


class BigInt {
private:
	static const int BASE = 10;
	static const int DIGIT_COUNT = 1;
	int size;
	int *values;
	bool is_positive;

	void set_size(int);
	int real_size() const;
	void assign_str(const char *s);
	friend BigInt abs_mult(const BigInt &, const BigInt &);
public:
	BigInt();
	BigInt(const BigInt &);
	~BigInt();

	friend std::ostream &operator<<(std::ostream &, const BigInt &);
	friend std::istream &operator>>(std::istream &, BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);

};

void BigInt::set_size(const int size) {
	//if (size > MAX_SIZE)
	//throw BigIntegerOverflow();
	this->size = size;
	this->values = new int[this->size];
	for (int i = 0; i < this->size; ++i)
		this->values[i] = 0;
}

int BigInt::real_size() const {
	int result = size - 1;
	while (values[result] == 0 && result >= 0) {
		--result;
	}
	return result + 1;
}

void BigInt::assign_str(const char *s) {
	int len_s = strlen(s);
	int k = 0;
	if (s[0] == '-') {
		this->is_positive = false;
		--len_s;
		k = 1;
	}
	else
		this->is_positive = true;
	set_size(len_s / DIGIT_COUNT + (len_s % DIGIT_COUNT != 0));
	for (int i = 0; i < this->size; i++) {
		int value = 0;
		for (int j = len_s - (i + 1) * DIGIT_COUNT + k; j < len_s - i * DIGIT_COUNT + k; ++j) {
			if (j >= 0 && s[j] != '-') {
				value = (value * 10) + (s[j] - 48);
			}
		}
		this->values[i] = value;
	}
}

BigInt::BigInt() {
	size = 0;
	is_positive = true;
}

BigInt::BigInt(const BigInt &that) {
	this->is_positive = that.is_positive;
	set_size(that.size);
	std::memcpy(this->values, that.values, size * sizeof(int));
}

BigInt::~BigInt() {
	delete[] values;
}

std::istream &operator >> (std::istream &in, BigInt &value) {
	char s[10005];
	in >> s;
	value.assign_str(s);
	return in;
}

std::ostream &operator<<(std::ostream &out, const BigInt &value) {
	int new_size = value.real_size();
	if (new_size == 0) {
		out << '0';
	}
	else {
		if (!value.is_positive) {
			out << '-';
		}
		for (int i = new_size - 1; i >= 0; i--) {
			int d = value.BASE / 10;
			int &v = value.values[i];
			while (d > v + 1 && i < new_size - 1) {
				out << '0';
				d /= 10;
			}
			out << v;
		}
	}
	return out;
}

BigInt abs_mult(const BigInt &a, const BigInt &b) {
	BigInt result;
	result.set_size(a.size + b.size);
	long long value;
	int extra;
	for (int i = 0; i < a.size; ++i) {
		extra = 0;
		for (int j = 0; j < b.size || extra > 0; ++j) {
			value = result.values[i + j] + extra;
			if (j < b.size)
				value += a.values[i] * b.values[j];
			result.values[i + j] = value % result.BASE;
			extra = value / result.BASE;
		}
	}
	return result;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
	BigInt result = abs_mult(a, b);
	if (a.is_positive + b.is_positive == 1)
		result.is_positive = false;
	return result;
}

int main() {
	BigInt a, b;
	std::cin >> a >> b;
	std::cout << a * b;
	//system("pause");
	return 0;
}