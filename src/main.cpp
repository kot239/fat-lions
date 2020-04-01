#include <iostream>
#include "World.hpp"
#include "vector_logic_lion.h"
#include "vector_logic_zebra.h"

using namespace world;

void run_game(World& world, VectorLogicZebra& logicZebra, VectorLogicLion& logicLion) {
    for (int i = 0; i < 100; i++) {
        for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
            logicZebra.find_target(world.zebrasArray_[j], world);
        }

        for (size_t j = 0; j < world.lionsArray_.size(); j++) {
            logicLion.find_target(world.lionsArray_[j], world);
            std::cout << j << ' ' << (world.lionsArray_[j].position_.x_) << '\n';
        }
        world.update();
    }    
}

int main() {
    World world;
    VectorLogicLion logicLion;
    VectorLogicZebra logicZebra;
    
    for (int i = 0; i < 5; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < 5; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }
    run_game(world, logicZebra, logicLion);
}