#include "vector_logic_lion.h"

using namespace world;

bool VectorLogicLion::ready_for_sex(const Animal::Lion& curLion) {
    return curLion.get_age() >= AGE_FOR_SEX &&
           curLion.get_sexcd() &&
           curLion.get_hunger() >= HUNGER_FOR_SEX;
}

int VectorLogicLion::dist(Point a, Point b) {
    return (a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_);
}

Vector VectorLogicZebra::find_correct_vec(const Animal::Lion& curLion, Vector resVector, const World& curWorld) {
    int timeToThink = 5;
    while (!curWorld.can_move(curZebra.get_position() + resVector * curLion.get_velocity())
            && timeToThink > 0) {
        resVector.x_ *= -1;
        --timeToThink;
    }
    return resVector;
}

void VectorLogicLion::find_target(Animal::Lion curLion) {
    if (curLion.get_age() >= MAX_AGE || curLion.get_hunger() == MAX_HUNGER) {
        curLion.nextAction_ = Action::DIE;
        return;
    }
    if (ready_for_sex(curLion)) {
        for (auto lion : lionsArray_) {
            int cur_dist = dist(lion.get_position(), curLion.get_position());
            if (lion.get_sex() != curLion.get_sex() && ready_for_sex(lion) &&
                (cur_dist < curLion.get_vision() * curLion.get_vision())) {

                if (lion.get_position() == curLion.get_position()) {
                    lion.nextAction_ = (get_sex() == FEMALE) ? REPRODUCE : NOTHING;
                    curLion.nextAction_ = (get_sex() == FEMALE) ? REPRODUCE : NOTHING;
                    return;
                }
                if (min_dist == -1 || cur_dist < min_dist) {
                    min_dist = cur_dist;
                    resVector = lion.get_position() - curLion.get_position();
                }
            }
        }
        curLion.nextAction_ = find_correct_vec(curLion, resVector, curWorld);
        return;
    }
    int min_dist = -1;
    for (auto zebra : zebrasArray_) {
        cur_dist = dist(zebra.get_position(), curLion.get_position());
        if (cur_dist < curLion.get_vision() * curLion.get_vision() &&
            (min_dist == -1 || cur_dist < min_dist)) {

            min_dist = cur_dist;
            resVector = grass.get_position() - curLion.get_position();
        }
    }
    if (resVector.x_ != 0 || resVector.y_ != 0) {
        curLion.nextAction_ = find_correct_vec(curLion, resVector, curWorld);
        return;
    }
    curLion.nextAction_ = curLion.get_direction();
}
