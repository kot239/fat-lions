#include "../include/Animal.hpp"
#include "../include/World.hpp"
#include <random>
#include <iostream>
#include <ctime>
#include<cstdlib>

namespace world {

Animal::Animal() {
    direction_.x_ = abs(rand()) % 100;
    direction_.y_= abs(rand()) % 100;
    if (rand() & 1) direction_.x_ *= -1;
    if (rand() & 1) direction_.y_ *= -1;
    direction_.normalize();
    velocity_ = START_VELOCITY;
    vision_ = 50;
    position_.x_ = 50 + rand() % 500;;
    position_.y_= 50 + rand() % 300;
    hunger_ = 0;
    age_= 0;
    reprodCd_ = -1;
    nextAction_ = Action::GO;
    if (std::rand() & 1) {
        sex_= Sex::MALE;
    } else {
        sex_ = Sex::FEMALE;
    }   
}

bool Animal::ready_for_reprod() const {
    return age_ >= AGE_FOR_REPROD &&
           reprodCd_ >= CD_REPROD_TIME &&
           hunger_ <= HUNGER_FOR_REPROD;
}

bool Animal::is_dead() {
    if (age_ >= MAX_AGE || hunger_ >= MAX_HUNGER) {
        nextAction_ = Action::DIE;
        return true;
    }
    return false; 
}

void Animal::make_move() {
    position_ += (direction_ * velocity_);
}

void swap(Animal &a, Animal &b) {
    std::swap(a.direction_, b.direction_);
    std::swap(a.nextAction_, b.nextAction_);
    std::swap(a.velocity_, b.velocity_);
    std::swap(a.position_, b.position_);
    std::swap(a.sex_, b.sex_);
    std::swap(a.age_, b.age_);
    std::swap(a.hunger_, b.hunger_);
    std::swap(a.reprodCd_, b.reprodCd_);
}

} //namespace world