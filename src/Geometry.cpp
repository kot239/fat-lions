//#include "World.hpp"
#include "../include/Geometry.hpp"
#include "../include/World.hpp"

#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

namespace world {

const double eps = 1e-6;

//Point

Point::Point() {
	x_ = abs(rand()) % X_FIELD_SIZE;
	y_ = abs(rand()) % Y_FIELD_SIZE;
}

Point::Point(double x, double y) : x_(x), y_(y) {}

Point::Point(const Point &other) : x_(other.x_), y_(other.y_) {}

Point& Point::operator=(const Point &other) {
	x_ = other.x_;
	y_ = other.y_;
	return *this;
}

Point &Point::operator+=(const Vector &v) {
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}

Point &Point::operator+=(const Point &other) {
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}

bool Point::operator==(const Point &point) {
	return (abs(x_ - point.x_) < eps && abs(y_ - point.y_) < eps);
}

Point Point::operator+(const Vector &v) const {
	Point cur(*this);
	cur += v;
	return cur;
}

Point Point::operator+(const Point &other) const {
	Point cur(*this);
	cur += other;
	return cur;
}

Vector Point::operator-(const Point &other) const {
	Vector cur;
	cur.x_ = x_ - other.x_;
	cur.y_ = y_ - other.y_;
	return cur;
}

//Point
//Vector

Vector::Vector(double x, double y) : x_(x), y_(y) {}

Vector::Vector(const Point &a, const Point &b) {
	x_ = b.x_ - a.x_;
	y_ = b.y_ - a.y_;
}

Vector::Vector(const Vector &other) : x_(other.x_), y_(other.y_) {}

void Vector::normalize() {
 //   assert(!(len() < eps));
    *this *=  ((double)(1) / len());
}

Vector Vector::operator*(const double val) {
	Vector cur(*this);
	cur *= val;
	return cur;
}

Vector &Vector::operator*=(const double val) {
    x_ *= val;
    y_ *= val;
    return *this;
}

Vector &Vector::operator+=(const Vector &v) {
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}

double Vector::len() const {
	return std::sqrt(x_ * x_ + y_ * y_);
}

//Vector 
//Segment 
Segment::Segment(const Point &a, const Point &b) : a_(a), b_(b) {}

//Segment

double coord_scalar_product(const Vector &a, const Vector &b) {
	//std::cerr << "vc" << a.x_ << " " << b.x_ << " " << a.y_ << " " << b.y_ << " ! ";
	return a.x_ * b.x_ + a.y_ * b.y_;
}

//Angle
Angle::Angle(const Vector &a, const Vector &b) {
	//::cerr << coord_scalar_product(a, b) << " =prod ";
	phi = std::acos(coord_scalar_product(a, b) / a.len() / b.len());
}

Angle::Angle(const Vector &a) { //polar
	*this = Angle(a, Vector(1, 0));
}

bool Angle::operator<(const Angle &other) const {
	return phi + eps < other.phi;
}
bool Angle::operator==(const Angle &other) const {
	return abs(phi - other.phi) < eps;
}

Angle &Angle::operator=(const Angle &other) {
	phi = other.phi;
	return *this;
}

//Angle

//Polygon

double cross_product(const Vector &a, const Vector &b) {
	return a.len() * b.len() * std::sin(Angle(a, b).phi);
}

int get_sign(double val) {
	if (val + eps < 0) {
		return -1;
	}
	if (val - eps > 0) {
		return 1;
	}
	return 0;
}

bool point_in_polygon(const Point &point, const Polygon &polygon) { 
	size_t n = polygon.coord_.size();
	int sign = 0;
	for (size_t i = 0; i < n; ++i) {
		size_t next = i + 1;
		if (n == next) {
			next = 0;
		}
		int cur_sign = get_sign(cross_product(Vector(polygon.coord_[i], polygon.coord_[next]), Vector(polygon.coord_[i], point)));
		if (sign == 0 && cur_sign != 0) {
			sign = cur_sign;
		}
		if (sign == cur_sign || cur_sign == 0) {
			continue;
		}
		return false;
	}
	return true;
}

double oriented_area(const Point &a, const Point &b, const Point &c) {
	return (b.x_ - a.x_) * (c.y_ - a.y_) - (b.y_ - a.y_) * (c.x_ - a.x_);
}

double rotate(const Point &a, const Point &b, const Point &c) {
	return (b.x_ - a.x_) * (c.y_ - b.y_) - (b.y_ - a.y_) * (c.x_ - b.x_);
}

std::vector<Point> convex_hull(std::vector<Point> &v) { //gift wrapping algo
	auto trash = v;
	size_t n = v.size();
	assert(n > 2);
	for (size_t i = 1; i < n; ++i) {
		if (v[i].x_ < v[0].x_) {
			swap(v[0], v[i]);
		}
	}

	std::vector<Point> result = {v[0]};
	v.push_back(v[0]);
	size_t ind = 0;
	while (true) {
		++ind;
		for (size_t i = ind + 1; i <= n; ++i) {
			if (rotate(result.back(), v[ind], v[i]) < 0) {
				swap(v[ind], v[i]);
			}
		}
		if (v[ind] == result.front()) {
			break;
		}
		result.push_back(v[ind]);
	}
	//assert(result.size() > 2);
	return result;
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x_ - b.x_) * (a.x_- b.x_) + (a.y_ - b.y_) * (a.y_- b.y_));
}

bool in_field(const Point &a) {
    return (a.x_ >= 0 && a.y_ >= 0 && a.x_ < X_FIELD_SIZE && a.y_ < Y_FIELD_SIZE);
}

Polygon::Polygon(std::vector<Polygon> &polygons) {
	int cnt = 0;
	Point c;
	while (cnt < 10) {
		c = Point();
		double min_dist = 1e9;
		for (auto polygon : polygons) {
			for (size_t i = 0; i < polygon.coord_.size(); ++i) {
				min_dist = std::min(min_dist, dist(polygon.coord_[i], c));
			}
		}
		if (min_dist >= OBSTACLE_R) {
			break;
		}
		++cnt;
	}
	if (cnt == 10) {
		return;
	}
	size_ = abs(rand()) % 10 + 3;
	for (size_t i = 0; coord_.size() < size_; ++i) {
		Point d{};
		d.x_ = static_cast<int>(d.x_) % OBSTACLE_R;
		if (rand() & 1) {
			d.x_ *= -1;
		}
		d.y_ = static_cast<int>(d.y_) % OBSTACLE_R;
		if (rand() & 1) {
			d.y_ *= -1;
		}
		Point cur(c + d);
		bool flag = true;
		for (auto polygon : polygons) {
			if (!point_in_polygon(cur, polygon) || !in_field(cur)) {
				flag = false;
			}
		}
		if (flag) {
			coord_.push_back(cur);
		}

	}
	//coord_ = std::vector<Point>{{56, 291}, {29, 229}, {42,  233},  {30, 208}};
	//coord_.push_back(Point(1, 2));
	coord_ = convex_hull(coord_);
}

bool check_one_line_intersection(double a, double b, double c, double d) {
	if (a > b) {
		std::swap(a, b);
	}
	if (c > d) {
		std::swap(c, d);
	}
	return std::max(a, c) <= std::min(b, d);
}


bool segment_and_segment_intersection(const Segment &a, const Segment &b) { //simple
	return oriented_area(a.a_, a.b_, b.a_) * oriented_area(a.a_, a.b_, b.b_) <= 0 &&
	       oriented_area(b.a_, b.b_, a.a_) * oriented_area(b.a_, b.b_, a.b_) <= 0 &&
	       check_one_line_intersection(a.a_.x_, a.b_.x_, b.a_.x_, b.b_.x_) &&
	       check_one_line_intersection(a.a_.y_, a.b_.y_, b.a_.y_, b.b_.y_);
	//return rotate(A,B,C)*rotate(A,B,D)<=0 and rotate(C,D,A)*rotate(C,D,B)<0
}

bool segment_and_polygon_intersection(const Segment &segment, const Polygon &polygon) {
	for (size_t i = 0; i < polygon.coord_.size(); ++i) {
		Segment other{polygon.coord_[i], polygon.coord_[(i + 1) % polygon.coord_.size()]};
		if (segment_and_segment_intersection(segment, other)) {
			return true;
		}
	}
	return false;
}

void swap(Point &a, Point &b) {
	std::swap(a.x_, b.x_);
	std::swap(a.y_, b.y_);
}

void swap(Vector &a, Vector &b) {
	std::swap(a.x_, b.x_);
	std::swap(a.y_, b.y_);
}

void swap(Polygon &a, Polygon &b) {
	std::swap(a.coord_, b.coord_);
	std::swap(a.size_, b.size_);
}

} //namespace world