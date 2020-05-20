#include "animal_view.h"

#include <cmath>

//const char* LION_COLOR = "#FFCC33";

const double PI = 3.14159265;

AnimalView::AnimalView(const char* color, const Animal& animal, QObject* parent) : QObject(parent), QGraphicsItem(),
        position_(animal.position_), clicked_(false), color_(color){
    double arg = double(animal.direction_.y_ * (-1)) / sqrt(double(animal.direction_.x_ * animal.direction_.x_ + animal.direction_.y_ * animal.direction_.y_));
    if (animal.direction_.x_ >= 0) {
        angle_ = acos(arg) * 180.0 / PI;
    } else {
        angle_ = 360.0 - acos(arg) * 180.0 / PI;
    }
    setRotation(angle_);
    is_lion_ = (strcmp(color_, "#FFCC33") == 0 ? true : false);
    is_fem_ = (animal.sex_ == Sex::FEMALE ? true : false);
};

QRectF AnimalView::boundingRect() const {
    return QRectF(-50, -50, 50, 50);
};

void AnimalView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (is_lion_) {
        QPolygon body;
        body << QPoint(3, -3) << QPoint(3, 3) << QPoint(0, 4) << QPoint (0,5);
        body << QPoint(1, 6) << QPoint(0, 7) << QPoint(-1, 6) << QPoint (0,5);
        body << QPoint(0, 4) << QPoint(-3, 3) << QPoint(-3, -3);
        painter->setBrush(QColor(color_));
        painter->drawPolygon(body);
        QPolygon hair;
        hair << QPoint(3, -3) << QPoint(5, -5) << QPoint(3, -7) << QPoint (-3, -7) << QPoint(-5, -5) << QPoint(-3, -3);
        painter->setBrush(QColor("#663300"));
        painter->drawPolygon(hair);
    } else {
        QPolygon body;
        body << QPoint(4, 0) << QPoint(0, -9) << QPoint(-4, 0) << QPoint(-4, 4) << QPoint(4, 4);
        painter->setBrush(QColor("#FFFFFF"));
        painter->drawPolygon(body);
        QPolygon tail;
        tail << QPoint(0, 4) << QPoint(0, 6) << QPoint(1, 6) << QPoint(0, 7) << QPoint(-1, 6) << QPoint(0, 6);
        painter->setBrush(QColor("#000000"));
        painter->drawPolygon(tail);
        QPolygon fst;
        fst << QPoint(4, 2) << QPoint(4, 4) << QPoint(-4, 4) << QPoint(-4, 2);
        painter->setBrush(QColor("#000000"));
        painter->drawPolygon(fst);
        QPolygon snd;
        snd << QPoint(3, -1) << QPoint(-3, -1) << QPoint(-2, -2) << QPoint(2, -2);
        painter->setBrush(QColor("#000000"));
        painter->drawPolygon(snd);
        QPolygon left;
        left << QPoint(-1, -7) << QPoint(-3, -6) << QPoint(-1, -5);
        painter->drawPolygon(left);
        QPolygon right;
        right << QPoint(1, -7) << QPoint(3, -6) << QPoint(1, -5);
        painter->drawPolygon(right);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
};

void AnimalView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit signal1();
    clicked_ = true;
    QGraphicsItem::mousePressEvent(event);
};
