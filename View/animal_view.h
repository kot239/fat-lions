#ifndef LION_H_
#define LION_H_

#include "../include/Lion.hpp"

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

using namespace world;

class AnimalView : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
    AnimalView(const char* color, QObject* parent = nullptr);
    ~AnimalView();

    void set_location(Animal animal);

	Point position_;
	qreal angle_;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    const char* color_;
};

#endif // LION_H_
