#ifndef _INCLUDE_WORLD_HPP
#define _INCLUDE_WORLD_HPP

#include "Animal.hpp"
#include "Lion.hpp"
#include "Zebra.hpp"
#include "Grass.hpp"
#include "Obstacle.hpp"

#include <vector>

namespace world {

const int AGE_FOR_SEX = 5;
const int HUNGER_FOR_SEX = 10;
const int CD_SEX_TIME = 3;

class World final {
public:
	std::vector<Lion> lionsArray;
	std::vector<Zebra> zebrasArray;
	std::vector<Grass> grassArray;
	std::vector<Obstacle> obstaclesArray;

	bool can_move(Point pos);
	size_t get_lions_size() const;
	size_t get_zebras_size() const;
	size_t get_grass_size() const;
	size_t get_obstacles_size() const;

private:
	size_t lionsSize_, zebrasSize_, grassSize_, obstaclesSize_;
};

} //namespace world

#endif // _INCLUDE_WORLD_HPP