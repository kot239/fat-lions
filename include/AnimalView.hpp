#ifndef LION_H_
#define LION_H_

#include "Animal.hpp"

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

using namespace world;

class AnimalView : public QObject, public QGraphicsItem {

	Q_OBJECT

signals:

public:
    AnimalView(const char* color, const Animal& animal, QObject* parent = nullptr);
    ~AnimalView() = default;

	Point position_;
	qreal angle_;
    bool clicked_;
    bool is_lion_;
    bool is_fem_;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    const char* color_;
};

#endif // LION_H_
