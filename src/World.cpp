#include "World.hpp"

namespace world {

bool World::can_move(Point pos) {
	return true;
}

size_t World::get_lions_size() const {
	return lionsSize_;
}

size_t World::get_zebras_size() const {
	return zebrasSize_;
}

size_t World::get_grass_size() const {
	return grassSize_;
}

size_t World::get_obstacles_size() const {
	return obstaclesSize_;
}

} //namespace world