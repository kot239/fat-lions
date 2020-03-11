#include "view.h"
#include "ui_view.h"

const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 450;
const int MAP_H_CONOR = 20;
const int MAP_W_CONOR = 20;

View::View(QWidget* parent) : QWidget(parent), ui_(new Ui::View) {
    ui_->setupUi(this);
    scene_ = new QGraphicsScene();
    lion_ = new LionView();

    ui_->graphicsView->setScene(scene_);
    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui_->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_->setSceneRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);

    scene_->addItem(lion_);
    lion_->setPos(50, 50);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, lion_, &LionView::slot_game_timer);
    timer->start(1000 / 50);
}

View::~View() {
    delete ui_;
}

