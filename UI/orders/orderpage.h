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
#include <QPushButton>
#include "../../../Entities/order/order.h"
#include "../static/header/headerwidget.h"
#include <QScrollBar>
#include "../../Services/order/OrderService.h"
#include "../../utils/TimeHelper.h"
#include "../diagram/transmissionchart.h"


class OrderPage : public QWidget {
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);

private slots:
    void onPriceRangeCheckboxStateChanged(int state);

    void showCarCatalogPage();

    void onDateRangeCheckboxStateChanged(int state);

    void showTransmissionChartPage();

    void onStartDateSelectionChanged();

    void onEndDateSelectionChanged();

    void onDeleteButtonClicked();

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
    QPushButton *deleteButton;

    void setupUI();

    void populateOrders();

    void populateTableWithOrders(const std::vector<Order> &orders);

    void filterOrdersByDateRange(const QDate &startDate, const QDate &endDate);
};

#endif // ORDERPAGE_H
