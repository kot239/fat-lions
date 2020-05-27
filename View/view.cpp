#include "view.h"
#include "ui_view.h"
#include <iostream>

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
        animal = new AnimalView(color, animals[j]);
        scene_->addItem(animal);
        animals_view_.push_back(animal);
        animal->setPos(animal->position_.x_, animal->position_.y_);
        //connect(animal, SIGNAL(signal1()), this, SLOT(slot_animal_information()));
    }
}

void View::add_grass(const std::vector<Grass> grass) {
    for (size_t j = 0; j < grass.size(); j++) {
        GrassView* grass_rec;
        grass_rec = new GrassView(grass[j]);
        scene_->addItem(grass_rec);
        grass_rec->setPos(grass_rec->position_.x_, grass_rec->position_.y_);
    }
}

void View::add_obstacles(const std::vector<Polygon> obsts) {
    for (size_t j = 0; j < obsts.size(); j++) {
        ObstacleView* obs;
        obs = new ObstacleView(obsts[j]);
        scene_->addItem(obs);
        obs->setPos(obs->position_.x_, obs->position_.y_);
    }
}

void View::add_background() {
    QGraphicsRectItem* bg = new QGraphicsRectItem(10, 10, 621, 471);
    bg->setBrush(QColor(204, 255, 153, 130));
    scene_->addItem(bg);
}

void View::clear_scene() {
    animals_view_.clear();
    QList<QGraphicsItem*> all = scene_->items();
    for(int i = 0; i < all.size(); i++) {
    QGraphicsItem *obj = all[i];
        scene_->removeItem(obj);
        delete obj;
        scene_->update();
    }
}

void View::update_world() {
    //scene_->clear();
    slot_animal_information();
    clear_scene();

    add_background();
    add_obstacles(world->obstaclesArray_);
    add_grass(world->grassArray_);
    add_animals(world->zebrasArray_, ZEBRA_COLOR);
    add_animals(world->lionsArray_, LION_COLOR);

    for (auto& curZebra : world->zebrasArray_) {
        rlogic->find_target_zebra(curZebra);
    }

    for (auto& curLion : world->lionsArray_) {
        rlogic->find_target_lion(curLion);
    }
    world->update();

    chart_->draw_chart(world->lionsArray_.size(), world->zebrasArray_.size());
}

void View::stop_game() {
    timer->stop();
    clear_scene();
    world->obstaclesArray_.clear();
    world->lionsArray_.clear();
    world->zebrasArray_.clear();
    world->grassArray_.clear();
    chart_->clean();
    ui_->start_button->setEnabled(true);
    ui_->pic->setPixmap(*animal_png_);
    ui_->who->setText("Who");
    ui_->sex->setText("Sex");
    return;
}

void View::start_game() {
    number_of_lions_ = ui_->lions_numb->value();
    number_of_zebras_ = ui_->zebras_numb->value();
    ui_->start_button->setEnabled(false);
    for (int i = 0; i < 10; ++i) {
        Polygon tmp(world->obstaclesArray_);
        if (tmp.coord_.size() > 0) {
            world->obstaclesArray_.push_back(tmp);
        }
    }
    for (int i = 0; i < number_of_zebras_; i++) {
        Zebra tmp;
        tmp.position_ = world->get_good_position();
        world->zebrasArray_.push_back(tmp);
    }
    for (int i = 0; i < number_of_lions_; i++) {
        Lion tmp;
        tmp.position_ = world->get_good_position();
        world->lionsArray_.push_back(tmp);
    }
    timer = new QTimer();
    timer->start(SECOND / FPS);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_world()));
    connect(ui_->stop_button, SIGNAL(clicked()), this, SLOT(stop_game()));
    return;
}

void View::slot_animal_information() {
    for (auto item: animals_view_) {
        if (item->clicked_) {
            ui_->who->setText(item->is_lion_ ? "Lion" : "Zebra");
            ui_->sex->setText(item->is_fem_ ? "Female" : "Male");
            if (item->is_lion_ && item->is_fem_)
                ui_->pic->setPixmap(*lion_f1_);
            if (item->is_lion_ && !item->is_fem_)
                ui_->pic->setPixmap(*lion_m1_);
            if (!item->is_lion_ && item->is_fem_)
                ui_->pic->setPixmap(*zebra_f1_);
            if (!item->is_lion_ && !item->is_fem_)
                ui_->pic->setPixmap(*zebra_m1_);
            item->clicked_ = false;
            break;
        }
    }
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

    animal_png_ = new QPixmap;
    animal_png_->load("../fat-lions/View/animal.png");
    lion_m1_ = new QPixmap;
    lion_m1_->load("../fat-lions/View/lion_m1.png");
    lion_f1_ = new QPixmap;
    lion_f1_->load("../fat-lions/View/lion_f1.png");
    zebra_m1_ = new QPixmap;
    zebra_m1_->load("../fat-lions/View/zebra_m1.png");
    zebra_f1_ = new QPixmap;
    zebra_f1_->load("../fat-lions/View/zebra_f1.png");

    qDebug() << QFile("../fat-lions/View/animal.png").exists();

    ui_->pic->setPixmap(*animal_png_);

    scene_->setSceneRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);

    connect(ui_->start_button, SIGNAL(clicked()), this, SLOT(start_game()));
    world = new World();
    vlogic = new VectorLogic(*world);
    rlogic = new RandomLogic(*world);   
   
}

View::~View() {
    delete rlogic;
    delete vlogic;
    delete world;
    delete ui_;
}
