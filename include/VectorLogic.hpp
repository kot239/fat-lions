#ifndef _INCLUDE_VECTORLOGIC_HPP_
#define _INCLUDE_VECTORLOGIC_HPP_

#include "World.hpp"

class VectorLogic {
public:
    explicit VectorLogic(const world::World& world) : curWorld_(world) {}
    bool ready_for_reprod(const world::Animal& curAnimal);
    double sqr_dist(world::Point a, world::Point b);
    world::Vector find_correct_vec(world::Animal& curAnimal, world::Vector resVector);
    bool is_dead(world::Animal& animal);
    void find_target_lion(world::Lion& curLion);
    void find_target_zebra(world::Zebra& curZebra);

    template<typename T>
    bool reproduce(T& curAnimal, const std::vector<T>& animalArray); 

    template<typename T>
    void nutrition(world::Animal& curAnimal, const std::vector<T>& foodArray);
private:
    const world::World& curWorld_;
};

#endif