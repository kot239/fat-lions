#include "../include/Grass.hpp"
#include <random>

namespace world {

Grass::Grass() {
	position_.x_ = abs(rand()) % 600;
    position_.y_= abs(rand()) % 400;
}

Grass::Grass(Animal &animal) {
	position_ = animal.position_;
}

void swap(Grass &a, Grass &b) {
	swap(a.position_, b.position_);
}

} //namespace world