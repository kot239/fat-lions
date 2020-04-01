#ifndef VIEW_H_
#define VIEW_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QLabel>

#include "animal_view.h"
#include "../include/World.hpp"
#include "../include/vector_logic_lion.h"
#include "../include/vector_logic_zebra.h"

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
    Ui::View* ui_;
    QGraphicsScene* scene_;
    QTimer* timer;
    World world;
    VectorLogicLion logicLion;
    VectorLogicZebra logicZebra;

    template <typename T>
    void add_animals(const std::vector<T>& animals, const char* color);
};

#endif // VIEW_H_