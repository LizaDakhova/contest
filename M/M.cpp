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
	friend bool abs_a_bigger_b(const BigInt &, const BigInt &); // check if a >= b
	friend BigInt abs_sum(const BigInt &, const BigInt &);
	friend BigInt abs_sub(const BigInt &, const BigInt &);
public:
	BigInt();
	BigInt(const BigInt &);
	~BigInt();

	friend std::ostream &operator<<(std::ostream &, const BigInt &);
	friend std::istream &operator>>(std::istream &, BigInt &);

	friend BigInt operator+(const BigInt &, const BigInt &);
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

bool abs_a_bigger_b(const BigInt &a, const BigInt &b) {
	int a_size = a.real_size();
	int b_size = b.real_size();
	if (a_size > b_size)
		return true;
	else if (a_size < b_size)
		return false;
	else {
		for (int i = a_size - 1; i >= 0; --i) {
			if (a.values[i] > b.values[i])
				return true;
			else if (a.values[i] < b.values[i])
				return false;
		}
		return true;
	}
}

BigInt abs_sum(const BigInt &a, const BigInt &b) {
	BigInt result;
	int cap = (a.size >= b.size ? a.size : b.size) + 1;
	result.set_size(cap);
	int value;
	int extra = 0;
	for (int i = 0; i < cap; ++i) {
		value = 0;
		if (i < a.size)
			value += a.values[i];
		if (i < b.size)
			value += b.values[i];
		result.values[i] = (value + extra) % result.BASE;
		extra = (value + extra) / result.BASE;
	} 
	return result;
}

BigInt abs_sub(const BigInt &a, const BigInt &b) {
	BigInt result;
	int cap = a.size;
	result.set_size(cap);
	int value;
	int lack = 0;
	for (int i = 0; i < cap; ++i) {
		value = a.values[i];
		if (i < b.size)
			value -= b.values[i];
		value -= lack;
		if (value < 0) {
			result.values[i] = result.BASE + value;
			lack = 1;
		}
		else {
			result.values[i] = value;
			lack = 0;
		}
	}
	return result;
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

BigInt operator+(const BigInt &a, const BigInt &b) {
	if (a.is_positive + b.is_positive != 1) {
		BigInt result = abs_sum(a, b);
		result.is_positive = a.is_positive;
		return result;
	}
	else {
		if (abs_a_bigger_b(a, b)) {
			BigInt result = abs_sub(a, b);
			result.is_positive = a.is_positive;
			return result;
		}
		else {
			BigInt result = abs_sub(b, a);
			result.is_positive = b.is_positive;
			return result;
		}
	}
}

int main() {
	BigInt a, b;
	std::cin >> a >> b;
	std::cout << a + b;
	//system("pause");
	return 0;
}