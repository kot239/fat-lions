#ifndef _INCLUDE_RANDOMLOGIC_HPP_
#define _INCLUDE_RANDOMLOGIC_HPP_

#include "World.hpp"

constexpr int NUMBER_OF_POINTS = 50;
constexpr int LEN_COEF = 1;
constexpr int MAXX = 600;
constexpr int MAXY = 600;

double fRand(double fMin, double fMax);

class PointGenerator {
public:
    const std::vector<world::Point>& generate_point(const world::Animal&);
private:
    std::vector<world::Point> points_ = std::vector<world::Point>(NUMBER_OF_POINTS);
};

class CountBenefits {
public:
    CountBenefits(const world::World& world) : curWorld_(world) {}
    double count_benefits_for_lion(const world::Lion&, const world::Point&);
    double count_benefits_for_zebra(const world::Point&);
private:
    const world::World& curWorld_;
};

class RandomLogic {
public:
    explicit RandomLogic(world::World& world) : curWorld_(world), point_cost(world) {}
    void find_target_lion(world::Lion& curLion);
    void find_target_zebra(world::Zebra& curZebra);

    template<typename T>
    bool reproduce(T& curAnimal, const std::vector<T>& animalArray); 
    template<typename T>
    bool nutrition(world::Animal& curAnimal, const std::vector<T>& foodArray); 
private:
    const world::World& curWorld_;
    CountBenefits point_cost;
    PointGenerator generator_;
    std::vector<world::Point> points_;
};


#endif