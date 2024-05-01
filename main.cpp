#include <QApplication>
#include <QPushButton>
#include "UI/cars/carcatalogpage.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CarCatalogPage home;
    home.show();
    return QApplication::exec();
}
