#include <iostream>
#include <cmath>

class Vector {
private:
	double x;
	double y;
public:
	Vector();
	Vector(const double x, const double y);
	Vector(const Vector &);
	double get_x() const;
	double get_y() const;

	friend std::istream &operator >> (std::istream &, Vector &);
	friend std::ostream &operator<<(std::ostream &, const Vector &);

	friend double mod(const Vector&);
	Vector operator+(const Vector &);
	Vector operator-(const Vector &);
	double operator*(const Vector &);
	double vector_mult(const Vector &);
};

Vector::Vector() {
	this->x = 0;
	this->y = 0;
}

Vector::Vector(const double x, const double y) {
	this->x = x;
	this->y = y;
}

Vector::Vector(const Vector &that) {
	this->x = that.x;
	this->y = that.y;
}

double Vector::get_x() const {
	return x;
}

double Vector::get_y() const {
	return y;
}

std::istream &operator>>(std::istream &in, Vector &v) {
	double x, y;
	in >> x >> y;
	v.x = x;
	v.y = y;
	return in;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
	out << v.x << ' ' << v.y;
	return out;
}

double mod(const Vector &v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector Vector::operator+(const Vector &that) {
	Vector result;
	result.x = this->x + that.x;
	result.y = this->y + that.y;
	return result;
}

Vector Vector::operator-(const Vector &that) {
	Vector result;
	result.x = this->x - that.x;
	result.y = this->y - that.y;
	return result;
}

double Vector::operator*(const Vector &that) {
	return this->x * that.x + this->y * that.y;
}

double Vector::vector_mult(const Vector &that) {
	return this->x * that.y - this->y * that.x;
}

double abs(double value) {
	if (value >= 0)
		return value;
	else
		return -value;
}

int main() {
	Vector a, a1, a2, b, b1, b2;
	std::cin >> a1 >> a2;
	std::cin >> b1 >> b2;
	a = a2 - a1;
	b = b2 - b1;
	std::cout.setf(std::ios::fixed);
	std::cout.precision(6);
	std::cout << mod(a) << ' ' << mod(b) << '\n';
	std::cout << a + b << '\n';
	std::cout << a * b << ' ' << a.vector_mult(b) << '\n';
	std::cout << abs(a.vector_mult(b)) / 2 << '\n';
	//system("pause");
	return 0;
}