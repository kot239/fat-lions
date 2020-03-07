#include "Animal.hpp"
#include "World.hpp"

namespace world {

Point Animal::get_position() const {
	return position_;
}

Sex Animal::get_sex() const {
	return sex_;
}

int Animal::get_age() const {
	return age_;
}

int Animal::get_hunger() const {
	return hunger_;
}

bool Animal::get_sexcd() const {
	return sexcd_ >= CD_SEX_TIME;
}

} //namespace world