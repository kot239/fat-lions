#include "../include/World.hpp"
#include <iostream>
#include <cmath>

namespace world {


bool World::can_move(const Point &from, const Point &to) const {
    /*for (auto &polygon : obstaclesArray_) {
        if (segment_and_polygon_intersection(Segment{from, to}, polygon)) {
            return false;
        }
    }
    return true; */
    if (to.x_ < 10 || to.x_ > (621 - 10) ||
        to.y_ < 10 || to.y_ > (471 - 10)) {
        return false;
    }
     return true;
}

template<typename ANIMAL, typename FOOD>
void World::eating(ANIMAL& animal, std::vector<FOOD>& foodArray, int nutrition) {
    animal.make_move();
    if (foodArray.size() == 0) {
        return;
    }
    for (auto& food : foodArray) {
        if (abs(animal.position_.x_- food.position_.x_) < 10 && 
            abs(animal.position_.y_- food.position_.y_) < 10 && 
            animal.nextAction_ == Action::EAT) {

            animal.hunger_ -= nutrition;
            animal.nextAction_ = Action::GO;
            food = foodArray.back();
        }
    }
    foodArray.pop_back();
}

template<typename ANIMAL>
void World::reproduce(std::vector<ANIMAL>& animalArray) {
    for (size_t i = 0; i < animalArray.size(); i++) {
        if (animalArray[i].nextAction_ == Action::REPRODUCE) {
            if (animalArray[i].sex_ == Sex::FEMALE) {
                ANIMAL new_animal;
                new_animal.position_ = animalArray[i].position_;
                animalArray.push_back(new_animal);
            }
            animalArray[i].nextAction_ = Action::GO;
            animalArray[i].reprodCd_ = -1;
        }
    }
}

template <typename ANIMAL, typename FOOD>
void World::update_species(std::vector<ANIMAL>& animalArray, std::vector<FOOD>& foodArray, int nutrition) {
    int numbAlive = 0;
    for (auto& animal : animalArray) {
        if (animal.nextAction_ == Action::EAT) {
            eating<ANIMAL, FOOD>(animal, foodArray, nutrition);
        }
        if (animal.nextAction_ == Action::GO) {
            animal.make_move();
        }
        if (animal.nextAction_ != Action::REPRODUCE) {
           ++animal.age_;
           ++animal.reprodCd_;
           ++animal.hunger_;
        }
        
        if (animal.nextAction_ != Action::DIE) {
            animalArray[numbAlive] = animal;
            ++numbAlive;
        } 
    }
    animalArray.resize(numbAlive);
    reproduce<ANIMAL>(animalArray);
}

void World::update() {
    update_species<Lion, Zebra>(lionsArray_, zebrasArray_, ZEBRAS_NUTRITION);
    update_species<Zebra, Grass>(zebrasArray_, grassArray_, GRASS_NUTRITION);

    if (rand() % FREQUENCY == 0) {
        Grass new_grass;
        grassArray_.push_back(new_grass);
    }
}

} //namespace world
