#include <iostream>
#include <cmath>

double abs(double a) {
	if (a >= 0)
		return a;
	else
		return -a;
}

class Base;
class Point;
class Segment;
class Line;
class Ray;

class Vector {
private:
	double x;
	double y;
public:
	Vector();
	Vector(const double x, const double y);
	Vector(const Point &a, const Point &b);
	Vector(const Vector &);

	double get_x() const { return x; };
	double get_y() const { return y; };

	friend std::istream &operator >> (std::istream &, Vector &);
	friend std::ostream &operator<<(std::ostream &, const Vector &);

	friend double mod(const Vector&);
	Vector operator+(const Vector &);
	Vector operator-(const Vector &);
	double operator*(const Vector &);
	double vector_mult(const Vector &);
};

class Base {
public:
	virtual void replace(const Vector &) = 0;
	virtual bool contains_point(const Point &) const = 0;
	virtual bool crosses_segment(const Segment &) const = 0;
};

class Point : public Base {
private:
	double x;
	double y;
public:
	Point();
	Point(const double x, const double y);
	Point(const Point &);

	double get_x() const { return x; }
	double get_y() const { return y; }

	Point &operator=(const Point &);
	bool operator==(const Point &) const;
	double distance(const Point &) const;
	void replace(const Vector &);
	bool contains_point(const Point &) const;
	bool crosses_segment(const Segment &) const;
	friend std::ostream &operator<<(std::ostream &, const Point &);
	friend std::istream &operator >> (std::istream &, Point &);
};

class Segment : public Base {
private:
	Point first;
	Point last;
public:
	Segment();
	Segment(const Point &first, const Point &second);
	Segment(const Segment &);

	Point get_first() const { return first; }
	Point get_last() const { return last; }

	void replace(const Vector &);
	bool contains_point(const Point &) const;
	bool crosses_segment(const Segment &) const;
	double distance_point(const Point &that) const;
	double distance_segment(const Segment &that) const;
};

class Line : public Base {
	double a;
	double b;
	double c;
public:
	Line();
	Line(const double a, const double b, const double c);
	Line(const Point &, const Point &);
	Line(const Line &);
	Line &operator=(const Line &);

	void replace(const Vector &);
	bool contains_point(const Point &) const;
	bool crosses_segment(const Segment &) const;
	bool parallel(const Line &) const;
	Point line_intersection(const Line &) const;
	double distance_point(const Point &) const;
	double distance_line(const Line &) const;
	Vector direct_vector() const;
};

class Ray : public Base {
	Point start;
	Point lays_on_ray;
public:
	Ray();
	Ray(const Point &start, const Point &lays_on_ray);
	Ray(const Ray &);
	Ray &operator=(const Ray &);
	void replace(const Vector &);
	bool contains_point(const Point &) const;
	bool crosses_segment(const Segment &) const;
	double distance_point(const Point &) const;
};

/////////////////////////////////////////////////////////////////////////////////Vector

Vector::Vector() {
	this->x = 0;
	this->y = 0;
}

Vector::Vector(const double x, const double y) {
	this->x = x;
	this->y = y;
}

Vector::Vector(const Point &a, const Point &b) {
	x = b.get_x() - a.get_x();
	y = b.get_y() - a.get_y();
}

Vector::Vector(const Vector &that) {
	this->x = that.x;
	this->y = that.y;
}

std::istream &operator >> (std::istream &in, Vector &v) {
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

//////////////////////////////////////////////////////////////////////////////////////Point

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(const double x, const double y) {
	this->x = x;
	this->y = y;
}

Point::Point(const Point &that) {
	this->x = that.x;
	this->y = that.y;
}

Point &Point::operator=(const Point &that) {
	this->x = that.x;
	this->y = that.y;
	return *this;
}

bool Point::operator==(const Point &that) const {
	return this->x == that.x && this->y == that.y;
}

double Point::distance(const Point &that) const {
	return sqrt((that.x - this->x) * (that.x - this->x) + (that.y - this->y) * (that.y - this->y));
}

void Point::replace(const Vector &v) {
	this->x += v.get_x();
	this->y += v.get_y();
}

bool Point::contains_point(const Point &that) const {
	return *this == that;
}

bool Point::crosses_segment(const Segment &s) const {
	Vector directed_s(s.get_first(), s.get_last());
	Vector a(s.get_first(), *this);
	Vector b(s.get_last(), *this);
	return a.vector_mult(directed_s) == 0 && a * b <= 0;
}

std::istream &operator >> (std::istream &in, Point &p) {
	int x, y;
	in >> x >> y;
	p.x = x;
	p.y = y;
	return in;
}

std::ostream &operator<<(std::ostream &out, const Point &p) {
	out << p.x << ' ' << p.y;
	return out;
}

/////////////////////////////////////////////////////////////////////////Segment

Segment::Segment() {
	first = Point(0, 0);
	last = Point(0, 0);
}

Segment::Segment(const Point &first, const Point &last) {
	this->first = first;
	this->last = last;
}

Segment::Segment(const Segment &that) {
	this->first = that.first;
	this->last = that.last;
}

void Segment::replace(const Vector &v) {
	first.replace(v);
	last.replace(v);
}

bool Segment::contains_point(const Point &p) const {
	return p.crosses_segment(*this);
}

bool Segment::crosses_segment(const Segment &that) const {
	bool check1, check2, check3;
	Line this_line(this->get_first(), this->get_last());
	Line that_line(that.get_first(), that.get_last());
	check1 = this_line.crosses_segment(that);
	check2 = that_line.crosses_segment(*this);
	double this_min_x = this->first.get_x() <= this->last.get_x() ? this->first.get_x() : this->last.get_x();
	double this_max_x = this->first.get_x()> this->last.get_x() ? this->first.get_x() : this->last.get_x();
	double this_min_y = this->first.get_y() <= this->last.get_y() ? this->first.get_y() : this->last.get_y();
	double this_max_y = this->first.get_y()> this->last.get_y() ? this->first.get_y() : this->last.get_y();
	double that_min_x = that.first.get_x() <= that.last.get_x() ? that.first.get_x() : that.last.get_x();
	double that_max_x = that.first.get_x()> that.last.get_x() ? that.first.get_x() : that.last.get_x();
	double that_min_y = that.first.get_y() <= that.last.get_y() ? that.first.get_y() : that.last.get_y();
	double that_max_y = that.first.get_y()> that.last.get_y() ? that.first.get_y() : that.last.get_y();
	check3 = this_min_x <= that_max_x && this_max_x >= that_min_x && this_min_y <= that_max_y && this_max_y >= that_min_y;
	return check1 && check2 && check3;
}

double Segment::distance_point(const Point &p) const {
	Ray directed(first, last);
	Ray nodirected(last, first);
	return (directed.distance_point(p) > nodirected.distance_point(p) ? directed.distance_point(p) : nodirected.distance_point(p));
}

double Segment::distance_segment(const Segment &that) const {
	if (crosses_segment(that))
		return 0;
	else {
		double d1 = this->distance_point(that.first);
		double min_d = d1;
		double d2 = this->distance_point(that.last);
		if (d2 < min_d)
			min_d = d2;
		double d3 = that.distance_point(this->first);
		if (d3 < min_d)
			min_d = d3;
		double d4 = that.distance_point(this->last);
		if (d4 < min_d)
			min_d = d4;
		return min_d;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////Line

Line::Line() {
	a = 0;
	b = 0;
	c = 0;
}

Line::Line(const double a, const double b, const double c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Line::Line(const Point &p1, const Point &p2) {
	a = p1.get_y() - p2.get_y();
	b = p2.get_x() - p1.get_x();
	c = p1.get_x() * p2.get_y() - p1.get_y() * p2.get_x();
}

Line::Line(const Line &that) {
	this->a = that.a;
	this->b = that.b;
	this->c = that.c;
}

Line &Line::operator=(const Line &that) {
	this->a = that.a;
	this->b = that.b;
	this->c = that.c;
	return *this;
}

void Line::replace(const Vector &v) {
	this->c += this->a * v.get_x() + this->b * v.get_y();
}

bool Line::contains_point(const Point &p) const {
	return (this->a * p.get_x() + this->b * p.get_y() + this->c) == 0;
}

bool Line::crosses_segment(const Segment &s) const {
	return (a * s.get_first().get_x() + b * s.get_first().get_y() + c) * (a * s.get_last().get_x() + b * s.get_last().get_y() + c) <= 0;
}

bool Line::parallel(const Line &that) const {
	return (this->a * that.b - this->b * that.a) == 0;
}

Point Line::line_intersection(const Line &that) const {
	Point result((this->b * that.c - this->c * that.b) / (this->a * that.b - this->b * that.a), (this->c * that.a - this->a * that.c) / (this->a * that.b - this->b * that.a));
	return result;
}

double Line::distance_point(const Point &p) const {
	return abs(a * p.get_x() + b * p.get_y() + c) / sqrt(a * a + b * b);
}

double Line::distance_line(const Line &that) const {
	if (!parallel(that))
		return 0;
	else {
		Point p;
		if (that.a != 0) {
			p = Point(-1 * that.c / that.a, 0);
		}
		else {
			p = Point(0, -1 * that.c / that.b);
		}
		return distance_point(p);
	}
}

Vector Line::direct_vector() const {
	Vector result(-1 * b, a);
	return result;
}

///////////////////////////////////////////////////////////////////////////////Ray

Ray::Ray() {
	start = Point(0, 0);
	lays_on_ray = Point(0, 0);
}

Ray::Ray(const Point &start, const Point &lays_on_ray) {
	this->start = start;
	this->lays_on_ray = lays_on_ray;
}

Ray::Ray(const Ray &that) {
	this->start = that.start;
	this->lays_on_ray = that.lays_on_ray;
}

Ray &Ray::operator=(const Ray &that) {
	this->start = that.start;
	this->lays_on_ray = that.lays_on_ray;
	return *this;
}

void Ray::replace(const Vector &v) {
	start.replace(v);
	lays_on_ray.replace(v);
}

bool Ray::contains_point(const Point &p) const {
	Vector strict_ray(start, lays_on_ray);
	Vector start_p(start, p);
	return start_p.vector_mult(strict_ray) == 0 && start_p * strict_ray >= 0;
}

bool Ray::crosses_segment(const Segment &s) const {
	Line line(start, lays_on_ray);
	if (line.contains_point(s.get_first()) || line.contains_point(s.get_last())) {
		return true;
	}
	else {
		Line start_first(start, s.get_first());
		Segment last_ray_on_line(s.get_last(), lays_on_ray);
		return line.crosses_segment(s) && !(start_first.crosses_segment(last_ray_on_line));
	}
}

double Ray::distance_point(const Point &p) const {
	Vector strict_ray(start, lays_on_ray);
	Vector start_p(start, p);
	Line line(start, lays_on_ray);
	if (strict_ray * start_p >= 0)
		return line.distance_point(p);
	else
		return mod(start_p);
}

int main() {
	Point A, B, C, D;
	std::cin >> A >> B >> C >> D;
	Segment AB(A, B), CD(C, D);
	std::cout.setf(std::ios::fixed);
	std::cout.precision(6);
	std::cout << AB.distance_segment(CD) << '\n';
	//system("pause");
	return 0;
}