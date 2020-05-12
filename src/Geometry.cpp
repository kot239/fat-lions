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


bool Point::operator==(const Point &point) {
	return (abs(x_ - point.x_) < eps && abs(y_ - point.y_) < eps);
}

Point Point::operator+(const Vector &v) const {
	Point cur(*this);
	cur += v;
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
	return a.x_ * b.x_ + a.y_ + b.y_;
}

//Angle
Angle::Angle(const Vector &a, const Vector &b) {
	phi = std::acos(a.len() * b.len() / coord_scalar_product(a, b));
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
	size_t n = polygon.size_;
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

std::vector<Point> convex_hull(std::vector<Point> &v) { //gift wrapping algo
	size_t ind = 0, n = v.size();
	for (size_t i = 1; i < n; ++i) {
		if (v[i].y_ < v[ind].y_) {
			ind = i;
		}
		if (v[i].y_ == v[ind].y_ && v[i].x_ > v[ind].x_) {
			ind = i;
		}
	}

	auto p0 = v[ind];
	auto pi = p0;
	std::vector<Point> result = {p0};
	v.push_back(p0);
	ind = 0;
	while (true) {
		++ind;
		for (size_t i = ind; i < n; ++i) {
			Vector v1(result.back(), v[i]), v2(result.back(), v[ind]);
			Angle angle1(v1);
			Angle angle2(v2);
			if (angle1 < angle2 || (angle1 == angle2 && v1.len() > v2.len())) {
				swap(v[i], v[ind]);
			}
		}
		pi = v[ind];
		if (pi == p0) {
			break;
		}
		result.push_back(pi);
	}
	return result;

}

Polygon::Polygon(std::vector<Polygon> &polygons) {
	size_ = abs(rand()) % 10 + 3;
	for (size_t i = 0; i < size_; ++i) {
		auto cur = Point();
		for (auto polygon : polygons) {
			if (!point_in_polygon(cur, polygon)) {
				coord_.push_back(cur);
			}
		}
	}
	coord_ = convex_hull(coord_);
	size_ = coord_.size();
	size_t ind = 0;
	while(ind < polygons.size()) {
		if (point_in_polygon(polygons[ind].coord_[0], *this)) {
			swap(polygons[ind], polygons.back());
			polygons.pop_back();
		} else {
			++ind;
		}
	}
	polygons.push_back(*this);
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

double oriented_area(const Point &a, const Point &b, const Point &c) {
	return (b.x_ - a.x_) * (c.y_ - a.y_) - (b.y_ - a.y_) * (c.x_ - a.x_);
}

bool segment_and_segment_intersection(const Segment &a, const Segment &b) { //simple
	return oriented_area(a.a_, a.b_, b.a_) * oriented_area(a.a_, a.b_, b.b_) <= 0 && 
	       oriented_area(b.a_, b.b_, a.a_) * oriented_area(b.a_, b.b_, a.b_) <= 0 &&
	       check_one_line_intersection(a.a_.x_, a.b_.x_, b.a_.x_, b.a_.x_) &&
	       check_one_line_intersection(a.a_.y_, a.b_.y_, b.a_.y_, b.a_.y_);
}

bool segment_and_polygon_intersection(const Segment &segment, const Polygon &polygon) {
	for (size_t i = 0; i < polygon.size_; ++i) {
		Segment other{polygon.coord_[i], polygon.coord_[(i + 1) % polygon.size_]};
		if (segment_and_segment_intersection(segment, other)) {
			return false;
		}
	}
	return true;
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