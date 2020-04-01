#ifndef _INCLUDE_ANIMAL_HPP
#define _INCLUDE_ANIMAL_HPP


#include <variant>
#include "Geometry.hpp"

namespace world {

enum class Sex {
	MALE, FEMALE
};

enum class Action {
	EAT, DIE, GO, REPRODUCE, NOTHING
};

class Animal {
public:
	Vector direction_;
	Action nextAction_;
	double velocity_;
	int vision_;
	Point position_;
	int hunger_;
	int age_;
	int sexcd_;
	Sex sex_;

    Animal();
	Animal(const Animal &other);

	Point get_position() const;
	Sex get_sex() const;
	int get_age() const;
	int get_vision() const;
	int get_hunger() const;
	bool get_sexcd() const;

	void make_move();
	
};

void swap(Animal &a, Animal &b);

} //namespace world

#endif // _INCLUDE_ANIMAL_HPP