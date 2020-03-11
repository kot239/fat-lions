#include "lion.h"

const char* LION_COLOR = "#FFCC33";

LionView::LionView(QObject* parent) : QObject(parent), QGraphicsItem(), angle_(0) {
	setRotation(angle_);
};

LionView::~LionView() {};

void LionView::slot_game_timer() {
    angle_ += 5;
    setRotation(angle_);
};

QRectF LionView::boundingRect() const {
	return QRectF(-30, -30, 60, 60);
};

void LionView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QPolygon polygon;
    polygon << QPoint(0, -10) << QPoint(5, 5) << QPoint(-5,5);
    painter->setBrush(QColor(LION_COLOR));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
