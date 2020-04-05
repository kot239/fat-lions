//#include "World.hpp"
#include "../include/Geometry.hpp"
#include "../include/World.hpp"

#include <cmath>
#include <stdlib.h>

namespace world {

const double eps = 1e-5;

//Point

Point::Point() {
	x_ = abs(rand()) % X_FIELD_SIZE;
	y_ = abs(rand()) % Y_FIELD_SIZE;
}

Point::Point(const Point &other) : x_(other.x_), y_(other.y_) {}

Point &Point::operator=(const Point &other) {
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


Vector &Vector::operator*(const int val) {
	x_*= val;
	y_ *= val;
	return *this;
}

Vector &Vector::operator*=(const int val) {
	*this = *this * val;
	return *this;
}

Vector &Vector::operator+=(const Vector &v) {
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}

//Vector 
//Segment 
Segment::Segment(const Point &a, const Point &b) : a_(a), b_(b) {}

//Segment

//Polygon
bool point_in_polygon(const Point &point, const Polygon &polygon) { //TODO
	return false;
}

std::vector<Point> &convex_hull(std::vector<Point> &v) { //TODO
	return v;
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