#include "../include/VectorLogic.hpp"
#include "../include/World.hpp"

using namespace world;

bool VectorLogic::ready_for_reprod(const Animal& curAnimal) {
    return curAnimal.age_ >= AGE_FOR_REPROD &&
           curAnimal.reprodCd_ &&
           curAnimal.hunger_ >= HUNGER_FOR_REPROD;
}

double VectorLogic::sqr_dist(Point a, Point b) {
    return (a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_);
}

Vector VectorLogic::find_correct_vec(const Animal& curAnimal, Vector resVector, const World& curWorld) {
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; i <= 1; j += 2) {
            resVector.x_ *= j;
            resVector.y_ *= i;
            if (curWorld.can_move(curAnimal.position_, curAnimal.position_ + resVector * curAnimal.velocity_)) {
                return resVector;
            }
            resVector.x_ *= j;
            resVector.y_ *= i;
        }
    }
    return resVector;
}

bool VectorLogic::is_dead(Animal& curAnimal) {
    if (curAnimal.age_ >= MAX_AGE || curAnimal.hunger_ >= MAX_HUNGER) {
        curAnimal.nextAction_ = Action::DIE;
        return true;
    }
    return false; 
}

template<typename T>
void VectorLogic::reproduce(T& curAnimal, std::vector<T>& animalArray, World& curWorld) {
    double curDist;
    double minDist = -1;
    Vector resVector = {0, 0};
    for (auto& animal : animalArray) {
        curDist = sqr_dist(animal.position_, curAnimal.position_);
        if (animal.sex_ != curAnimal.sex_ && ready_for_reprod(animal) &&
            (curDist < curAnimal.vision_ * curAnimal.vision_)) {

            if (animal.position_ == curAnimal.position_) {
                animal.nextAction_ = (animal.sex_ == Sex::FEMALE) ? Action::REPRODUCE : Action::NOTHING;
                curAnimal.nextAction_ = (curAnimal.sex_ == Sex::FEMALE) ? Action::REPRODUCE : Action::NOTHING;
                return;
            }
            if (minDist == -1 || curDist < minDist) {
                minDist = curDist;
                resVector = animal.position_ - curAnimal.position_;
            }
        }
    }
    curAnimal.nextAction_ = Action::GO;
    curAnimal.direction_ = find_correct_vec(curAnimal, resVector, curWorld);
}


template<typename T>
void VectorLogic::nutrition(Animal& curAnimal, const std::vector<T>& foodArray, World& curWorld) {
    double curDist;
    double minDist = -1;
    Vector resVector = {0, 0};
    for (auto& food : foodArray) {
        curDist = sqr_dist(food.position_, curAnimal.position_);
        if (curDist < curAnimal.vision_ * curAnimal.vision_ &&
            (minDist == -1 || curDist < minDist)) {

            minDist = curDist;
            resVector = food.position_ - curAnimal.position_;
        }
    }
    if (resVector.x_ != 0 || resVector.y_ != 0) {
        curAnimal.nextAction_ = Action::GO;
        curAnimal.direction_ = find_correct_vec(curAnimal, resVector, curWorld);
        return;
    }
}

void VectorLogic::find_target_lion(Lion& curLion, World& curWorld) {
    if (is_dead(curLion)) {
        return;
    }
    if (ready_for_reprod(curLion)) {
        reproduce<Lion>(curLion, curWorld.lionsArray_, curWorld);
        return;
    }
    nutrition<Zebra>(curLion, curWorld.zebrasArray_, curWorld);
    curLion.nextAction_ = Action::GO;
}

void VectorLogic::find_target_zebra(Zebra& curZebra, World& curWorld) {
    if (is_dead(curZebra)) {
        return;
    }

    Vector resVector = {0, 0};

    for (auto& lion : curWorld.lionsArray_) {
        if (sqr_dist(lion.position_, curZebra.position_) < curZebra.vision_ * curZebra.vision_) {
            resVector += lion.position_ - curZebra.position_; //find result vector
        }
    }

    if (resVector.x_ != 0 || resVector.y_ != 0) { //check if lions around
        resVector *= -1;
        curZebra.nextAction_ = Action::GO;
        curZebra.direction_ = find_correct_vec(curZebra, resVector, curWorld);
        return;   
    }

    if (ready_for_reprod(curZebra)) {
        reproduce<Zebra>(curZebra, curWorld.zebrasArray_, curWorld);
        return;
    }
    nutrition<Grass>(curZebra, curWorld.grassArray_, curWorld);
    curZebra.nextAction_ = Action::GO;
}
