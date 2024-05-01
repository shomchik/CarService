#ifndef ORDERSPAGE_H
#define ORDERSPAGE_H

#include <QtWidgets>
#include <QTableWidget>
#include "../../../Entities/order/Order.h"

class OrdersPage : public QWidget
{
    Q_OBJECT
public:
    explicit OrdersPage(QWidget *parent = nullptr);

    signals:
            void viewOrderDetails(const Order &order);

public slots:
            void addOrder(const Order &order);

private slots:
            void openOrderDetails(int row, int column);

private:
    QTableWidget *ordersTable;

    void setupUI();
};

#endif // ORDERSPAGE_H
