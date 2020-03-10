#include "view.h"
#include "ui_view.h"

const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 450;
const int MAP_H_CONOR = 20;
const int MAP_W_CONOR = 20;

View::View(QWidget* parent) : QWidget(parent), ui(new Ui::View) {
    ui->setupUi(this);
    scene_ = new QGraphicsScene();
    lion_ = new LionView();

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_->setSceneRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);

    scene_->addItem(lion_);
    lion_->setPos(50, 50);
}

View::~View() {
    delete ui;
}

