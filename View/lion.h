#ifndef LION_H_
#define LION_H_

#include "../include/Lion.hpp"

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

using namespace world;

class LionView : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	LionView(QObject* parent = nullptr);
	~LionView();

	void set_location(Lion lion);

	Point position_;
	qreal angle_;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // LION_H_