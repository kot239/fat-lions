#ifndef GRASS_VIEW_H_
#define GRASS_VIEW_H_

#include "../include/Grass.hpp"

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

using namespace world;

class GrassView : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
    GrassView(const Grass& grass, QObject* parent = nullptr);
    ~GrassView() = default;

    Point position_;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GRASS_VIEW_H_
