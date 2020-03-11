#ifndef _INCLUDE_GEOMETRY_HPP_
#define _INCLUDE_GEOMETRY_HPP_

#include <vector>

namespace world {

class Vector;

class Point final {
public:
	int x_, y_;

	Point &operator=(const Point &other);
	Point &operator+=(const Vector &v);
	bool operator==(const Point &other);
	Point operator+(const Vector &v) const;
	Vector operator-(const Point &other) const;
};

class Vector final {
public:
	int x_, y_;
    Vector &operator+=(const Vector &v);
    Vector &operator*=(const int val);
	Vector &operator*(const int val);

};

class Figure final {
public:
	bool point_in_figure(const Point &point) const;
private:
	std::vector<Point> coord_;
};

void swap(Point &a, Point &b);

void swap(Vector &a, Vector &b);
} //namespace world

#endif // _INCLUDE_GEOMETRY_HPP_