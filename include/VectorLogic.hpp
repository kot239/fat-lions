#ifndef _INCLUDE_VECTORLOGIC_HPP_
#define _INCLUDE_VECTORLOGIC_HPP_

#include "World.hpp"

struct VectorLogic {
    bool ready_for_reprod(const world::Animal& curAnimal);
    double sqr_dist(world::Point a, world::Point b);
    world::Vector find_correct_vec(world::Animal& curAnimal, world::Vector resVector, const world::World& curWorld);
    bool is_dead(world::Animal& animal);
    void find_target_lion(world::Lion& curLion, world::World& curWorld);
    void find_target_zebra(world::Zebra& curZebra, world::World& curWorld);

    template<typename T>
    void reproduce(T& curAnimal, std::vector<T>& animalArray, world::World& curWorld); 

    template<typename T>
    void nutrition(world::Animal& curAnimal, const std::vector<T>& foodArray, world::World& curWorld);
};

#endif