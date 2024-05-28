#include "orderpage.h"
#include <QScrollBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>

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

    priceRangeCheckbox = new QCheckBox("Price Range", this);
    lowestPriceLabel = new QLabel("Lowest Price:", this);
    lowestPriceEdit = new QLineEdit(this);
    highestPriceLabel = new QLabel("Highest Price:", this);
    highestPriceEdit = new QLineEdit(this);
    QHBoxLayout *priceRangeLayout = new QHBoxLayout();
    priceRangeLayout->addWidget(priceRangeCheckbox);
    priceRangeLayout->addWidget(lowestPriceLabel);
    priceRangeLayout->addWidget(lowestPriceEdit);
    priceRangeLayout->addWidget(highestPriceLabel);
    priceRangeLayout->addWidget(highestPriceEdit);
    priceRangeLayout->addStretch();

    dateRangeCheckbox = new QCheckBox("Date Range", this);
    startDateLabel = new QLabel("Start Date:", this);
    startDateEdit = new QDateEdit(this);
    startDateCalendar = new QCalendarWidget(this);
    endDateLabel = new QLabel("End Date:", this);
    endDateEdit = new QDateEdit(this);
    endDateCalendar = new QCalendarWidget(this);
    QHBoxLayout *dateRangeLayout = new QHBoxLayout();
    dateRangeLayout->addWidget(dateRangeCheckbox);
    dateRangeLayout->addWidget(startDateLabel);
    dateRangeLayout->addWidget(startDateEdit);
    dateRangeLayout->addWidget(startDateCalendar);
    dateRangeLayout->addWidget(endDateLabel);
    dateRangeLayout->addWidget(endDateEdit);
    dateRangeLayout->addWidget(endDateCalendar);
    dateRangeLayout->addStretch();

    QVBoxLayout *bottomLayout = new QVBoxLayout();
    bottomLayout->addLayout(priceRangeLayout);
    bottomLayout->addLayout(dateRangeLayout);
    bottomLayout->addStretch();

    mainLayout->addLayout(bottomLayout);

    connect(priceRangeCheckbox, &QCheckBox::stateChanged, this, &OrderPage::onPriceRangeCheckboxStateChanged);
    connect(dateRangeCheckbox, &QCheckBox::stateChanged, this, &OrderPage::onDateRangeCheckboxStateChanged);
    connect(startDateCalendar, &QCalendarWidget::selectionChanged, this, &OrderPage::onStartDateSelectionChanged);
    connect(endDateCalendar, &QCalendarWidget::selectionChanged, this, &OrderPage::onEndDateSelectionChanged);
}

void OrderPage::populateOrders() {
    ordersTable->clearContents();
    auto orders = orderService.getAllOrders();
    ordersTable->setRowCount(0);

    for (const auto &order : orders) {
        int row = ordersTable->rowCount();
        ordersTable->insertRow(row);

        QTableWidgetItem *itemId = new QTableWidgetItem(order.getId());
        QTableWidgetItem *itemStart = new QTableWidgetItem(TimeHelper::tmToQString(order.getStartDate()));
        QTableWidgetItem *itemEnd = new QTableWidgetItem(TimeHelper::tmToQString(order.getEndDate()));
        QTableWidgetItem *itemCarId = new QTableWidgetItem(order.getCarId());
        QTableWidgetItem *itemClientId = new QTableWidgetItem(order.getClientId());
        QTableWidgetItem *itemPrice = new QTableWidgetItem(QString::number(order.getPrice()));

        ordersTable->setItem(row, 0, itemId);
        ordersTable->setItem(row, 1, itemStart);
        ordersTable->setItem(row, 2, itemEnd);
        ordersTable->setItem(row, 3, itemCarId);
        ordersTable->setItem(row, 4, itemClientId);
        ordersTable->setItem(row, 5, itemPrice);
    }
}

void OrderPage::onPriceRangeCheckboxStateChanged(int state) {
    lowestPriceLabel->setEnabled(state == Qt::Checked);
    lowestPriceEdit->setEnabled(state == Qt::Checked);
    highestPriceLabel->setEnabled(state == Qt::Checked);
    highestPriceEdit->setEnabled(state == Qt::Checked);

    if (state == Qt::Checked) {
        // Filter orders based on price range
                double lowestPrice = lowestPriceEdit->text().toDouble();
        double highestPrice = highestPriceEdit->text().toDouble();
        auto filteredOrders = orderService.findOrdersByPriceRange(lowestPrice, highestPrice);

        // Populate the table with filtered orders
        populateTableWithOrders(filteredOrders);
    } else {
        // If the checkbox is unchecked, repopulate the table with all orders
        populateOrders();
    }
}

void OrderPage::onDateRangeCheckboxStateChanged(int state) {
    startDateLabel->setEnabled(state == Qt::Checked);
    startDateEdit->setEnabled(state == Qt::Checked);
    startDateCalendar->setEnabled(state == Qt::Checked);
    endDateLabel->setEnabled(state == Qt::Checked);
    endDateEdit->setEnabled(state == Qt::Checked);
    endDateCalendar->setEnabled(state == Qt::Checked);

    if (state == Qt::Checked) {
        // If the checkbox is checked, show the calendar widgets
        startDateCalendar->setHidden(false);
        endDateCalendar->setHidden(false);
    } else {
        // If the checkbox is unchecked, hide the calendar widgets
        startDateCalendar->setHidden(true);
        endDateCalendar->setHidden(true);
        // Repopulate the table with all orders
        populateOrders();
    }
}

void OrderPage::onStartDateSelectionChanged() {
    // Get the selected start date from the calendar widget
    QDate startDate = startDateCalendar->selectedDate();
    // Set the selected date in the date edit widget for display
    startDateEdit->setDate(startDate);
    // If the end date is also selected, filter orders
    if (endDateEdit->date().isValid()) {
        filterOrdersByDateRange(startDate, endDateEdit->date());
    }
}

void OrderPage::onEndDateSelectionChanged() {
    // Get the selected end date from the calendar widget
    QDate endDate = endDateCalendar->selectedDate();
    // Set the selected date in the date edit widget for display
    endDateEdit->setDate(endDate);
    // If the start date is also selected, filter orders
    if (startDateEdit->date().isValid()) {
        filterOrdersByDateRange(startDateEdit->date(), endDate);
    }
}

void OrderPage::filterOrdersByDateRange(const QDate &startDate, const QDate &endDate) {
    // Convert QDate to tm
    tm startTm = TimeHelper::QDateToTm(startDate);
    tm endTm = TimeHelper::QDateToTm(endDate);

    // Find orders within the specified date range
    auto filteredOrders = orderService.findOrdersByDateRange(startTm, endTm);

    // Populate the table with filtered orders
    populateTableWithOrders(filteredOrders);
}

void OrderPage::populateTableWithOrders(const std::vector<Order> &orders) {
    ordersTable->clearContents();
    ordersTable->setRowCount(0);

    for (const auto &order : orders) {
        int row = ordersTable->rowCount();
        ordersTable->insertRow(row);

        QTableWidgetItem *itemId = new QTableWidgetItem(order.getId());
        QTableWidgetItem *itemStart = new QTableWidgetItem(TimeHelper::tmToQString(order.getStartDate()));
        QTableWidgetItem *itemEnd = new QTableWidgetItem(TimeHelper::tmToQString(order.getEndDate()));
        QTableWidgetItem *itemCarId = new QTableWidgetItem(order.getCarId());
        QTableWidgetItem *itemClientId = new QTableWidgetItem(order.getClientId());
        QTableWidgetItem *itemPrice = new QTableWidgetItem(QString::number(order.getPrice()));

        ordersTable->setItem(row, 0, itemId);
        ordersTable->setItem(row, 1, itemStart);
        ordersTable->setItem(row, 2, itemEnd);
        ordersTable->setItem(row, 3, itemCarId);
        ordersTable->setItem(row, 4, itemClientId);
        ordersTable->setItem(row, 5, itemPrice);
    }
}

