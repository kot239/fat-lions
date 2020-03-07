#ifndef _INCLUDE_OBSTACLE_HPP_
#define _INCLUDE_OBSTACLE_HPP_

#include <vector>

namespace world {

class Obstacle final {
private:
	std::vector<Point> coord;
};

} //namespace world

#endif // _INCLUDE_OBSTACLE_HPP_