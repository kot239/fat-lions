#include "World.hpp"

namespace world {

bool World::can_move(const Point pos) const {
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
	for (size_t i = 0; i < zebrasArray_.size(); ++i) {
		Zebra *zebra = &zebrasArray_[i];
		if (zebra->nextAction_ == Action::EAT) {
			zebra->make_move();
			for (size_t j = 0; j < grassArray_.size(); ++j) {
				if (grassArray_[j].get_position() == zebra->position_) {
					zebra->hunger_ -= GRASS_NUTRITION;
					grass_death(j);
					break;
				}
			}
		}
		if (zebra->nextAction_ == Action::DIE) {
			zebras_death(i);
			--i;
		}
		if (zebra->nextAction_ == Action::GO) {
			zebra->make_move();
		}
		if (zebra->nextAction_ == Action::REPRODUCE) {
			if (zebra->sex_ == Sex::FEMALE) {
				zebrasArray_.push_back(Zebra(*zebra));
			}
			zebra->sexcd_ = -1;
		}
		++zebra->age_;
		++zebra->sexcd_;
	}


	for (size_t i = 0; i < lionsArray_.size(); ++i) {
		Lion *lion = &lionsArray_[i];
		if (lion->nextAction_ == Action::EAT) {
			lion->make_move();
			for (size_t j = 0; j < zebrasArray_.size(); ++j) {
				if (zebrasArray_[j].position_ == lion->position_) {
					lion->hunger_ -= ZEBRAS_NUTRITION;
					zebras_death(j);
					break;
				}
			}
		}
		if (lion->nextAction_ == Action::DIE) {
			lions_death(i);
			--i;
		}
		if (lion->nextAction_ == Action::GO) {
			lion->make_move();
		}
		if (lion->nextAction_ == Action::REPRODUCE) {
			if (lion->sex_ == Sex::FEMALE) {
				lionsArray_.push_back(Lion(*lion));
			}
			lion->sexcd_ = -1;
		}
		++lion->age_;
		++lion->sexcd_;
	}



}

} //namespace world