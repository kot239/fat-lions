#ifndef _INCLUDE_GEOMETRY_HPP_
#define _INCLUDE_GEOMETRY_HPP_

#include <vector>

namespace world {

class Vector;

class Point final {
public:
	double x_, y_;

	Point();
	Point(const Point &other);

	Point &operator=(const Point &other);
	Point &operator+=(const Vector &v);
	bool operator==(const Point &other);
	Point operator+(const Vector &v) const;
	Vector operator-(const Point &other) const;
};

class Vector final {
public:
	double x_, y_;

	Vector() = default;
	Vector(double x, double y);
	Vector(const Vector &v);
	Vector(const Point &a, const Point &b);
    Vector &operator+=(const Vector &v);
    Vector &operator*=(const int val);
	Vector operator*(const int val);

	double len() const;

};

class Angle final {
public:
	double phi;

	Angle(const Vector &a);
	Angle(const Vector &a, const Vector &b);

	bool operator<(const Angle &other) const;
	bool operator==(const Angle &other) const;
	Angle &operator=(const Angle &other);
};

class Segment final {
public:
	Point a_, b_;

	Segment(const Point &a, const Point &b);
};

class Polygon final {
public:
	size_t size_;
	std::vector<Point> coord_;

	Polygon(std::vector<Polygon> &polygons);
};

void swap(Point &a, Point &b);

void swap(Vector &a, Vector &b);

void swap(Polygon &a, Polygon &b);

} //namespace world

#endif // _INCLUDE_GEOMETRY_HPP_