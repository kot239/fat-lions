#include "../include/vector_logic_lion.h"
#include "../include/World.hpp"
#include <iostream>

using namespace world;

bool VectorLogicLion::ready_for_sex(const Lion& curLion) {
    return curLion.get_age() >= AGE_FOR_SEX &&
           curLion.get_sexcd() &&
           curLion.get_hunger() >= HUNGER_FOR_SEX;
}

int VectorLogicLion::dist(Point a, Point b) {
    return (a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_);
}

Vector VectorLogicLion::find_correct_vec(const Lion& curLion, Vector resVector, const World& curWorld) {
    int timeToThink = 5;
    while (!curWorld.can_move(curLion.get_position() + resVector * curLion.velocity_)
            && timeToThink > 0) {
        resVector.x_ *= -1;
        --timeToThink;
    }
    return resVector;
}

void VectorLogicLion::find_target(Lion& curLion, World& curWorld) {
    if (curLion.get_age() >= MAX_AGE || curLion.get_hunger() == MAX_HUNGER) {
        curLion.nextAction_ = Action::DIE;
        return;
    }
    int cur_dist;
    int min_dist = -1;
    Vector resVector = {0, 0};
    if (ready_for_sex(curLion)) {
        for (auto lion : curWorld.lionsArray_) {
            cur_dist = dist(lion.get_position(), curLion.get_position());
            if (lion.get_sex() != curLion.get_sex() && ready_for_sex(lion) &&
                (cur_dist < curLion.get_vision() * curLion.get_vision())) {

                if (lion.get_position() == curLion.get_position()) {
                    lion.nextAction_ = (lion.get_sex() == Sex::FEMALE) ? Action::REPRODUCE : Action::NOTHING;
                    curLion.nextAction_ = (curLion.get_sex() == Sex::FEMALE) ? Action::REPRODUCE : Action::NOTHING;
                    return;
                }
                if (min_dist == -1 || cur_dist < min_dist) {
                    min_dist = cur_dist;
                    resVector = lion.get_position() - curLion.get_position();
                }
            }
        }
        curLion.nextAction_ = Action::GO;
        curLion.direction_ = find_correct_vec(curLion, resVector, curWorld);
        return;
    }
    min_dist = -1;
    for (auto zebra : curWorld.zebrasArray_) {
        cur_dist = dist(zebra.get_position(), curLion.get_position());
        if (cur_dist < curLion.get_vision() * curLion.get_vision() &&
            (min_dist == -1 || cur_dist < min_dist)) {

            min_dist = cur_dist;
            resVector = zebra.get_position() - zebra.get_position();
        }
    }
    if (resVector.x_ != 0 || resVector.y_ != 0) {
        curLion.nextAction_ = Action::GO;
        curLion.direction_ = find_correct_vec(curLion, resVector, curWorld);
        return;
    }
    curLion.nextAction_ = Action::GO;
}
