#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QLabel>

class View : public QWidget {

public:
    View(QWidget* parent = nullptr);
    ~View();

protected:
    void paintEvent(QPaintEvent* event);
    void draw_map();
    void draw_animals();

private:
    QLabel* animal;
};

#endif // VIEW_H
