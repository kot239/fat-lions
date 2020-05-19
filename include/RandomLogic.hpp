#ifndef _INCLUDE_RANDOMLOGIC_HPP_
#define _INCLUDE_RANDOMLOGIC_HPP_

#include "World.hpp"

constexpr int NUMBER_OF_POINTS = 500;
constexpr int LEN_COEF = 1;
constexpr int MAXX = 600;
constexpr int MAXY = 600;
constexpr int DANGER_COST  = -10000;

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
    double count_benefits_for_zebra(const world::Zebra&, const world::Point&);
private:
    template<typename T>
    double count_benefits_food(const world::Animal&, const std::vector<T>&, const world::Point&);

    template<typename T>
    double count_benefits_reprod(const T&, const std::vector<T>&, const world::Point&);
    const world::World& curWorld_;
};

class RandomLogic {
public:
    explicit RandomLogic(world::World& world) : curWorld_(world), point_cost(world) {}
    void find_target_lion(world::Lion& curLion);
    void find_target_zebra(world::Zebra& curZebra);
private:
    template<typename T>
    bool reproduce(T& curAnimal, const std::vector<T>& animalArray); 

    template<typename T>
    bool nutrition(world::Animal& curAnimal, const std::vector<T>& foodArray); 

    bool inDanger(world::Zebra& curZebra);

    void check_errors(world::Animal& curAnimal);

    
    const world::World& curWorld_;
    CountBenefits point_cost;
    PointGenerator generator_;
    std::vector<world::Point> points_;
};


#endif