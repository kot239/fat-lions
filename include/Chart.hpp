#ifndef CHART_H_
#define CHART_H_

#include <QtCharts/QtCharts>
#include <QGraphicsItem>

using namespace QtCharts;

#include "World.hpp"

class Chart : public QChart {


public:
    Chart(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = nullptr);
	virtual ~Chart() = default;
    void draw_chart(qreal lions_cnt, qreal zebras_cnt);
    void clean();

private:
    QLineSeries* series_lions_;
    QLineSeries* series_zebras_;
	QValueAxis* axis_x_;
    QValueAxis* axis_y_;
    qreal x_l_, x_z_;
    qreal y_l_, y_z_;
    qreal range_x_, range_y_;
};

#endif // CHART_H_
