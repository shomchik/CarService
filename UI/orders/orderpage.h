#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QLabel>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include "../../../Entities/order/order.h"
#include "../static/header/headerwidget.h"
#include <QScrollBar>
#include "../../Services/order/OrderService.h"
#include "../../utils/TimeHelper.h"

class OrderPage : public QWidget {
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);

signals:
    void navigateToCatalog();

private slots:
    void onPriceRangeCheckboxStateChanged(int state);

    void onDateRangeCheckboxStateChanged(int state);

    void onStartDateSelectionChanged();

    void onEndDateSelectionChanged();

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
    QCalendarWidget *startDateCalendar;
    QCalendarWidget *endDateCalendar;

    void setupUI();

    void populateOrders();

    void populateTableWithOrders(const std::vector<Order> &orders);

    void filterOrdersByDateRange(const QDate &startDate, const QDate &endDate);
    void applyStyles();
};

#endif // ORDERPAGE_H
