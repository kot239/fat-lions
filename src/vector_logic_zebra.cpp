#include "vector_logic_zebra.h"
#include "World.hpp"

using namespace world;

bool VectorLogicZebra::ready_for_sex(const Zebra& curZebra) {
    return curZebra.get_age() >= AGE_FOR_SEX &&
           curZebra.get_sexcd() &&
           curZebra.get_hunger() >= HUNGER_FOR_SEX;
}

int VectorLogicZebra::dist(Point a, Point b) {
    return (a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_);
}

Vector VectorLogicZebra::find_correct_vec(const Zebra& curZebra, Vector resVector, const World& curWorld) {
    int timeToThink = 5;
    while (!curWorld.can_move(curZebra.get_position() + resVector * curZebra.velocity_)
            && timeToThink > 0) {
        resVector.x_ *= -1;
        --timeToThink;
    }
    return resVector;
}

void VectorLogicZebra::find_target(Zebra& curZebra, World& curWorld) {

    if (curZebra.get_age() >= MAX_AGE || curZebra.get_hunger() == MAX_HUNGER) {
        curZebra.nextAction_ = Action::DIE;
        return;
    }

    Vector resVector = {0, 0};
     // find_danger
    for (auto lion : curWorld.lionsArray_) {
        if (dist(lion.get_position(), curZebra.get_position()) < curZebra.get_vision() * curZebra.get_vision()) {
            resVector += lion.get_position() - curZebra.get_position(); //find result vector
        }
    }

    if (resVector.x_ != 0 || resVector.y_ != 0) { //check if lions around
        resVector *= -1;
        curZebra.nextAction_ = Action::GO;
        curZebra.direction_ = find_correct_vec(curZebra, resVector, curWorld);
        return;   
    }
    int cur_dist;
    int min_dist = -1;
     // find_zebra
    if (ready_for_sex(curZebra)) {
        for (auto zebra : curWorld.zebrasArray_) {
            cur_dist = dist(zebra.get_position(), curZebra.get_position());
            if (zebra.get_sex() != curZebra.get_sex() && ready_for_sex(zebra) &&
                (cur_dist < curZebra.get_vision() * curZebra.get_vision())) {

                if (zebra.get_position() == curZebra.get_position()) {
                    zebra.nextAction_ = (zebra.get_sex() == Sex::FEMALE) ? Action::REPRODUCE : Action::NOTHING;
                    curZebra.nextAction_ = (curZebra.get_sex() == Sex::FEMALE) ? Action::REPRODUCE : Action::NOTHING;
                    return;
                }
                if (min_dist == -1 || cur_dist < min_dist) {
                    min_dist = cur_dist;
                    resVector = zebra.get_position() - curZebra.get_position();
                }
            }
        }
        curZebra.direction_ = find_correct_vec(curZebra, resVector, curWorld);
        curZebra.nextAction_ = Action::GO;
        return;
    }
   // find_grass
    min_dist = -1;
    for (auto grass : curWorld.grassArray_) {
        cur_dist = dist(grass.get_position(), curZebra.get_position());
        if (cur_dist < curZebra.get_vision() * curZebra.get_vision() &&
            (min_dist == -1 || cur_dist < min_dist)) {

            min_dist = cur_dist;
            resVector = grass.get_position() - curZebra.get_position();
        }
    }
    if (resVector.x_ != 0 || resVector.y_ != 0) {
        curZebra.direction_ = find_correct_vec(curZebra, resVector, curWorld);
        curZebra.nextAction_ = Action::GO; 
        return;
    }
    curZebra.nextAction_ = Action::GO;
}
