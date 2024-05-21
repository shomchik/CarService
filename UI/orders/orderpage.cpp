#include "orderpage.h"
#include <QScrollBar>
#include <QApplication>
#include <qdesktopwidget.h>
#include <qheaderview.h>
#include <QMessageBox>

#include "../../Services/order/OrderService.h"
#include "../../utils/TimeHelper.h"

using namespace std;

OrderPage::OrderPage(QWidget *parent) : QWidget(parent) {
    setupUI();
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
    ordersTable->setAlternatingRowColors(true); // Alternate row colors
    ordersTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ordersTable->setColumnCount(6);
    QStringList headers = {
        "Идентификатор заказа", "Начало", "Конец", "Идентификатор машины", "Идентификатор клиента", "Цена"
    };
    ordersTable->setHorizontalHeaderLabels(headers);
    ordersTable->horizontalHeader()->setStyleSheet("background-color: #ccc;");

    int tableWidth = QApplication::desktop()->width();
    for (int i = 0; i < 6; ++i) {
        ordersTable->setColumnWidth(i, tableWidth / 6);
    }

    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(ordersTable);

    setLayout(mainLayout);

    connect(headerWidget, &HeaderWidget::catalogClicked, this, &OrderPage::navigateToCatalog);

    populateOrders();
}

void OrderPage::populateOrders() {
    ordersTable->clearContents();
    ordersTable->setRowCount(0);

    try {
        std::vector<Order> orders = orderService.getAllOrders();

        ordersTable->setRowCount(static_cast<int>(orders.size()));

        for (int i = 0; i < static_cast<int>(orders.size()); ++i) {
            const Order &order = orders.at(i);
            QTableWidgetItem *idItem = new QTableWidgetItem(order.getId());
            QTableWidgetItem *startDateItem = new QTableWidgetItem(TimeHelper::tmToQString(order.getStartDate()));
            QTableWidgetItem *endDateItem = new QTableWidgetItem(TimeHelper::tmToQString(order.getEndDate()));
            QTableWidgetItem *carIdItem = new QTableWidgetItem(order.getCarId());
            QTableWidgetItem *clientIdItem = new QTableWidgetItem(order.getClientId());

            QString priceString = QString::number(order.getPrice());
            QTableWidgetItem *priceItem = new QTableWidgetItem(priceString);

            ordersTable->setItem(i, 0, idItem);
            ordersTable->setItem(i, 1, startDateItem);
            ordersTable->setItem(i, 2, endDateItem);
            ordersTable->setItem(i, 3, carIdItem);
            ordersTable->setItem(i, 4, clientIdItem);
            ordersTable->setItem(i, 5, priceItem);
        }
    } catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        QMessageBox::critical(this, "Error",
                              "Failed to load orders due to invalid argument: " + QString::fromStdString(e.what()));
    } catch (const std::out_of_range &e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        QMessageBox::critical(this, "Error",
                              "Failed to load orders due to out of range error: " + QString::fromStdString(e.what()));
    } catch (const std::exception &e) {
        std::cerr << "Error populating orders: " << e.what() << std::endl;
        QMessageBox::critical(this, "Error", "Failed to load orders: " + QString::fromStdString(e.what()));
    } catch (...) {
        std::cerr << "An unknown error occurred while populating orders." << std::endl;
        QMessageBox::critical(this, "Error", "An unknown error occurred while loading orders.");
    }
}
