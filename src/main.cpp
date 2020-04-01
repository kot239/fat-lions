#include <iostream>
#include "World.hpp"
#include "VectorLogic.hpp"

using namespace world;

void run_game(World& world, VectorLogic& logic) {
    for (int i = 0; i < 100; i++) {
        for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
            logic.find_target_zebra(world.zebrasArray_[j], world);
        }

        for (size_t j = 0; j < world.lionsArray_.size(); j++) {
            logic.find_target_lion(world.lionsArray_[j], world);
        }
        world.update();
    }    
}

int main() {
    World world;
    VectorLogic vector_logic;

    for (int i = 0; i < 5; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < 5; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }
    run_game(world, vector_logic);
} 