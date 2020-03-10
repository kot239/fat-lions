#ifndef VIEW_H_
#define VIEW_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QLabel>

#include <lion.h>

namespace Ui {
class View;
}

class View : public QWidget {

    Q_OBJECT

public:
    explicit View(QWidget* parent = nullptr);
    ~View();

private:
    Ui::View* ui_;
    QGraphicsScene* scene_;
    LionView* lion_;
    QTimer* timer;
};

#endif // VIEW_H_
