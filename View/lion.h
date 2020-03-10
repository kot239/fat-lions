#ifndef LION_H_
#define LION_H_

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

class LionView : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	LionView(QObject* parent = nullptr);
	~LionView();

signals:

public slots:
	void slot_game_timer();

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	qreal angle_;
};

#endif // LION_H_