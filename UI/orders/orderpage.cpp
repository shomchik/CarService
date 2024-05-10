// orderspage.cpp

#include "orderpage.h"
#include "../../../utils/TimeHelper.h"

OrderPage::OrderPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    populateOrders();
}

void OrderPage::setupUI() {
    headerWidget = new HeaderWidget(this);
    ordersTable = new QTableWidget(this);
    mainLayout = new QVBoxLayout(this);

    ordersTable->setStyleSheet(
            "QTableWidget { border: 1px solid #000; background-color: #fff; }");
    ordersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ordersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ordersTable->setVisible(false); // Hide vertical header
    ordersTable->setAlternatingRowColors(true); // Alternate row colors
    ordersTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add columns and set headers
    ordersTable->setColumnCount(6);
    QStringList headers = {"ID", "Start Date", "End Date", "Car ID", "Client ID", "Price"};
    ordersTable->setHorizontalHeaderLabels(headers);
    ordersTable->setStyleSheet("QHeaderView::section { background-color: #ccc; }");

    populateOrders();

    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(ordersTable);

    QScrollBar *verticalScrollBar = new QScrollBar(Qt::Vertical, this);
    mainLayout->addWidget(verticalScrollBar);

    setLayout(mainLayout);

    connect(headerWidget, &HeaderWidget::catalogClicked, [=]() {
        emit navigateToCatalog();
    });
}

void OrderPage::populateOrders() {
    ordersTable->setColumnCount(6);
    QStringList headers = {"ID", "Start Date", "End Date", "Car ID", "Client ID", "Price"};
    ordersTable->setHorizontalHeaderLabels(headers);

    QList<Order> orders = {
            Order("1", {0, 0, 0, 20, 3, 121, 0, 0, 0}, {0, 0, 0, 20, 3, 121, 0, 0, 0}, "1", "Client123", 1200.0),
            Order("2", {0, 0, 0, 19, 3, 121, 0, 0, 0}, {0, 0, 0, 19, 3, 121, 0, 0, 0}, "2", "Client456", 1500.0),
            Order("3", {0, 0, 0, 18, 3, 121, 0, 0, 0}, {0, 0, 0, 18, 3, 121, 0, 0, 0}, "3", "Client789", 1100.0),
            Order("4", {0, 0, 0, 17, 3, 121, 0, 0, 0}, {0, 0, 0, 17, 3, 121, 0, 0, 0}, "4", "Client321", 1350.0),
            Order("5", {0, 0, 0, 16, 3, 121, 0, 0, 0}, {0, 0, 0, 16, 3, 121, 0, 0, 0}, "5", "Client654", 980.0),
            Order("6", {0, 0, 0, 15, 3, 121, 0, 0, 0}, {0, 0, 0, 15, 3, 121, 0, 0, 0}, "6", "Client987", 1650.0),
            Order("7", {0, 0, 0, 14, 3, 121, 0, 0, 0}, {0, 0, 0, 14, 3, 121, 0, 0, 0}, "7", "Client234", 1400.0),
            Order("8", {0, 0, 0, 13, 3, 121, 0, 0, 0}, {0, 0, 0, 13, 3, 121, 0, 0, 0}, "8", "Client567", 1150.0),
            Order("9", {0, 0, 0, 12, 3, 121, 0, 0, 0}, {0, 0, 0, 12, 3, 121, 0, 0, 0}, "9", "Client890", 1250.0),
            Order("10", {0, 0, 0, 11, 3, 121, 0, 0, 0}, {0, 0, 0, 11, 3, 121, 0, 0, 0}, "10", "Client135", 1450.0),
            Order("11", {0, 0, 0, 10, 3, 121, 0, 0, 0}, {0, 0, 0, 10, 3, 121, 0, 0, 0}, "11", "Client468", 1000.0),
            Order("12", {0, 0, 0, 9, 3, 121, 0, 0, 0}, {0, 0, 0, 9, 3, 121, 0, 0, 0}, "12", "Client791", 1300.0),
            Order("13", {0, 0, 0, 8, 3, 121, 0, 0, 0}, {0, 0, 0, 8, 3, 121, 0, 0, 0}, "13", "Client224", 1550.0),
            Order("14", {0, 0, 0, 7, 3, 121, 0, 0, 0}, {0, 0, 0, 7, 3, 121, 0, 0, 0}, "14", "Client557", 1700.0),
            Order("15", {0, 0, 0, 6, 3, 121, 0, 0, 0}, {0, 0, 0, 6, 3, 121, 0, 0, 0}, "15", "Client890", 1250.0),
            Order("16", {0, 0, 0, 5, 3, 121, 0, 0, 0}, {0, 0, 0, 5, 3, 121, 0, 0, 0}, "16", "Client135", 1450.0),
            Order("17", {0, 0, 0, 4, 3, 121, 0, 0, 0}, {0, 0, 0, 4, 3, 121, 0, 0, 0}, "17", "Client468", 1000.0),
            Order("18", {0, 0, 0, 3, 3, 121, 0, 0, 0}, {0, 0, 0, 3, 3, 121, 0, 0, 0}, "18", "Client791", 1300.0),
            Order("19", {0, 0, 0, 2, 3, 121, 0, 0, 0}, {0, 0, 0, 2, 3, 121, 0, 0, 0}, "19", "Client224", 1550.0),
            Order("20", {0, 0, 0, 1, 3, 121, 0, 0, 0}, {0, 0, 0, 1, 3, 121, 0, 0, 0}, "20", "Client557", 1700.0),
    };

    ordersTable->setRowCount(orders.size());

    for (int i = 0; i < orders.size(); ++i) {
        Order order = orders.at(i);
        QTableWidgetItem *idItem = new QTableWidgetItem(order.getId());

        QTableWidgetItem *startDateItem = new QTableWidgetItem(TimeHelper::tmToQString(order.getStartDate()));
        QTableWidgetItem *endDateItem = new QTableWidgetItem(TimeHelper::tmToQString(order.getEndDate()));
        QTableWidgetItem *carIdItem = new QTableWidgetItem(order.getCarId());
        QTableWidgetItem *clientIdItem = new QTableWidgetItem(order.getClientId());
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(order.getPrice()));

        ordersTable->setItem(i, 0, idItem);
        ordersTable->setItem(i, 1, startDateItem);
        ordersTable->setItem(i, 2, endDateItem);
        ordersTable->setItem(i, 3, carIdItem);
        ordersTable->setItem(i, 4, clientIdItem);
        ordersTable->setItem(i, 5, priceItem);
    }
}
