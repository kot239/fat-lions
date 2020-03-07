#include "Grass.hpp"

namespace world {

Point Grass::get_position() const {
	return position_;
}

Grass::Grass(Animal &animal) {
	position_ = animal.position_;
}

void swap(Grass &a, Grass &b) {
	swap(a.position_, b.position_);
}

} //namespace world