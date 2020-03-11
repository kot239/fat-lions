#ifndef _INCLUDE_WORLD_HPP
#define _INCLUDE_WORLD_HPP

#include "Geometry.hpp"
#include "Lion.hpp"
#include "Zebra.hpp"
#include "Grass.hpp"
#include "Obstacle.hpp"

#include <vector>

namespace world {

const int AGE_FOR_SEX = 5;
const int MAX_AGE = 100;
const int HUNGER_FOR_SEX = 10;
const int CD_SEX_TIME = 3;
const int MAX_HUNGER = 100;
const int GRASS_NUTRITION = 10;
const int START_VELOCITY = 5;
const int START_HUNGER = 2;
const int ZEBRAS_NUTRITION = 20;

class World final {
public:
	std::vector<Lion> lionsArray_;
	std::vector<Zebra> zebrasArray_;
	std::vector<Grass> grassArray_;
	std::vector<Obstacle> obstaclesArray_;

	bool can_move(const Point pos) const;
	void update();
	void zebras_death(size_t ind);
	void lions_death(size_t ind);
	void grass_death(size_t ind);
};

} //namespace world

#endif // _INCLUDE_WORLD_HPP