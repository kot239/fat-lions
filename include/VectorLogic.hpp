#ifndef _INCLUDE_VECTORLOGIC_HPP_
#define _INCLUDE_VECTORLOGIC_HPP_

#include "World.hpp"

using namespace world;

struct VectorLogic {
    bool ready_for_reprod(const Animal& curAnimal);
    int dist(Point a, Point b);
    Vector find_correct_vec(const Animal& curAnimal, Vector resVector, const World& curWorld);
    bool is_died(Animal& animal);
    void find_target_lion(Lion& curLion, World& curWorld);
    void find_target_zebra(Zebra& curZebra, World& curWorld);

    template<typename T>
    void reproduce(T& curAnimal, const std::vector<T>& animalArray, World& curWorld); 

    template<typename T>
    void nutrition(Animal& curAnimal, const std::vector<T>& foodArray, World& curWorld);
};

#endif