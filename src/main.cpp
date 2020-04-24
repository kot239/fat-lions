#include <iostream>
#include "World.hpp"
#include "VectorLogic.hpp"
#include <ctime>

using namespace world;

void run_game(World& world, VectorLogic& logic) {
    for (int i = 0; i < 1000; i++) {
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
    std::srand(std::time(nullptr));
    World world;
    VectorLogic vector_logic;

    for (int i = 0; i < 0; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < 1; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }
    std::cout << "START\n";
    std::cout << world.lionsArray_[0].direction_.x_ << ' ' << world.lionsArray_[0].direction_.y_ << '\n';
    run_game(world, vector_logic);

} 