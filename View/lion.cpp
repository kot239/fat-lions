#include "lion.h"

#include <cmath>

const char* LION_COLOR = "#FFCC33";

const double PI = 3.14159265;

LionView::LionView(QObject* parent) : QObject(parent), QGraphicsItem() {};

LionView::~LionView() {};

void LionView::set_location(Lion lion) {
    position_ = lion.position_;
    double arg = double(lion.direction_.y_) / sqrt(double(lion.direction_.x_ * lion.direction_.x_ + lion.direction_.y_ * lion.direction_.y_));
    if (lion.direction_.x_ >= 0) {
        angle_ = acos(arg) * 180.0 / PI;
    } else {
        angle_ = 360.0 - acos(arg) * 180.0 / PI;
    }
    setRotation(angle_);
};

QRectF LionView::boundingRect() const {
	return QRectF(-30, -30, 60, 60);
};

void LionView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QPolygon polygon;
    polygon << QPoint(0, -10) << QPoint(5, 5) << QPoint(-5,5);
    painter->setBrush(QColor(LION_COLOR));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
