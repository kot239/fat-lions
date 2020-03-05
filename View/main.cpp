#include "view.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char* argv[])
{
    // very important comand
    QApplication a(argc, argv);

    View w;

    w.resize(800, 600);
    w.setWindowTitle("Fat Lions");
    w.setWindowIcon(QIcon("icon.png"));
    w.show();

    //start of the game
    return a.exec();
}
