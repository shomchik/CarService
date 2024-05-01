// You may need to build the project (run Qt uic code generator) to get "ui_OrdersPage.h" resolved
#include "orderspage.h"
#include <QHeaderView>
#include <QPushButton>

OrdersPage::OrdersPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void OrdersPage::setupUI()
{
    ordersTable = new QTableWidget(this);
    ordersTable->setColumnCount(3);
    ordersTable->setHorizontalHeaderLabels({"Order ID", "User ID", "Car ID"});
    ordersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ordersTable, &QTableWidget::cellDoubleClicked, this, &OrdersPage::openOrderDetails);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(ordersTable);
    setLayout(layout);
}

void OrdersPage::addOrder(const Order &order)
{
    int row = ordersTable->rowCount();
    ordersTable->insertRow(row);

    QTableWidgetItem *orderIdItem = new QTableWidgetItem(order.getId());
    QTableWidgetItem *userIdItem = new QTableWidgetItem(order.getClientId());
    QTableWidgetItem *carIdItem = new QTableWidgetItem(order.getCarId());

    ordersTable->setItem(row, 0, orderIdItem);
    ordersTable->setItem(row, 1, userIdItem);
    ordersTable->setItem(row, 2, carIdItem);
}

void OrdersPage::openOrderDetails(int row, int column)
{
    // Retrieve order details from the table
    QString orderId = ordersTable->item(row, 0)->text();
    QString userId = ordersTable->item(row, 1)->text();
    QString carId = ordersTable->item(row, 2)->text();

    // Emit signal to open order details page
    Order order(orderId, tm{}, tm{}, carId,userId, 0.0);
    emit viewOrderDetails(order);
}
