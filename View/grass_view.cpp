#include "grass_view.h"

#include <cmath>

GrassView::GrassView(const Grass& grass, QObject* parent) : QObject(parent), QGraphicsItem(), position_(grass.position_) {};

QRectF GrassView::boundingRect() const {
	return QRectF(-30, -30, 30, 30);
};

void GrassView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QPolygon polygon;
    polygon << QPoint(5, -5) << QPoint(-5, -5) << QPoint(-5, 5) << QPoint(5, 5);
    painter->setBrush(QColor("#339933"));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
