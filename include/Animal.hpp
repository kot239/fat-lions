#ifndef _INCLUDE_ANIMAL_HPP
#define _INCLUDE_ANIMAL_HPP

namespace world {

struct Point {
	int x_, y_;
};

struct Vector {
	int x_, y_;
};

enum class Sex {
	MALE, FEMALE
};

enum class Action {
	EAT, DIE, GO, REPRODUCE
};

class Animal {
public:
	Vector direction;
	Action nextAction;
	int velocity;

	Point get_position() const;
	Sex get_sex() const;
	int get_age() const;
	int get_hunger() const;
	bool get_sexcd() const;
	
private:
	Point position_;
	Sex sex_;
	int age_;
	int hunger_;
	int sexcd_;
};

} //namespace world

#endif // _INCLUDE_ANIMAL_HPP