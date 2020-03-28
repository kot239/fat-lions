#ifndef VIEW_H_
#define VIEW_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QLabel>

#include "lion.h"
#include "zebra.h"
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
    LionView* lion;
    Ui::View* ui_;
    QGraphicsScene* scene_;
    QTimer* timer;
    World world;
    VectorLogicLion logicLion;
    VectorLogicZebra logicZebra;
};

#endif // VIEW_H_
