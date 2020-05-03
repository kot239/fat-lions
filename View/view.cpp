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

    for (auto& curZebra : world.zebrasArray_) {
        logic.find_target_zebra(curZebra, world);
    }

    for (auto& curLion : world.lionsArray_) {
        logic.find_target_lion(curLion, world);
    }
    world.update();
    chart_->draw_chart(world.lionsArray_.size(), world.zebrasArray_.size());
}

void View::stop_game() {
    timer->stop();
    scene_->clear();
    world.zebrasArray_.clear();
    world.lionsArray_.clear();
    chart_->clean();
    ui_->start_button->setEnabled(true);
    return;
}

void View::start_game() {
    number_of_lions_ = ui_->lions_numb->value();
    number_of_zebras_ = ui_->zebras_numb->value();

    ui_->start_button->setEnabled(false);
    for (int i = 0; i < number_of_zebras_; i++) {
        Zebra tmp;
        world.zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < number_of_lions_; i++) {
        Lion tmp;
        world.lionsArray_.push_back(tmp);
    }
    timer = new QTimer();
    timer->start(SECOND / FPS);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_world()));
    connect(ui_->stop_button, SIGNAL(clicked()), this, SLOT(stop_game()));
    return;
}

View::View(QWidget* parent) : QWidget(parent), ui_(new Ui::View) {
    ui_->setupUi(this);
    scene_ = new QGraphicsScene();
    chart_ = new Chart();
    chart_->legend()->hide();

    ui_->map->setScene(scene_);
    ui_->map->setRenderHint(QPainter::Antialiasing);
    ui_->map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->chart_view->setChart(chart_);

    scene_->setSceneRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);

    connect(ui_->start_button, SIGNAL(clicked()), this, SLOT(start_game()));
}

View::~View() {
    delete ui_;
}
