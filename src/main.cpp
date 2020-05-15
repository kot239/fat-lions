#include <iostream>
#include "World.hpp"
#include "VectorLogic.hpp"
#include <ctime>

using namespace world;

void run_game(World& world, VectorLogic& logic) {
    for (int i = 0; i < 1000; i++) {
        for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
            logic.find_target_zebra(world.zebrasArray_[j]);
        }

        for (size_t j = 0; j < world.lionsArray_.size(); j++) {
            logic.find_target_lion(world.lionsArray_[j]);
        }
        world.update();
    }    
}

int main() {
    std::srand(std::time(nullptr));
    World world;
    VectorLogic vector_logic(world);
    for (int i = 0; i < 50; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < 50; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }

    for (int i = 0; i < 10; ++i) {
        Polygon tmp(world.obstaclesArray_);
        if (tmp.coord_.size() > 0) {
            world.obstaclesArray_.push_back(tmp);
        }
    }

    for (int i = 0; i < world.obstaclesArray_.size(); ++i) {
        std::cout << "Polygon " << i << "\n";
        for (int j = 0; j < (int)world.obstaclesArray_[i].coord_.size(); ++j) {
            std::cout << world.obstaclesArray_[i].coord_[j].x_ << " " << world.obstaclesArray_[i].coord_[j].y_ << "\n";
        }
    }

    run_game(world, vector_logic);

} 