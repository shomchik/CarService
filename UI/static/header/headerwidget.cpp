#include "headerwidget.h"

HeaderWidget::HeaderWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    headerLabel = new QLabel("Сервис Аренды Машин", this);
    QFont font("Arial", 24, QFont::Bold);
    headerLabel->setFont(font);
    headerLabel->setStyleSheet("color: #000;"); // Black color
    headerLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(headerLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    catalogButton = new QPushButton("Каталог", this);
    ordersButton = new QPushButton("Заказы", this);
    buttonLayout->addWidget(catalogButton);
    buttonLayout->addWidget(ordersButton);
    layout->addLayout(buttonLayout);

    connect(catalogButton, &QPushButton::clicked, this, &HeaderWidget::onCatalogClicked);
    connect(ordersButton, &QPushButton::clicked, this, &HeaderWidget::onOrdersClicked);
}

void HeaderWidget::onCatalogClicked() {
    emit catalogClicked();
}

void HeaderWidget::onOrdersClicked() {
    emit ordersClicked();
}
