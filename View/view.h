#ifndef VIEW_H_
#define VIEW_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QtCharts/QChartView>
#include <QPushButton>
#include <QInputDialog>
#include <QList>
#include <QDebug>
#include <QFile>
#include <string>

#include "animal_view.h"
#include "chart.h"
#include "grass_view.h"
#include "obstacles_view.h"
#include "../include/World.hpp"
#include "../include/VectorLogic.hpp"

namespace Ui {
class View;
}

class View : public QWidget {

    Q_OBJECT

signals:

public slots:
    void update_world();
    void start_game();
    void stop_game();

public:
    explicit View(QWidget* parent = nullptr);
    ~View();

private:
    Ui::View* ui_;
    QGraphicsScene* scene_;
    QTimer* timer;
    World* world = nullptr;
    VectorLogic* logic = nullptr;
    Chart* chart_;
    QList<AnimalView*> animals_view_;
    int number_of_lions_ = 1;
    int number_of_zebras_ = 1;

    QPixmap* lion_m1_;
    QPixmap* lion_f1_;
    QPixmap* zebra_m1_;
    QPixmap* zebra_f1_;
    QPixmap* animal_png_;

    template <typename T>
    void add_animals(const std::vector<T>& animals, const char* color);
    void add_grass(const std::vector<Grass> grass_);
    void add_obstacles(const std::vector<Polygon> obsts);
    void add_background();
    void clear_scene();
    void slot_animal_information();

private slots:
};

#endif // VIEW_H_
