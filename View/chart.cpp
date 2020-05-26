#include "chart.h"

using namespace QtCharts;

Chart::Chart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    QChart(QChart::ChartTypeCartesian, parent, wFlags), x_l_(0), x_z_(0), range_x_(1000), range_y_(100) {

    series_lions_ = new QLineSeries;
    series_zebras_ = new QLineSeries;
    axis_x_ = new QValueAxis;
    axis_y_ = new QValueAxis;

    QPen alive_lions("#FFCC33");
    alive_lions.setWidthF(1.5);
    series_lions_->setPen(alive_lions);
    series_lions_->append(x_l_, y_l_);
    addSeries(series_lions_);

    QPen alive_zebras("#999999");
    alive_zebras.setWidthF(1.5);
    series_zebras_->setPen(alive_zebras);
    series_zebras_->append(x_z_, y_z_);
    addSeries(series_zebras_);

    addAxis(axis_x_,Qt::AlignBottom);
    addAxis(axis_y_,Qt::AlignLeft);
    series_lions_->attachAxis(axis_x_);
    series_lions_->attachAxis(axis_y_);
    series_zebras_->attachAxis(axis_x_);
    series_zebras_->attachAxis(axis_y_);
    axis_x_->setTickCount(0);
    axis_x_->setRange(0, range_x_);
    axis_y_->setRange(0, range_y_);
    axis_x_->setTickCount(2);
    //axis_y_->setTickCount(2);

}

void Chart::draw_chart(qreal lions_cnt, qreal zebras_cnt) {
    x_l_++;
    y_l_ = lions_cnt;
    QPen alive_lions("#FFCC33");
    alive_lions.setWidthF(1.5);
    series_lions_->setPen(alive_lions);
    series_lions_->append(x_l_, y_l_);
    x_z_++;
    y_z_ = zebras_cnt;

    QPen alive_zebras("#999999");
    alive_zebras.setWidthF(1.5);
    series_zebras_->setPen(alive_zebras);
    series_zebras_->append(x_z_, y_z_);

    if (x_l_ + 10 > range_x_) {
        range_x_++;
        axis_x_->setRange(0, range_x_);
    }

    if (y_l_ + 10 > range_y_ || y_z_ + 10 > range_y_) {
        range_y_++;
        axis_y_->setRange(0, range_y_);
    }

}

void Chart::clean() {
    series_lions_->clear();
    series_zebras_->clear();
    x_l_ = 0;
    x_z_ = 0;
    range_x_ = 1000;
    range_y_ = 100;
    axis_x_->setRange(0, range_x_);
    axis_y_->setRange(0, range_y_);
}
