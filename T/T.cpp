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

class MatrixWrongSizeError : logic_error {
public:
	MatrixWrongSizeError();
};

MatrixWrongSizeError::MatrixWrongSizeError() : logic_error("Error") {}

class MatrixIndexError : logic_error {
public:
	MatrixIndexError();
};

MatrixIndexError::MatrixIndexError() : logic_error("Error") {}

class MatrixIsDegenerateError : logic_error {
public:
	MatrixIsDegenerateError();
};

MatrixIsDegenerateError::MatrixIsDegenerateError() : logic_error("Error") {}

////////////////////////////////////////////////////////////////////////////////////Rational

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

////////////////////////////////////////////////////////////////////////////////////Matrix

template <typename T> // надо не забыть про класс по умолчанию
class Matrix {
protected:
	int rows;
	int columns;
	T **values;
	void set_size(const int rows, const int columns);
public:
	Matrix();
	Matrix(const int rows, const int columns);
	Matrix(const Matrix<T> &);
	~Matrix();

	int getRowsNumber() const { return rows; }
	int getColumnsNumber() const { return columns; }
	T operator()(const int row, const int column) const;

	template <typename T1>
	friend istream &operator >> (istream &, Matrix<T1> &);
	template <typename T1>
	friend ostream &operator << (ostream &, const Matrix<T1> &);
	
	virtual Matrix<T> &operator=(const Matrix<T> &);
	Matrix<T> operator+(const Matrix<T> &) const;
	Matrix<T> operator-(const Matrix<T> &) const;
	Matrix<T> operator*(const Matrix<T> &) const;
	Matrix<T> operator*(const T &) const;
	template <typename T1> friend Matrix<T1> operator*(const T1, const Matrix<T1> &);
	Matrix<T> operator/(const T &) const;

	Matrix<T> &operator+=(const Matrix<T> &);
	Matrix<T> &operator-=(const Matrix<T> &);
	Matrix<T> &operator*=(const Matrix<T> &);
	Matrix<T> &operator*=(const T);
	Matrix<T> &operator/=(const T);
	Matrix<T> getTransposed() const;
	Matrix<T> &transpose();
};

template <typename T>
void Matrix<T>::set_size(const int rows, const int columns) {
	this->rows = rows;
	this->columns = columns;
	this->values = new T*[rows];
	for (int i = 0; i < rows; ++i) {
		this->values[i] = new T[columns];
		for (int j = 0; j < columns; ++j)
			this->values[i][j] = 0;
	}
}

template <typename T>
Matrix<T>::Matrix() {
	set_size(1, 1);
}

template <typename T>
Matrix<T>::Matrix(const int rows, const int columns) {
	set_size(rows, columns);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &that) {
	this->rows = that.rows;
	this->columns = that.columns;
	this->values = new T*[this->rows];
	for (int i = 0; i < this->rows; ++i) {
		this->values[i] = new T[this->columns];
		for (int j = 0; j < this->columns; ++j)
			this->values[i][j] = that.values[i][j];
	}
}

template <typename T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < rows; ++i)
		delete[] values[i];
	delete[] values;
}

template <typename T>
T Matrix<T>::operator()(const int row, const int column) const{
	if (row >= rows || column >= columns)
		throw MatrixIndexError();
	return values[row][column];
}

template <typename T1>
istream &operator >> (istream &in, Matrix<T1> &m) {
	for (int i = 0; i < m.rows; ++i)
		for (int j = 0; j < m.columns; ++j)
			in >> m.values[i][j];
	return in;
}

template <typename T1>
ostream &operator << (ostream &out, const Matrix<T1> &m) {
	for (int i = 0; i < m.rows; ++i) {
		for (int j = 0; j < m.columns; ++j)
			out << m.values[i][j] << ' ';
		out << '\n';
	}
	return out;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &that) {
	if (this != &that) {
		this->rows = that.rows;
		this->columns = that.columns;
		this->values = new T*[this->rows];
		for (int i = 0; i < this->rows; ++i) {
			this->values[i] = new T[this->columns];
			for (int j = 0; j < this->columns; ++j)
				this->values[i][j] = that.values[i][j];
		}
	}
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &that) const {
	if (this->rows != that.rows || this->columns != that.columns)
		throw MatrixWrongSizeError();
	Matrix<T> result(this->rows, this->columns);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->columns; ++j)
			result.values[i][j] = this->values[i][j] + that.values[i][j];
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &that) const {
	if (this->rows != that.rows || this->columns != that.columns)
		throw MatrixWrongSizeError();
	Matrix<T> result(this->rows, this->columns);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->columns; ++j)
			result.values[i][j] = this->values[i][j] - that.values[i][j];
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &that) const {
	if (this->columns != that.rows)
		throw MatrixWrongSizeError();
	Matrix<T> result(this->rows, that.columns);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < that.columns; ++j)
			for (int k = 0; k < this->columns; ++k)
				result.values[i][j] += this->values[i][k] * that.values[k][j];
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &t) const {
	Matrix<T> result = *this;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			result.values[i][j] *= t;
	return result;
}

template <typename T1>
Matrix<T1> operator*(const T1 t, const Matrix<T1> &m) {
	return m * t;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T &t) const {
	Matrix<T> result = *this;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			result.values[i][j] /= t;
	return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &that) {
	*this = *this + that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &that) {
	*this = *this - that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &that) {
	*this = *this * that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const T t) {
	*this = *this * t;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const T t) {
	*this = *this / t;
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::getTransposed() const{
	Matrix<T> result(this->columns, this->rows);
	for (int i = 0; i < this->columns; ++i)
		for (int j = 0; j < this->rows; ++j) 
			result.values[i][j] = this->values[j][i];
	return result;
}

template <typename T>
Matrix<T> &Matrix<T>::transpose() {
	*this = this->getTransposed();
	return *this;
}

template <typename T>
class SquareMatrix : public Matrix<T> {
private:
	SquareMatrix<T> my_minor(const int without_row, const int without_col) const;
public:
	SquareMatrix(const int);
	SquareMatrix(const Matrix<T> &);
	SquareMatrix(const SquareMatrix<T> &);

	int getSize() const;

	SquareMatrix<T> operator+(const SquareMatrix<T> &) const;
	SquareMatrix<T> operator-(const SquareMatrix<T> &) const;
	SquareMatrix<T> operator*(const SquareMatrix<T> &) const;
	Matrix<T> operator*(const Matrix<T> &) const;
	SquareMatrix<T> operator*(const T) const;
	template<typename T1> friend SquareMatrix<T1> operator*(const T1, const SquareMatrix<T1> &);
	SquareMatrix<T> operator/(const T) const;

	SquareMatrix<T> operator=(const SquareMatrix<T> &that);
	SquareMatrix<T> &operator+=(const SquareMatrix<T> &);
	SquareMatrix<T> &operator-=(const SquareMatrix<T> &);
	SquareMatrix<T> &operator*=(const SquareMatrix<T> &);
	Matrix<T> &operator*=(const Matrix<T> &);
	SquareMatrix<T> &operator*=(const T);
	SquareMatrix<T> &operator/=(const T);

	SquareMatrix<T> getTransposed() const;
	SquareMatrix<T> &transpose();
	T getDeterminant() const;
	SquareMatrix<T> getInverse() const;
	SquareMatrix<T> &invert();
	T getTrace() const;
};

template <typename T>
SquareMatrix<T> SquareMatrix<T>::my_minor(const int without_row, const int without_column) const {
	SquareMatrix<T> result(getSize() - 1);
	for (int row = 0; row < getSize(); ++row)
		for (int column = 0; column < getSize(); ++column) 
			if (row != without_row && column != without_column) {
				int i = row;
				int j = column;
				if (row > without_row)
					i = row - 1;
				if (column > without_column) 
					j = column - 1;
				result.values[i][j] = Matrix<T>::values[row][column];
		}
	return result;
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const int size) {
	Matrix<T>::set_size(size, size);
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T> &that) {
	this->rows = that.rows;
	this->columns = that.columns;
	this->values = new T*[this->rows];
	for (int i = 0; i < this->rows; ++i) {
		this->values[i] = new T[this->columns];
		for (int j = 0; j < this->columns; ++j)
			this->values[i][j] = that.values[i][j];
	}
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const Matrix<T> &that) {
	if (that.getRowsNumber() != that.getColumnsNumber())
		throw MatrixWrongSizeError();
	this->rows = that.getRowsNumber();
	this->columns = that.getColumnsNumber();
	this->values = new T*[this->rows];
	for (int i = 0; i < this->rows; ++i) {
		this->values[i] = new T[this->columns];
		for (int j = 0; j < this->columns; ++j)
			this->values[i][j] = that(i, j);
	}
}

template <typename T>
int SquareMatrix<T>::getSize() const{
	return Matrix<T>::getRowsNumber();
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T> &that) const {
	return Matrix<T>::operator+(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix<T> &that) const {
	return Matrix<T>::operator-(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T> &that) const {
	return Matrix<T>::operator*(that);
}

template <typename T>
Matrix<T> SquareMatrix<T>::operator*(const Matrix<T> &that) const {
	return Matrix<T>::operator*(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T t) const {
	return Matrix<T>::operator*(t);
}

template<typename T1> 
SquareMatrix<T1> operator*(const T1 t, const SquareMatrix<T1> &m) {
	return m * t;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator/(const T t) const {
	return Matrix<T>::operator/(t);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator=(const SquareMatrix<T> &that) {
	if (this != &that) {
		this->rows = that.rows;
		this->columns = that.columns;
		this->values = new T*[this->rows];
		for (int i = 0; i < this->rows; ++i) {
			this->values[i] = new T[this->columns];
			for (int j = 0; j < this->columns; ++j)
				this->values[i][j] = that.values[i][j];
		}
	}
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator+=(const SquareMatrix<T> &that) {
	*this = *this + that;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator-=(const SquareMatrix<T> &that) {
	*this = *this - that;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const SquareMatrix<T> &that) {
	*this = *this * that;
	return *this;
}

template <typename T>
Matrix<T> &SquareMatrix<T>::operator*=(const Matrix<T> &that) {
	*this = *this * that;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const T t) {
	*this = *this * t;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator/=(const T t) {
	*this = *this / t;
	return *this;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::getTransposed() const {
	return Matrix<T>::getTransposed();
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::transpose() {
	*this = getTransposed();
	return *this;
}

template <typename T>
T SquareMatrix<T>::getDeterminant() const {
	SquareMatrix<T> copy = *this;
	T det = T(1);
	bool flag = true;
	for (int column = 0; flag && column < getSize(); ++column) { // идем по столбцам
		int early_row = column;
		int row = column;
		while (row < copy.getSize() && copy.values[row][column] == T(0)) { //ищем первый ненулевой символ в столбце
			++row;
		}
		if (row == copy.getSize()) {
			flag = false;
		}
		else {
			if (row != early_row) {
				for (int j = 0; j < getSize(); ++j)
					swap(copy.values[row][j], copy.values[early_row][j]);
				det *= -1;
			}
			for (int i = early_row + 1; i < copy.getSize(); ++i) {
				T t = copy.values[i][column] / copy.values[early_row][column];
				for (int j = column; j < getSize(); ++j) 
					copy.values[i][j] -= copy.values[early_row][j] * t;
			}
		}
		det *= copy.values[early_row][column];
	}
	if (!flag) {
		det = T(0);
	}
	return det;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse() const {
	if (getDeterminant() == T(0))
		throw MatrixIsDegenerateError();
	SquareMatrix<T> result(getSize());
	T det = getDeterminant();
	for (int i = 0; i < getSize(); ++i) 
		for (int j = 0; j < getSize(); ++j) {
			result.values[i][j] = my_minor(i, j).getDeterminant() / det;
			if ((i + j) % 2)
				result.values[i][j] *= -1;
		}
	result.transpose();
	return result;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::invert() {
	*this = getInverse();
	return *this;
}

template <typename T>
T SquareMatrix<T>::getTrace() const {
	T sum = T(0);
	for (int i = 0; i < getSize(); ++i)
		sum += Matrix<T>::values[i][i];
	return sum;
}

int main() {
	int m, n, p, q;
	cin >> m >> n >> p >> q;

	Matrix<int> A(m, n), B(p, q);
	cin >> A >> B;

	A = A;
	try {
		cout << A + B * 2 - m * A << endl;
		cout << (A -= B += A *= 2) << endl;
		cout << (((A -= B) += A) *= 2) << endl;
	}
	catch (const MatrixWrongSizeError&) {
		cout << "A and B are of different size." << endl;
	}
	B = A;
	cout << B << endl;

	Rational r;
	cin >> r;
	Matrix<Rational> C(m, n), D(p, q);
	cin >> C >> D;
	try {
		cout << C * D << endl;
		cout << (C *= D) << endl;
		cout << C << endl;
	}
	catch (const MatrixWrongSizeError&) {
		cout << "C and D have not appropriate sizes for multiplication." << endl;
	}
	cout << C.getTransposed() * (r * C) << endl;
	cout << C.transpose() << endl;
	cout << C << endl;

	SquareMatrix<Rational> S(m);
	cin >> S;
	SquareMatrix<Rational> P(S);
	const SquareMatrix<Rational>& rS = S;
	cout << rS.getSize() << ' ' << rS.getDeterminant() << ' ' << rS.getTrace() << endl;
	cout << (S = S) * (S + rS) << endl;
	cout << (S *= S) << endl;
	C.transpose();
	cout << rS * C << endl;
	cout << S << endl;
	S = P;
	cout << (Rational(1, 2) * S).getDeterminant() << endl;
	try {
		cout << rS(0, 0) << endl;
		(S(0, 0) *= 2) /= 2;
		cout << rS(0, m) << endl;
	}
	catch (const MatrixIndexError&) {
		cout << "Index out of range." << endl;
	}
	cout << rS.getTransposed() << endl;
	try {
		cout << rS.getInverse() << endl;
		cout << S.invert().getTransposed().getDeterminant() << endl;
		cout << S << endl;
	}
	catch (const MatrixIsDegenerateError&) {
		cout << "Cannot inverse S." << endl;
	}
	//system("pause");
	return 0;
}