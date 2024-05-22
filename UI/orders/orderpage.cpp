// orderpage.cpp

#include "orderpage.h"
#include <QScrollBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>

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

    // Price range filter
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

    // Date range filter
    dateRangeCheckbox = new QCheckBox("Date Range", this);
    startDateLabel = new QLabel("Start Date:", this);
    startDateEdit = new QDateEdit(this);
    endDateLabel = new QLabel("End Date:", this);
    endDateEdit = new QDateEdit(this);
    QHBoxLayout *dateRangeLayout = new QHBoxLayout();
    dateRangeLayout->addWidget(dateRangeCheckbox);
    dateRangeLayout->addWidget(startDateLabel);
    dateRangeLayout->addWidget(startDateEdit);
    dateRangeLayout->addWidget(endDateLabel);
    dateRangeLayout->addWidget(endDateEdit);
    dateRangeLayout->addStretch();

    // Bottom layout for checkboxes and fields
    QVBoxLayout *bottomLayout = new QVBoxLayout();
    bottomLayout->addLayout(priceRangeLayout);
    bottomLayout->addLayout(dateRangeLayout);
    bottomLayout->addStretch();

    mainLayout->addLayout(bottomLayout);
}

void OrderPage::populateOrders() {
    ordersTable->clearContents();
    ordersTable->setRowCount(0);

    // Populating orders logic...
}

void OrderPage::onPriceRangeCheckboxStateChanged(int state) {
    lowestPriceLabel->setEnabled(state == Qt::Checked);
    lowestPriceEdit->setEnabled(state == Qt::Checked);
    highestPriceLabel->setEnabled(state == Qt::Checked);
    highestPriceEdit->setEnabled(state == Qt::Checked);
}

void OrderPage::onDateRangeCheckboxStateChanged(int state) {
    startDateLabel->setEnabled(state == Qt::Checked);
    startDateEdit->setEnabled(state == Qt::Checked);
    endDateLabel->setEnabled(state == Qt::Checked);
    endDateEdit->setEnabled(state == Qt::Checked);
}
