#include "../include/Animal.hpp"
#include "../include/World.hpp"
#include <random>
#include <iostream>
#include <ctime>

namespace world {

Animal::Animal() {
    direction_.x_ = abs(rand()) % 100;
    direction_.y_= abs(rand()) % 100;
    if (rand() & 1) direction_.x_ *= -1;
    if (rand() & 1) direction_.y_ *= -1;
   
    velocity_ = 1;
   
    position_.x_ = abs(rand()) % 400;
    position_.y_= abs(rand()) % 400;
   
    hunger_ = 0;
    age_= 0;
    sexcd_ = 0;
   
    if (std::rand() & 1) {
        sex_= Sex::MALE;
    } else {
        sex_ = Sex::FEMALE;
    }   
}

Animal::Animal(const Animal &other) : direction_(other.direction_)
									, nextAction_(Action::NOTHING)
									, velocity_(START_VELOCITY)
									, position_(other.position_)
									, hunger_(START_HUNGER)
									, age_(-1)
									, sexcd_(CD_SEX_TIME) {
	if (std::rand() & 1) {
		sex_ = Sex::MALE;
	} else {
		sex_ = Sex::FEMALE;
	}
}

void Animal::make_move() {
	double len = sqrt((direction_.x_ - position_.x_) * (direction_.x_ - position_.x_) +
	(direction_.y_ - position_.y_) * (direction_.y_ - position_.y_)); 

	direction_.x_ = (direction_.x_ - position_.x_) / len;
	direction_.y_ = (direction_.y_ - position_.y_) / len; 
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
	std::swap(a.sexcd_, b.sexcd_);
}

} //namespace world