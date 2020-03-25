#include "zebra.h"

#include <cmath>

const char* ZEBRA_COLOR = "#999999";

const double PI = 3.14159265;

ZebraView::ZebraView(QObject* parent) : QObject(parent), QGraphicsItem() {};

ZebraView::~ZebraView() {};

void ZebraView::set_location(Zebra zebra) {
    position_ = zebra.position_;
    double arg = double(zebra.direction_.y_) / sqrt(double(zebra.direction_.x_ * zebra.direction_.x_ + zebra.direction_.y_ * zebra.direction_.y_));
    if (zebra.direction_.x_ >= 0) {
        angle_ = acos(arg) * 180.0 / PI;
    } else {
        angle_ = 360.0 - acos(arg) * 180.0 / PI;
    }
    setRotation(angle_);
};

QRectF ZebraView::boundingRect() const {
	return QRectF(-30, -30, 60, 60);
};

void ZebraView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QPolygon polygon;
    polygon << QPoint(0, -10) << QPoint(5, 5) << QPoint(-5,5);
    painter->setBrush(QColor(ZEBRA_COLOR));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
