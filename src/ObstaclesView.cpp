#include "include/ObstaclesView.hpp"

#include <cmath>

ObstacleView::ObstacleView(const Polygon obst, QObject* parent) : QObject(parent), QGraphicsItem(), obst_(obst) {
	position_.x_ = 0;
	position_.y_ = 0;
};

QRectF ObstacleView::boundingRect() const {
	return QRectF(0, 0, 100, 100);
};

void ObstacleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QPolygon polygon;
    for (auto pt: obst_.coord_)
    	polygon << QPoint(pt.x_, pt.y_);
    painter->setBrush(QColor("#666666"));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
