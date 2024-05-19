#include "headerwidget.h"
#include "../../cars/catalog/carcatalogpage.h"
#include <QLineEdit>
#include <QPushButton>

HeaderWidget::HeaderWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // White holder widget
    QWidget *holderWidget = new QWidget(this);
    holderWidget->setStyleSheet("background-color: #fff; border-bottom: 2px solid #ccc; padding: 10px; border-radius: 10px;");
    mainLayout->addWidget(holderWidget);

    // Layout for header contents
    QVBoxLayout *holderLayout = new QVBoxLayout(holderWidget);
    holderLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *headerLabel = new QLabel("Сервис Аренды Машин", holderWidget);
    QFont font("Arial", 24, QFont::Bold);
    headerLabel->setFont(font);
    headerLabel->setAlignment(Qt::AlignLeft);
    headerLabel->setStyleSheet("background-color: none;"); // No background color

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->addWidget(headerLabel);

    QLineEdit *searchLineEdit = new QLineEdit(holderWidget);
    searchLineEdit->setPlaceholderText("Поиск...");
    searchLineEdit->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; padding: 5px;");
    headerLayout->addWidget(searchLineEdit);

    // Search button
    QPushButton *searchButton = new QPushButton(holderWidget);
    searchButton->setIcon(QIcon(":/icons/search_icon.png"));
    searchButton->setStyleSheet("QPushButton { border: none; background-color: transparent; }");
    searchButton->setCursor(Qt::PointingHandCursor);
    headerLayout->addWidget(searchButton);

    // Text labels styled like links
    QLabel *catalogLabel = new QLabel("<a href=\"#\">Каталог</a>", holderWidget);
    QLabel *ordersLabel = new QLabel("<a href=\"#\">Заказы</a>", holderWidget);
    catalogLabel->setTextFormat(Qt::RichText);
    ordersLabel->setTextFormat(Qt::RichText);
    catalogLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ordersLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    catalogLabel->setOpenExternalLinks(false);
    ordersLabel->setOpenExternalLinks(false);
    catalogLabel->setStyleSheet("color: #000;");
    ordersLabel->setStyleSheet("color: #000;");

    headerLayout->addWidget(catalogLabel);
    headerLayout->addWidget(ordersLabel);

    holderLayout->addLayout(headerLayout);

    connect(catalogLabel, &QLabel::linkActivated, this, &HeaderWidget::catalogClicked);
    connect(ordersLabel, &QLabel::linkActivated, this, &HeaderWidget::ordersClicked);
}