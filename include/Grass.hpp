#ifndef _INCLUDE_GRASS_HPP_
#define _INCLUDE_GRASS_HPP_

#include "Geometry.hpp"
#include "Animal.hpp"

namespace world {

class Grass final {
public:
	Grass(Animal &animal);
	Point get_position() const;
	Point position_;
};

void swap(Grass &a, Grass &b);

} //namespace world

#endif // _INCLUDE_GRASS_HPP_