#ifndef _INCLUDE_WORLD_HPP
#define _INCLUDE_WORLD_HPP

#include "../include/Geometry.hpp"
#include "../include/Lion.hpp"
#include "../include/Zebra.hpp"
#include "../include/Grass.hpp"
#include "../include/Obstacle.hpp"

#include <vector>

namespace world {

const int AGE_FOR_REPROD = 100;
const int MAX_AGE = 100000000;
const int HUNGER_FOR_REPROD = 10;
const int CD_REPROD_TIME = 100;
const int MAX_HUNGER = 100000000;
const int GRASS_NUTRITION = 10;
const double START_VELOCITY = 5;
const int START_HUNGER = 2;
const int START_VISION = 50;
const int ZEBRAS_NUTRITION = 20;
const size_t X_FIELD_SIZE = 672;
const size_t Y_FIELD_SIZE = 472;


class World final {
public:
	std::vector<Lion> lionsArray_;
	std::vector<Zebra> zebrasArray_;
	std::vector<Grass> grassArray_;
	std::vector<Polygon> obstaclesArray_;

	bool can_move(const Point &from, const Point &to) const;
	void update();
	void zebras_death(size_t ind);
	void lions_death(size_t ind);
	void grass_death(size_t ind);
};

} //namespace world

#endif // _INCLUDE_WORLD_HPP