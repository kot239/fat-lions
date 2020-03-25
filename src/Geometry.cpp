#include "../include/Geometry.hpp"

namespace world {

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

bool Point::operator==(const Point &point) {
	return x_ == point.x_ && y_ == point.y_;
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


bool Figure::point_in_figure(const Point &point) const {
	return (point.x_ >= coord_[0].x_ && point.x_ <= coord_[1].x_ && point.y_ <= coord_[0].y_ && point.y_ >= coord_[2].y_);
} 

void swap(Point &a, Point &b) {
	std::swap(a.x_, b.x_);
	std::swap(a.y_, b.y_);
}

void swap(Vector &a, Vector &b) {
	std::swap(a.x_, b.x_);
	std::swap(a.y_, b.y_);
}

} //namespace world