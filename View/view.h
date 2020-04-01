#ifndef VIEW_H_
#define VIEW_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QLabel>
#include <vector>

#include "animal_view.h"
//#include "zebra.h"
#include "../include/World.hpp"
#include "../include/vector_logic_lion.h"
#include "../include/vector_logic_zebra.h"
//#include "Geometry.hpp"

namespace Ui {
class View;
}

class View : public QWidget {

    Q_OBJECT

signals:

public slots:
    void update_world();

public:
    explicit View(QWidget* parent = nullptr);
    ~View();

private:
    AnimalView* lion;
    Ui::View* ui_;
    QGraphicsScene* scene_;
    QTimer* timer;
    World world;
    VectorLogicLion logicLion;
    VectorLogicZebra logicZebra;

    void add_animals(const std::vector<Animal> animals, const char* color);
};

#endif // VIEW_H_
