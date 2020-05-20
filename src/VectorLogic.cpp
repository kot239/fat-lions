#include "../include/VectorLogic.hpp"
#include "../include/World.hpp"
#include <iostream>
#include <cmath>

using namespace world;

double VectorLogic::sqr_dist(Point a, Point b) {
    return (a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_);
}

Vector VectorLogic::find_correct_vec(Animal& curAnimal, Vector resVector) {
    resVector.normalize();
    if (curWorld_.can_move(curAnimal.position_, curAnimal.position_ + resVector * curAnimal.velocity_)) {
        return resVector;
    }
    for (int i = 1; i >= -1; i -= 2) {
        for (int j = 1; j >= -1; j -= 2) {
            resVector.x_ *= j;
            resVector.y_ *= i;
            resVector.normalize();
            if (curWorld_.can_move(curAnimal.position_, curAnimal.position_ + resVector * curAnimal.velocity_)) {
                return resVector;
            }
            resVector.x_ *= j;
            resVector.y_ *= i;
        }
    }
    return resVector; 
}

template<typename T>
bool VectorLogic::reproduce(T& curAnimal, const std::vector<T>& animalArray) {
    double curDist;
    double minDist = -1;
    Vector resVector = {0, 0};
    for (const auto& animal : animalArray) {
        curDist = sqr_dist(animal.position_, curAnimal.position_);
        if (animal.sex_ != curAnimal.sex_ && animal.ready_for_reprod() &&
            (curDist < curAnimal.vision_ * curAnimal.vision_)) {

            if (abs(animal.position_.x_ - curAnimal.position_.x_) < 10 &&
                abs(animal.position_.y_ - curAnimal.position_.y_) < 10 ) {
                curAnimal.nextAction_ = Action::REPRODUCE;
                return true;
            }
            if (abs(minDist + 1) < 0.00001 || curDist < minDist) {
                minDist = curDist;
                resVector = animal.position_ - curAnimal.position_;
            }
        }
    }
    if (!(resVector.len() < 0.0001)) {
        curAnimal.direction_ = find_correct_vec(curAnimal, resVector);
        return true;
    }
    else {
        curAnimal.direction_ = find_correct_vec(curAnimal, curAnimal.direction_);
        return false;
    }
}


template<typename T>
void VectorLogic::nutrition(Animal& curAnimal, const std::vector<T>& foodArray) {
    double minDist = -1;
    double curDist = 0;
    Vector resVector = {0, 0};
    for (const auto& food : foodArray) {
        curDist = sqr_dist(food.position_, curAnimal.position_);

        if (curDist < curAnimal.vision_ * curAnimal.vision_ &&
            (abs(minDist + 1) < 0.00001 || curDist < minDist)) {

            minDist = curDist;
            resVector = food.position_ - curAnimal.position_;
            if (resVector.len() < curAnimal.velocity_) {
                curAnimal.nextAction_ = Action::EAT;
            }
        }
    }
    if (!(resVector.len() < 0.0001) && curAnimal.nextAction_ != Action::EAT)  {
        curAnimal.nextAction_ = Action::GO;
        curAnimal.direction_ = find_correct_vec(curAnimal, resVector);
        return;
    }
}

void VectorLogic::find_target_lion(Lion& curLion) { 
    if (curLion.is_dead()) {
        return;
    }
    if (curLion.ready_for_reprod()) {
        if (reproduce<Lion>(curLion, curWorld_.lionsArray_)) {
            return;
        }
    } 
    nutrition<Zebra>(curLion, curWorld_.zebrasArray_);
    curLion.direction_ = find_correct_vec(curLion, curLion.direction_);
}

void VectorLogic::find_target_zebra(Zebra& curZebra) {
    if (curZebra.is_dead()) {
        return;
    }

    Vector resVector = {0, 0};
    for (const auto& lion : curWorld_.lionsArray_) {
        if (sqr_dist(lion.position_, curZebra.position_) < curZebra.vision_ * curZebra.vision_) {
            resVector += lion.position_ - curZebra.position_; //find result vector
        }
    }

    if (!(resVector.len() < 0.0001)) { //check if lions around
        resVector *= -1;
        curZebra.nextAction_ = Action::GO;
        curZebra.direction_ = find_correct_vec(curZebra, resVector);
        return;   
    }

    if (curZebra.ready_for_reprod()) {
        if (reproduce<Zebra>(curZebra, curWorld_.zebrasArray_)) {
            return;
        }
    }
    nutrition<Grass>(curZebra, curWorld_.grassArray_);
    curZebra.direction_ = find_correct_vec(curZebra, curZebra.direction_);
}
