#ifndef OBSTACLE_VIEW_H_
#define OBSTACLE_VIEW_H_

#include "Geometry.hpp"

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

using namespace world;

class ObstacleView : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
    ObstacleView(const Polygon obst, QObject* parent = nullptr);
    ~ObstacleView() = default;

    Point position_;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	Polygon obst_;
};

#endif // OBSTACLE_VIEW_H_
