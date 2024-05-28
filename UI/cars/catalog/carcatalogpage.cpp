#include "carcatalogpage.h"
#include <iostream>
#include "../edit/qeditcardialog.h"

CarCatalogPage::CarCatalogPage(QWidget *parent) : QMainWindow(parent) {
    this->service = CarService();
    setWindowState(Qt::WindowMaximized);

    QScrollArea *scrollArea = new QScrollArea(this);
    setCentralWidget(scrollArea);
    scrollArea->setObjectName("scrollArea");

    catalogWidget = new QWidget(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(catalogWidget);

    catalogLayout = new QVBoxLayout();
    catalogWidget->setLayout(catalogLayout);

    header = new HeaderWidget(this);
    catalogLayout->addWidget(header);
    catalogLayout->setSpacing(20);

    populateCarCatalog();

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    connect(header, &HeaderWidget::ordersClicked, this, &CarCatalogPage::showOrdersPage);
    connect(header, &HeaderWidget::catalogClicked, this, &CarCatalogPage::showCarCatalogPage);
    connect(header, &HeaderWidget::addCarClicked, this, &CarCatalogPage::showAddCarDialog);
    connect(header, &HeaderWidget::searchResultClicked, this, &CarCatalogPage::showCarDetailsFromSearch);
    connect(header, &HeaderWidget::chartClicked, this, &CarCatalogPage::showTransmissionChartPage);
}

void CarCatalogPage::populateCarCatalog() {
    clearCarCatalog();

    auto entityCars = service.getAllCars();
    QList<Car> cars(entityCars.begin(), entityCars.end());

    int cardsInCurrentRow = 0;
    QHBoxLayout *currentRowLayout = new QHBoxLayout();
    catalogLayout->addLayout(currentRowLayout);

    for (const Car &car: cars) {
        if (cardsInCurrentRow == 3) {
            currentRowLayout = new QHBoxLayout();
            catalogLayout->addLayout(currentRowLayout);
            cardsInCurrentRow = 0;
        }

        QWidget *card = createCarCard(car);
        currentRowLayout->addWidget(card);
        cardsInCurrentRow++;
    }
}

void CarCatalogPage::clearCarCatalog() {
    // Remove all items except the header widget
    QLayoutItem *item;
    while ((item = catalogLayout->takeAt(1)) != nullptr) {
        // start from 1 to skip the header
        delete item->widget();
        delete item;
    }
}

void CarCatalogPage::showAddCarDialog() {
    QAddCarDialog *addCarDialog = new QAddCarDialog(this);
    if (addCarDialog->exec() == QDialog::Accepted) {
        populateCarCatalog();
    }
}

QWidget *CarCatalogPage::createCarCard(const Car &car) {
    QWidget *cardWidget = new QWidget(this);
    QVBoxLayout *cardLayout = new QVBoxLayout();
    cardWidget->setLayout(cardLayout);

    cardWidget->setStyleSheet(R"(
        QWidget {
            background-color: #ffffff;
            border: 1px solid #ccc;
            margin: 10px;
            border-radius: 10px;
            box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.1);
        }
        QLabel {
            font-weight: bold;
            font-size: 16px;
            color: #333;
        }
        QPushButton {
            background-color: #4CAF50;
            color: white;
            padding: 10px;
            border-radius: 5px;
            border: none;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    QString imagePath = QString("/Users/noriksaroyan/CLionProjects/CarLeasing/UI/static/img/x4.jpeg").arg(car.getId());
    QLabel *imageLabel = new QLabel(this);
    QPixmap image(imagePath);
    imageLabel->setPixmap(image.scaledToHeight(150, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(imageLabel);

    QLabel *titleLabel = new QLabel(car.getBrand() + " " + car.getModel(), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(titleLabel);

    QPushButton *cardButton = new QPushButton("Подробнее", this);
    cardLayout->addWidget(cardButton);

    connect(cardButton, &QPushButton::clicked, this, [car, this]() {
        showCarDetails(car);
    });

    cardWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    return cardWidget;
}

void CarCatalogPage::showCarDetails(const Car &car) {
    QDialog *detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Информация о машине");

    int detailsDialogWidth = 400;
    int detailsDialogHeight = 300;
    detailsDialog->setFixedSize(detailsDialogWidth, detailsDialogHeight);

    detailsDialog->setStyleSheet(R"(
        QDialog {
            background-color: #f9f9f9;
            border-radius: 10px;
        }
        QLabel {
            font-size: 14px;
            color: #555;
        }
        QPushButton {
            background-color: #4CAF50;
            color: white;
            padding: 10px;
            border-radius: 5px;
            border: none;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
        QPushButton#backButton {
            background-color: #ff0000;
        }
        QPushButton#backButton:hover {
            background-color: #e60000;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(detailsDialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *brandModelLabel = new QLabel(QString("%1 %2").arg(car.getBrand()).arg(car.getModel()), detailsDialog);
    brandModelLabel->setAlignment(Qt::AlignCenter);
    brandModelLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: #333;");
    mainLayout->addWidget(brandModelLabel);

    QLabel *volumeLabel = new QLabel("Объем: " + car.getVolume(), detailsDialog);
    mainLayout->addWidget(volumeLabel);

    QLabel *bodyTypeLabel = new QLabel(
        "Тип кузова: " + QString::fromStdString(CarSerializer::bodyTypeToString(car.getBodyType())), detailsDialog);
    mainLayout->addWidget(bodyTypeLabel);

    QLabel *transmissionLabel = new QLabel(
        "Трансмиссия: " + QString::fromStdString(CarSerializer::transmissionToString(car.getTransmission())),
        detailsDialog);
    mainLayout->addWidget(transmissionLabel);

    QLabel *rateLabel = new QLabel("Цена: " + QString::number(car.getRate(), 'f', 2), detailsDialog);
    mainLayout->addWidget(rateLabel);

    QLabel *hasCarSeatLabel = new QLabel("Есть детское кресло: " + QString(car.getHasCarSeat() ? "Да" : "Нет"),
                                         detailsDialog);
    mainLayout->addWidget(hasCarSeatLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *reserveButton = new QPushButton("Резервировать", detailsDialog);
    buttonLayout->addWidget(reserveButton);
    connect(reserveButton, &QPushButton::clicked, this, [car, this]() {
        QCarReservationDialog *reservationDialog = new QCarReservationDialog(car, this);
        reservationDialog->exec();
    });

    QPushButton *editButton = new QPushButton("Редактировать", detailsDialog);
    buttonLayout->addWidget(editButton);
    connect(editButton, &QPushButton::clicked, this, [car, detailsDialog, this]() {
        detailsDialog->accept();
        QEditCarDialog *editDialog = new QEditCarDialog(car, this);
        if (editDialog->exec() == QDialog::Accepted) {
            populateCarCatalog();
        }
    });

    QPushButton *backButton = new QPushButton("Отменить", detailsDialog);
    backButton->setObjectName("backButton");
    buttonLayout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, detailsDialog, &QDialog::accept);

    mainLayout->addLayout(buttonLayout);

    detailsDialog->exec();
}

void CarCatalogPage::showEditCarDialog(const Car &car) {
    QEditCarDialog editDialog(car, this);
    if (editDialog.exec() == QDialog::Accepted) {
        showCarDetails(car);
    }
}


void CarCatalogPage::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    QScrollArea *scrollArea = findChild<QScrollArea *>("scrollArea");
    if (scrollArea) {
        scrollArea->setFixedHeight(event->size().height());
    }
}

void CarCatalogPage::showOrdersPage() {
    OrderPage *ordersPage = new OrderPage(this);
    setCentralWidget(ordersPage);
}

void CarCatalogPage::showCarCatalogPage() {
    setCentralWidget(this);
}

void CarCatalogPage::showCarDetailsFromSearch(const QString &result) {
    if (result.startsWith("Cars->")) {
        QStringList parts = result.split("->");
        if (parts.size() < 2) {
            return;
        }
        QString carId = parts.at(1).split(":").first().trimmed();
        auto opt = service.getCarById(carId.toStdString());

        if (opt.has_value()) {
            Car car = opt.value();
            showCarDetails(car);
        }
    } else if (result.startsWith("Orders->")) {
        showOrdersPage();
    }
}

void CarCatalogPage::showTransmissionChartPage() {
    TransmissionChart *chartPage = new TransmissionChart(this);
    setCentralWidget(chartPage);
}
