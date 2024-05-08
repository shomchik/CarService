#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

class HeaderWidget : public QWidget {
Q_OBJECT
public:
    explicit HeaderWidget(QWidget *parent = nullptr);

signals:
    void catalogClicked();
    void ordersClicked();

private:
    QLabel *headerLabel;
    QPushButton *catalogButton;
    QPushButton *ordersButton;

private slots:
    void onCatalogClicked();
    void onOrdersClicked();
};

#endif // HEADERWIDGET_H
