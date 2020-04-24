#include "view.h"
#include "ui_view.h"


const char* LION_COLOR = "#FFCC33";
const char* ZEBRA_COLOR = "#999999";

const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 450;
const int MAP_H_CONOR = 20;
const int MAP_W_CONOR = 20;

const int SECOND = 1000;
const int FPS = 10;


template <typename T>
void View::add_animals(const std::vector<T>& animals, const char* color) {
    for (size_t j = 0; j < animals.size(); j++) {
        AnimalView* animal;
        animal = new AnimalView(color);
        animal->set_location(animals[j]);
        scene_->addItem(animal);
        animal->setPos(animal->position_.x_, animal->position_.y_);
    }
}
void View::update_world() {
    scene_->clear();

    add_animals(world.zebrasArray_, ZEBRA_COLOR);
    add_animals(world.lionsArray_, LION_COLOR);

    for (size_t j = 0; j < world.zebrasArray_.size(); j++) {
        logic.find_target_zebra(world.zebrasArray_[j], world);
    }

    for (size_t j = 0; j < world.lionsArray_.size(); j++) {
        logic.find_target_lion(world.lionsArray_[j], world);
    }
    world.update();
    chart_->draw_chart(world.lionsArray_.size(), world.zebrasArray_.size());
}

View::View(QWidget* parent) : QWidget(parent), ui_(new Ui::View) {
    ui_->setupUi(this);
    scene_ = new QGraphicsScene();
    chart_ = new Chart();
    chart_->legend()->hide();
    for (int i = 0; i < 10; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < 5; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }

    ui_->graphicsView->setScene(scene_);
    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui_->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->graphicsView_2->setChart(chart_);

    scene_->setSceneRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_world()));
    timer->start(SECOND / FPS);
}

View::~View() {
    delete ui_;
}
