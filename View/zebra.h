#ifndef ZEBRA_H_
#define ZEBRA_H_

#include "../include/Zebra.hpp"

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

using namespace world;

class ZebraView : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	ZebraView(QObject* parent = nullptr);
	~ZebraView();

	void set_location(Zebra zebra);

	Point position_;
	qreal angle_;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ZEBRA_H_