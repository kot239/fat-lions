#include "../include/World.hpp"
#include <iostream>

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

void World::zebras_death(size_t ind) {
	swap(zebrasArray_[ind], zebrasArray_.back());
	grassArray_.push_back(Grass(zebrasArray_[ind])); 
	zebrasArray_.pop_back();
}

void World::lions_death(size_t ind) {
	swap(lionsArray_[ind], lionsArray_.back());
	grassArray_.push_back(Grass(lionsArray_[ind])); 
	lionsArray_.pop_back();
}

void World::grass_death(size_t ind) {
	swap(grassArray_[ind], grassArray_.back());
	grassArray_.pop_back();
}

void World::update() {
	size_t cur_numb = lionsArray_.size();
	for (size_t i = 0; i < cur_numb; ++i) {
		Lion *lion = &lionsArray_[i];
		if (lion->nextAction_ == Action::EAT) {
			lion->make_move();
			for (size_t j = 0; j < zebrasArray_.size(); ++j) {
				if (abs(zebrasArray_[j].position_.x_- lion->position_.x_) < 10 && 
					abs(zebrasArray_[j].position_.y_- lion->position_.y_) < 10) {
					lion->hunger_ -= ZEBRAS_NUTRITION;
				    lion->nextAction_ = Action::GO;
					zebras_death(j);
					break;
				}
			}
		}
		if (lion->nextAction_ == Action::GO) {
			lion->make_move();
		}
		if (lion->nextAction_ == Action::REPRODUCE) {
			if (lion->sex_ == Sex::FEMALE) {
				Lion new_lion;
				new_lion.position_ = lion->position_;
				lionsArray_.push_back(new_lion);
			}
			lion->nextAction_ = Action::GO;

			lion->reprodCd_ = -1;
		}
		++lion->age_;
		++lion->reprodCd_;
		++lion->hunger_;
		if (lion->nextAction_ == Action::DIE) {
			lions_death(i);
			--i;
		}
	}
	cur_numb = zebrasArray_.size();
	for (size_t i = 0; i < cur_numb; ++i) {
		Zebra *zebra = &zebrasArray_[i];
		if (zebra->nextAction_ == Action::EAT) {
			zebra->make_move();
			for (size_t j = 0; j < grassArray_.size(); ++j) {
				if (grassArray_[j].get_position() == zebra->position_) {
					zebra->hunger_ -= GRASS_NUTRITION;
			        zebra->nextAction_ = Action::GO;

					grass_death(j);
					break;
				}
			}
		}
		if (zebra->nextAction_ == Action::GO) {
			zebra->make_move();
		}
		if (zebra->nextAction_ == Action::REPRODUCE) {
			if (zebra->sex_ == Sex::FEMALE) {
				Zebra new_zebra;
				new_zebra.position_ = zebra->position_;
				zebrasArray_.push_back(new_zebra);
			}
			zebra->nextAction_ = Action::GO;
			zebra->reprodCd_ = -1;
		}
		++zebra->age_;
		++zebra->hunger_;
		++zebra->reprodCd_;
		if (zebra->nextAction_ == Action::DIE) {
			zebras_death(i);
			--i;
		}
	}
}

} //namespace world