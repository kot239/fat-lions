#include "view.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QPixmap>

int main(int argc, char* argv[])
{
    // very important comand
    std::srand(unsigned(std::time(0)));
    QApplication a(argc, argv);

    View w;

    w.resize(1000, 600);
    //w.setWindowTitle("Fat Lions");
    //w.setWindowIcon(QIcon("fat_lion.png"));
    w.show();

    //start of the game
    return a.exec();
}
