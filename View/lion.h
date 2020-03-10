#ifndef LION_H_
#define LION_H_

#include <QGraphicsItem>
#include <QPainter>

class LionView : public QGraphicsItem {
public:
	LionView();
	~LionView();

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // LION_H_