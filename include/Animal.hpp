#ifndef _INCLUDE_ANIMAL_HPP
#define _INCLUDE_ANIMAL_HPP

struct Point {
	int x_, y_;
};

struct Vector {
	int x_, y_;
};

enum class Sex {
	MALE, FEMALE
};

class Animal {
public:
	
private:
	Point position_;
	Vector direction_;
	Sex sex_;
	int age_;
	int hunger_;
};

#endif // _INCLUDE_ANIMAL_HPP