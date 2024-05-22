// orderpage.h

#ifndef ORDERSPAGE_H
#define ORDERSPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QLabel>
#include <QMessageBox>
#include "../../../Entities/order/order.h"
#include "../static/header/headerwidget.h"
#include <QScrollBar>

#include "../../Services/order/OrderService.h"

class OrderPage : public QWidget {
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);

signals:
    void navigateToCatalog();

private slots:
    void onPriceRangeCheckboxStateChanged(int state);

    void onDateRangeCheckboxStateChanged(int state);

private:
    OrderService orderService;
    HeaderWidget *headerWidget;
    QTableWidget *ordersTable;
    QVBoxLayout *mainLayout;
    QCheckBox *priceRangeCheckbox;
    QLabel *lowestPriceLabel;
    QLabel *highestPriceLabel;
    QLineEdit *lowestPriceEdit;
    QLineEdit *highestPriceEdit;
    QCheckBox *dateRangeCheckbox;
    QLabel *startDateLabel;
    QLabel *endDateLabel;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;

    void setupUI();

    void populateOrders();
};

#endif // ORDERSPAGE_H
