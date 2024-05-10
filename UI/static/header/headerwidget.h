#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class HeaderWidget : public QWidget {
Q_OBJECT
public:
    explicit HeaderWidget(QWidget *parent = nullptr);

signals:
    void catalogClicked();
    void ordersClicked();

private:
    QPushButton *catalogButton;
    QPushButton *ordersButton;
};

#endif // HEADERWIDGET_H
