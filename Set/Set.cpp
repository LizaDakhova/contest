#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;

template <typename T>
class Set {
private:
	int	size;
	T *values;
	void resize();
	bool be_in(T) const;
	void print();
public:
	Set();
	Set(int size);
	Set(int size, T a, ...);
	Set(const Set<T> &);
	~Set();
	Set<T> &operator=(const Set<T> &);
	Set<T> operator+(const Set<T> &) const;
	Set<T> operator*(const Set<T> &) const;
	Set<T> operator-(const Set<T> &) const;
	Set<T> &operator >> (const T);
	template <typename C> friend ostream &operator << (ostream &out, const Set<C> &set);

};

template <typename T>
void Set<T>::resize() {
	T *result = new T[size + 1];
	for (int i = 0; i < size; ++i)
		result[i] = values[i];
	++size;
	delete[] values;
	values = result;
}

template <typename T>
bool Set<T>::be_in(T value) const{
	bool result = false;
	for (int i = 0; i < this->size && !result; ++i)
		if (value == this->values[i])
			result = true;
	return result;
}

template <typename T>
void Set<T>::print() {
	cout << "size is " << size << " values are ";
	for (int i = 0; i < size; ++i)
		cout << values[i] << ' ';
	cout << endl;
}

template <typename T>
Set<T>::Set() {
	size = 0;
}

template <typename T>
Set<T>::Set(int size) {
	this->size = size;
	this->values = new T[this->size];
}

template <typename T>
Set<T>::Set(int size, T a, ...) {
	this->size = size;
	this->values = new T[this->size];
	T *temp = &a;
	for (int i = 0; i < this->size; ++i) {
		this->values[i] = *temp;
		++temp;
	}
}

template <typename T>
Set<T>::Set(const Set<T> &that) {
	this->size = that.size;
	this->values = new T[this->size];
	for (int i = 0; i < this->size; ++i)
		this->values[i] = that.values[i];
}

template <typename T>
Set<T>::~Set() {
	delete[] values;
}

template <typename T>
Set<T> &Set<T>::operator=(const Set<T> &that) {
	if (this->size == 0)
		this->values = new T[that.size];
	this->size = that.size;
	for (int i = 0; i < this->size; ++i)
		this->values[i] = that.values[i];
	return *this;
}

template <typename T>
Set<T> Set<T>::operator+(const Set<T> &that) const {
	Set<T> result(this->size + that.size);
	int real_size = this->size;
	for (int i = 0; i < result.size; ++i)
		if (i < this->size)
			result.values[i] = this->values[i];
		else if (!this->be_in(that.values[i - this->size])) {
			result.values[real_size] = that.values[i - this->size];
			real_size += 1;
		}
	result.size = real_size;
	return result;
}

template <typename T>
Set<T> Set<T>::operator*(const Set<T> &that) const {
	Set<T> result(this->size);
	int real_size = 0;
	for (int i = 0; i < that.size; ++i)
		if (this->be_in(that.values[i])) {
			result.values[real_size] = this->values[i];
			++real_size;
		}
	result.size = real_size;
	return result;
}


template <typename T>
Set<T> Set<T>::operator-(const Set<T> &that) const {
	Set<T> result(this->size);
	int real_size = 0;
	for (int i = 0; i < this->size; ++i)
		if (!this->be_in(that.values[i])) {
			result.values[real_size] = this->values[i];
			++real_size;
		}
	result.size = real_size;
	return result;
}

template <typename T>
Set<T> &Set<T>::operator >> (const T a) {
	resize();
	values[size - 1] = a;
	return *this;
}

template <typename C>
ostream &operator << (ostream &out, const Set<C> &set) {
	for (int i = 0; i < set.size; ++i)
		out << set.values[i] << ' ';
	return out;
}


int main() {
	Set<int> set1;
	set1 >> 1 >> 3;
	cout << "set1: " << set1 << endl;
	Set<int> set2(2, 1, 4);
	cout << "set2: " << set2 << endl;
	cout << "set1 + set2: " << set1 + set2 << endl << "set2 - set1: " << set2 - set1 << endl << "set1 * set2: " << set1 * set2 << endl;
	system("pause");
	return 0;
}
