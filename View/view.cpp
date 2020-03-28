#include "view.h"
#include "ui_view.h"

#include <iostream>
//#include "animal_view.h"

const char* LION_COLOR = "#FFCC33";
const char* ZEBRA_COLOR = "#999999";

const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 450;
const int MAP_H_CONOR = 20;
const int MAP_W_CONOR = 20;
/*
void run_game(World& world, VectorLogicZebra& logicZebra, VectorLogicLion& logicLion) {
    for (int i = 0; i < 100; i++) {
        for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
            logicZebra.find_target(world.zebrasArray_[j], world);
        }

        for (size_t j = 0; j < world.lionsArray_.size(); j++) {
            logicLion.find_target(world.lionsArray_[j], world);
         //   std::cout << j << ' ' << (world.lionsArray_[j].position_.x_) << '\n';
        }
        world.update();
    }    
}
*/
void View::update_world() {
    scene_->clear();
    for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
        AnimalView* zebra;
        zebra = new AnimalView(ZEBRA_COLOR);
        zebra->set_location(world.zebrasArray_[j]);
        scene_->addItem(zebra);
        zebra->setPos(zebra->position_.x_, zebra->position_.y_);
    }
    for (size_t j = 0; j < world.lionsArray_.size(); j++) {
        AnimalView* lion;
        lion = new AnimalView(LION_COLOR);
        lion->set_location(world.lionsArray_[j]);
        scene_->addItem(lion);
        lion->setPos(lion->position_.x_, lion->position_.y_);
    }

    for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
        logicZebra.find_target(world.zebrasArray_[j], world);
    }

    for (size_t j = 0; j < world.lionsArray_.size(); j++) {
        logicLion.find_target(world.lionsArray_[j], world);
    }
    world.update();
}

View::View(QWidget* parent) : QWidget(parent), ui_(new Ui::View) {
    ui_->setupUi(this);
    scene_ = new QGraphicsScene();
    
    for (int i = 0; i < 5; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < 5; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }

    ui_->graphicsView->setScene(scene_);
    //ui_->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui_->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_->setSceneRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_world()));
    timer->start(1000);
}

View::~View() {
    delete ui_;
}

