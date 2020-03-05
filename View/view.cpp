#include "view.h"

#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QPixMap>

const char* MAP_COLOR = "#CCCC99";
const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 450;
const int MAP_H_CONOR = 20;
const int MAP_W_CONOR = 20;

View::View(QWidget* parent) : QWidget(parent) {
}

View::~View() {
}

void View::paintEvent(QPaintEvent* event) {

	Q_UNUSED(event);

	draw_map();
	draw_animals();
}

void View::draw_map() {
	QPainter painter(this);
	QPen pen(Qt::black, 2, Qt::SolidLine);

	// draw map border

	painter.setPen(pen);
	painter.drawLine(MAP_W_CONOR, MAP_H_CONOR, 
		MAP_W_CONOR + MAP_WIDTH, MAP_H_CONOR);
	painter.drawLine(MAP_W_CONOR + MAP_WIDTH, MAP_H_CONOR,
		MAP_WIDTH + MAP_W_CONOR, MAP_H_CONOR + MAP_HEIGHT);
	painter.drawLine(MAP_W_CONOR + MAP_WIDTH, MAP_H_CONOR + MAP_HEIGHT,
		MAP_W_CONOR, MAP_H_CONOR + MAP_HEIGHT);
	painter.drawLine(MAP_W_CONOR, MAP_H_CONOR + MAP_HEIGHT,
		MAP_W_CONOR, MAP_H_CONOR);

	// draw map rectangle

	painter.setBrush(QBrush(MAP_COLOR));
	painter.setOpacity(0.3);
	painter.drawRect(MAP_W_CONOR, MAP_H_CONOR, MAP_WIDTH, MAP_HEIGHT);
};

void View::draw_animals() {
	animal = new QLabel(this);
	QPixmap image("lion.png");
	int w = image.width();
	int h = image.height();
	animal->setPixmap(image);
	animal->setGeometry(40, 40, w, h);
	animal->show();
};

