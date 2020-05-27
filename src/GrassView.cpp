#include "GrassView.hpp"

#include <cmath>

GrassView::GrassView(const Grass& grass, QObject* parent) : QObject(parent), QGraphicsItem(), position_(grass.position_) {};

QRectF GrassView::boundingRect() const {
    return QRectF(-5, -5, 5, 5);
};

void GrassView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QPolygon polygon;
    polygon << QPoint(3, 3) << QPoint(-3, 3) << QPoint(-4, -4) << QPoint(-1, 0) << QPoint(0, -4) << QPoint(1, 0) << QPoint(4, -4);
    painter->setBrush(QColor("#339933"));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
