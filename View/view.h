#ifndef VIEW_H_
#define VIEW_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QPushButton>
#include <QInputDialog>
#include <QList>

#include "animal_view.h"
#include "chart.h"
#include "grass_view.h"
#include "obstacles_view.h"
#include "../include/World.hpp"
#include "../include/VectorLogic.hpp"
#include "../include/RandomLogic.hpp"

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
    VectorLogic* vlogic = nullptr;
    RandomLogic* rlogic = nullptr;
    Chart* chart_;
    int number_of_lions_ = 1;
    int number_of_zebras_ = 1;

    template <typename T>
    void add_animals(const std::vector<T>& animals, const char* color);
    void add_grass(const std::vector<Grass> grass_);
    void add_obstacles(const std::vector<Polygon> obsts);
    void clear_scene();
};

#endif // VIEW_H_
