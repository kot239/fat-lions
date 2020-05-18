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
            double r = fRand(curAnimal.velocity_ + 5, r0);
            dir *= r;
            Point new_pos = pos + dir;
            points_[i] = new_pos;
        }   
    }
    return points_;
}

double CountBenefits::count_benefits_for_lion(const Lion& curLion, 
                               const Point& point) {
    int coefHung = curLion.hunger_;
    int coefReprod = MAX_HUNGER - coefHung;
    Point startPoint = curLion.position_;
   // double lenPath = dist(point, startPoint);
    double pointBen = 0; 
    for (const auto& zebra : curWorld_.zebrasArray_) {
        if (dist(startPoint, zebra.position_) < curLion.vision_ &&
            dist(point, zebra.position_) < curLion.vision_ && 
            curWorld_.can_move(startPoint, zebra.position_) &&
            curWorld_.can_move(point, zebra.position_)) {
            pointBen += coefHung /(LEN_COEF * dist(point, zebra.position_));
        }
    }
    for (const auto& lion : curWorld_.lionsArray_) {
        if (lion.sex_ != curLion.sex_ &&
            lion.ready_for_reprod() &&
            dist(startPoint, lion.position_) < curLion.vision_ &&
            dist(point, lion.position_) < curLion.vision_ && 
            curWorld_.can_move(startPoint, lion.position_) &&
            curWorld_.can_move(point, lion.position_)) {
            pointBen += coefReprod / (LEN_COEF * dist(point, lion.position_));
        }
    }
    return pointBen;
}

template<typename T>
bool RandomLogic::reproduce(T& curAnimal, const std::vector<T>& animalArray) {
    if(curAnimal.ready_for_reprod()) {
        for (const auto& animal : animalArray) {
            if (animal.sex_ != curAnimal.sex_ &&
                animal.ready_for_reprod() &&
                dist(animal.position_, curAnimal.position_) < 10) {
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
        if (dist(curAnimal.position_, food.position_) < 10 ) {
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
    if (!curWorld_.can_move(curLion.position_, curLion.position_)) {
        std::cerr << curLion.position_.x_ << ' ' << curLion.position_.y_ << '\n';
        assert(false && "START_POINT_INCORRECT");
    }
    if(reproduce<Lion>(curLion, curWorld_.lionsArray_)) {
        return;
    }
    if (nutrition<Zebra>(curLion, curWorld_.zebrasArray_)) {
        return;
    }
    points_= generator_.generate_point(curLion);
    Point curPos = points_[0];
    Point optimalPoint = curPos;
    Point emergencyPoint = curPos;
    double maxBen = point_cost.count_benefits_for_lion(curLion, optimalPoint);
    bool has_optimal_point = false;
    bool has_emergency_point = false;
    for (const auto& point : points_) {
        if (curWorld_.can_move(curPos, point)) {
            double pointBen = point_cost.count_benefits_for_lion(curLion, point);
            if (pointBen > maxBen) {
                optimalPoint = point;
                maxBen = pointBen;
                has_optimal_point = true;
            } 
            emergencyPoint = point;
            has_emergency_point = true;
        }
    }
    if (has_optimal_point) {
        curLion.direction_ = optimalPoint - curPos;
        curLion.direction_.normalize();
        if (!curWorld_.can_move(curLion.position_, curLion.position_ + curLion.direction_ * curLion.velocity_)) {
            std::cerr << curPos.x_ << ' ' << curPos.y_ << '\n';        
            std::cerr << (curPos + curLion.direction_).x_  << ' ' << (curPos + curLion.direction_).y_ << '\n';
            assert(false);
        }
        curLion.nextAction_ = Action::GO; 
        return;
    }
    if (!curWorld_.can_move(curPos, curPos + curLion.direction_ * curLion.velocity_)) {
        if (has_emergency_point) {
            curLion.direction_ = emergencyPoint - curPos;
            curLion.direction_.normalize();
        }
        else {
            curLion.nextAction_ = Action::NOTHING;
            return;
        }
    } 
    if (!curWorld_.can_move(curLion.position_, curLion.position_ + curLion.direction_ * curLion.velocity_)) {
        std::cerr << curPos.x_ << ' ' << curPos.y_ << '\n';        
        std::cerr << (curPos + curLion.direction_).x_  << ' ' << (curPos + curLion.direction_).y_ << '\n';
        assert(curWorld_.can_move(curPos, curPos + curLion.direction_));
    } 
    curLion.nextAction_ = Action::GO; 
}
