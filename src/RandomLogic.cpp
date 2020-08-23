#include "../include/RandomLogic.hpp"
#include "../include/World.hpp"
#include <vector>
#include <random>
#include "../include/Geometry.hpp"
#include <iostream>
#include <assert.h>

using namespace world;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

const std::vector<Point>& PointGenerator::generate_point(const Animal& curAnimal) {
    Point pos = curAnimal.position_;
    double x0 = curAnimal.position_.x_;
    double y0 = curAnimal.position_.y_;
    points_[0] = curAnimal.position_;
    double r0 = curAnimal.vision_;
    for (int i = 1; i < NUMBER_OF_POINTS; i++) {
        double x = rand() % MAXX;
        double y = rand() % MAXY;
        if (!(abs(x - x0) < 0.0001 && abs(y - y0) < 0.0001)) {
            Vector dir(x - x0, y - y0);
            dir.normalize();
            double r = fRand(curAnimal.velocity_, r0);
            dir *= r;
            Point new_pos = pos + dir;
            points_[i] = new_pos;
        }   
    }
    return points_;
}

template<typename T>
double CountBenefits::count_benefits_food(const Animal& curAnimal,
                                          const std::vector<T>& foodArray,
                                          const Point& point) {
    int coefHung = curAnimal.hunger_;
    Point startPoint = curAnimal.position_;
    double pointBen = 0; 
    for (const auto& food : foodArray) {
        if (dist(startPoint, food.position_) < curAnimal.vision_ &&
            dist(point, food.position_) < curAnimal.vision_ && 
            curWorld_.can_move(startPoint, food.position_) &&
            curWorld_.can_move(point, food.position_)) {

            pointBen += coefHung /(LEN_COEF * dist(point, food.position_));
        }
    }
    return pointBen;
}

template<typename T>
double CountBenefits::count_benefits_reprod(const T& curAnimal,
                                          const std::vector<T>& animalArray,
                                          const Point& point) {
    int coefReprod = MAX_HUNGER - curAnimal.hunger_;
    Point startPoint = curAnimal.position_;
    double pointBen = 0; 
    for (const auto& animal : animalArray) {
        if (animal.sex_ != curAnimal.sex_ &&
            animal.ready_for_reprod() &&
            dist(startPoint, animal.position_) < curAnimal.vision_ &&
            dist(point, animal.position_) < curAnimal.vision_ && 
            curWorld_.can_move(startPoint, animal.position_) &&
            curWorld_.can_move(point, animal.position_)) {

            pointBen += coefReprod / (LEN_COEF * dist(point, animal.position_));
        }
    }
    return pointBen;
}

double CountBenefits::count_benefits_for_lion(const Lion& curLion, 
                               const Point& point) {
    double pointBen = 0; 
    pointBen += count_benefits_food<Zebra>(curLion, curWorld_.zebrasArray_, point);
    if (curLion.ready_for_reprod()) {
        pointBen += count_benefits_reprod<Lion>(curLion, curWorld_.lionsArray_, point);
    }
    return pointBen;
}


double CountBenefits::count_benefits_for_zebra(const Zebra& curZebra, 
                               const Point& point) {
    double pointBen = 0; 
    Point startPoint = curZebra.position_;

    pointBen += count_benefits_food<Grass>(curZebra, curWorld_.grassArray_, point);
    if (curZebra.ready_for_reprod()) {
        pointBen += count_benefits_reprod<Zebra>(curZebra, curWorld_.zebrasArray_, point);
    }
    for (const auto& lion : curWorld_.lionsArray_) {
        if (dist(lion.position_, startPoint) < curZebra.vision_ && 
            dist(point, lion.position_) < curZebra.vision_ &&
            curWorld_.can_move(startPoint, lion.position_) &&
            curWorld_.can_move(point, lion.position_)) {

            pointBen += DANGER_COST / (LEN_COEF * dist(point, lion.position_));
        }
    }
    return pointBen;
}

void RandomLogic::check_errors(world::Animal& curAnimal) {
    Point curPos = curAnimal.position_;
    if (!curWorld_.can_move(curAnimal.position_, curAnimal.position_ + curAnimal.direction_ * curAnimal.velocity_)) {
        std::cerr << curPos.x_ << ' ' << curPos.y_ << '\n';        
        std::cerr << (curPos + curAnimal.direction_).x_  << ' ' << (curPos + curAnimal.direction_).y_ << '\n';
        assert(false);
    }
}

template<typename T>
bool RandomLogic::reproduce(T& curAnimal, const std::vector<T>& animalArray) {
    if(curAnimal.ready_for_reprod()) {
        for (const auto& animal : animalArray) {
            if (animal.sex_ != curAnimal.sex_ &&
                animal.ready_for_reprod() &&
                dist(animal.position_, curAnimal.position_) < curAnimal.velocity_ ) {
                curAnimal.nextAction_ = Action::REPRODUCE;
                return true;
            }
        }
    }
    return false;
}

template<typename T>
bool RandomLogic::nutrition(Animal& curAnimal, const std::vector<T>& foodArray) {
    for (const auto& food : foodArray) {
        if (dist(curAnimal.position_, food.position_) < curAnimal.velocity_ ) {
            curAnimal.nextAction_ = Action::EAT;
            return true;
        }
    }
    return false;
}

void RandomLogic::find_target_lion(Lion& curLion) {
    if (curLion.is_dead()) {
        return;
    }
    if(reproduce<Lion>(curLion, curWorld_.lionsArray_)) {
        return;
    }
    if (nutrition<Zebra>(curLion, curWorld_.zebrasArray_)) {
        return;
    }
    points_= generator_.generate_point(curLion);
    Point curPos = points_[0];
    set_start_value(curPos);
    double maxBen = point_cost_.count_benefits_for_lion(curLion, optimalPoint_);
    for (const auto& point : points_) {
        if (curWorld_.can_move(curPos, point)) {
            double pointBen = point_cost_.count_benefits_for_lion(curLion, point);
            if (pointBen > maxBen) {
                optimalPoint_ = point;
                maxBen = pointBen;
                has_optimal_point_ = true;
            } 
            emergencyPoint_ = point;
            has_emergency_point_ = true;
        }
    }
    update_dir(curLion);
}

bool RandomLogic::inDanger(Zebra& curZebra) {
    for (const auto& lion : curWorld_.lionsArray_) {
        if (dist(lion.position_, curZebra.position_) < curZebra.vision_) {
            return true;
        }
    }
    return false;
}

void RandomLogic::find_target_zebra(Zebra& curZebra) {
    if (curZebra.is_dead()) {
        return;
    }
    if (!inDanger(curZebra)) {
        if (reproduce<Zebra>(curZebra, curWorld_.zebrasArray_)) {
            return;
        }
        if (nutrition<Grass>(curZebra, curWorld_.grassArray_)) {
            return;
        }
    }
    points_= generator_.generate_point(curZebra);
    Point curPos = points_[0];
    set_start_value(curPos);
    double maxBen = point_cost_.count_benefits_for_zebra(curZebra, optimalPoint_);
    for (const auto& point : points_) {
        if (curWorld_.can_move(curPos, point)) {
            double pointBen = point_cost_.count_benefits_for_zebra(curZebra, point);
            if (pointBen > maxBen) {
                optimalPoint_ = point;
                maxBen = pointBen;
                has_optimal_point_ = true;
            } 
            emergencyPoint_ = point;
            has_emergency_point_ = true;
        }
    }
    update_dir(curZebra);
}

void RandomLogic::set_start_value(const Point& curPos) {
    optimalPoint_ = curPos;
    emergencyPoint_ = curPos;
    has_optimal_point_ = false;
    has_emergency_point_ = false;
}

void RandomLogic::update_dir(Animal& curAnimal) {
    Point curPos = curAnimal.position_;
    if (has_optimal_point_) {
        curAnimal.direction_ = optimalPoint_ - curPos;
        curAnimal.direction_.normalize();   
        curAnimal.nextAction_ = Action::GO; 
        return;
    }
    if (!curWorld_.can_move(curPos, curPos + curAnimal.direction_ * curAnimal.velocity_)) {
        if (has_emergency_point_) {
            curAnimal.direction_ = emergencyPoint_ - curPos;
            curAnimal.direction_.normalize();
        }
        else {
            curAnimal.nextAction_ = Action::NOTHING;
            return;
        }
    } 
    curAnimal.nextAction_ = Action::GO; 
}
