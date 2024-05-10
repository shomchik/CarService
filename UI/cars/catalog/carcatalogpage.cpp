#include "carcatalogpage.h"

CarCatalogPage::CarCatalogPage(QWidget *parent) : QMainWindow(parent) {
    this->service = CarService();
    setWindowState(Qt::WindowMaximized);

    QScrollArea * scrollArea = new QScrollArea(this);
    setCentralWidget(scrollArea);
    scrollArea->setObjectName("scrollArea");

    QWidget * catalogWidget = new QWidget(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(catalogWidget);

    QVBoxLayout *catalogLayout = new QVBoxLayout();
    catalogWidget->setLayout(catalogLayout);

    HeaderWidget *header = new HeaderWidget( this);
    catalogLayout->addWidget(header);
    catalogLayout->setSpacing(20);

    QList<Car> cars = QList<Car>::fromVector(QVector<Car>::fromStdVector(service.getAllCars()));
    cout << cars.size();

    int cardsInCurrentRow = 0;
    QHBoxLayout *currentRowLayout = new QHBoxLayout();
    catalogLayout->addLayout(currentRowLayout);

    for (const Car &car: cars) {
        if (cardsInCurrentRow == 3) {
            currentRowLayout = new QHBoxLayout();
            catalogLayout->addLayout(currentRowLayout);
            cardsInCurrentRow = 0;
        }

        QWidget * card = createCarCard(car);
        currentRowLayout->addWidget(card);
        cardsInCurrentRow++;
    }

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    connect(header, &HeaderWidget::ordersClicked, this, &CarCatalogPage::showOrdersPage);
}

QWidget *CarCatalogPage::createCarCard(const Car &car) {
    QWidget * cardWidget = new QWidget(this);
    QVBoxLayout *cardLayout = new QVBoxLayout();
    cardWidget->setLayout(cardLayout);

    cardWidget->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; margin: 10px; border-radius: 10px;");

    QString imagePath = QString("/Users/noriksaroyan/CLionProjects/CarLeasing/UI/static/img/x4.jpeg").arg(car.getId());
    QLabel *imageLabel = new QLabel(this);
    QPixmap image(imagePath);
    imageLabel->setPixmap(image.scaledToHeight(150, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(imageLabel);

    QLabel *titleLabel = new QLabel(car.getBrand() + " " + car.getModel(), this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #333;");
    titleLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(titleLabel);

    QPushButton *cardButton = new QPushButton("Подробнее", this);
    cardButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px;");
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

    QLabel *hasCarSeatLabel = new QLabel("Есть детское кресло: " + QString(car.isHasCarSeat() ? "Да" : "Нет"),
                                         detailsDialog);
    mainLayout->addWidget(hasCarSeatLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *reserveButton = new QPushButton("Зарезервировать", detailsDialog);
    reserveButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px;");
    connect(reserveButton, &QPushButton::clicked, this, [car, this]() {
        QCarReservationDialog *reservationDialog = new QCarReservationDialog(car, this);
        reservationDialog->exec();
    });
    buttonLayout->addWidget(reserveButton);

    QPushButton *backButton = new QPushButton("Вернуться к каталогу", detailsDialog);
    backButton->setStyleSheet("background-color: #ff0000; color: white; padding: 10px; border-radius: 5px;");
    connect(backButton, &QPushButton::clicked, detailsDialog, &QDialog::accept);
    buttonLayout->addWidget(backButton);

    mainLayout->addLayout(buttonLayout);

    detailsDialog->exec();
}

void CarCatalogPage::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    QScrollArea * scrollArea = findChild<QScrollArea *>("scrollArea");
    if (scrollArea)
        scrollArea->setFixedHeight(event->size().height());
}

void CarCatalogPage::showOrdersPage() {
    OrderPage *ordersPage = new OrderPage(this); // Assuming OrderPage is your orders page class
    setCentralWidget(ordersPage);
}
