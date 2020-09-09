#include "HarmonographApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HarmonographApp w;
    w.show();
    return a.exec();
}
