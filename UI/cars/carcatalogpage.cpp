#include "carcatalogpage.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include "iostream"
#include "../static/header/headerwidget.h"
#include "../../Entities/car/Car.h"
#include <QVBoxLayout>


CarCatalogPage::CarCatalogPage(QWidget *parent) : QMainWindow(parent) {
    setWindowState(Qt::WindowMaximized);

    QScrollArea *scrollArea = new QScrollArea(this);
    setCentralWidget(scrollArea);
    scrollArea->setObjectName("scrollArea");

    QWidget *catalogWidget = new QWidget(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(catalogWidget);

    QVBoxLayout *catalogLayout = new QVBoxLayout();
    catalogWidget->setLayout(catalogLayout);

    HeaderWidget *header = new HeaderWidget("Лизинг Машин", this);
    catalogLayout->addWidget(header);

    catalogLayout->setSpacing(20);
//    catalogLayout->setContentsMargins(0, 0, 0, 0);

    QList<Car> cars;
    cars << Car("1", "Mercedes", "G63", "2.0L", SEDAN, AUTOMATIC, true)
         << Car("2", "BMW", "X5", "3.0L", SUV, AUTOMATIC, true)
         << Car("3", "Audi", "A4", "1.8L", SEDAN, MANUAL, false)
         << Car("4", "Toyota", "Camry", "2.5L", SEDAN, AUTOMATIC, true)
         << Car("5", "Ford", "Mustang", "5.0L", COUPE, MANUAL, true)
         << Car("6", "Tesla", "Model S", "Electric", SEDAN, AUTOMATIC, false)
         << Car("7", "Chevrolet", "Tahoe", "5.3L", SUV, AUTOMATIC, true)
         << Car("8", "Honda", "Civic", "1.5L", SEDAN, AUTOMATIC, true)
         << Car("9", "Jeep", "Wrangler", "3.6L", SUV, MANUAL, true)
         << Car("10", "Volkswagen", "Golf", "1.4L", HATCHBACK, MANUAL, false);

    int cardsInCurrentRow = 0;
    QHBoxLayout *currentRowLayout = new QHBoxLayout();
    catalogLayout->addLayout(currentRowLayout);

    for (const Car &car : cars) {
        if (cardsInCurrentRow == 5) {
            currentRowLayout = new QHBoxLayout();
            catalogLayout->addLayout(currentRowLayout);
            cardsInCurrentRow = 0;
        }

        QWidget *card = createCarCard(car);
        currentRowLayout->addWidget(card);
        cardsInCurrentRow++;
    }

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

QWidget* CarCatalogPage::createCarCard(const Car& car) {
    QWidget *cardWidget = new QWidget(this);
    QVBoxLayout *cardLayout = new QVBoxLayout();
    cardWidget->setLayout(cardLayout);

    cardWidget->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; margin: 10px;");

    // Load car image
    QString imagePath = QString("/Users/noriksaroyan/CLionProjects/CarLeasing/UI/static/img/x4.jpeg").arg(car.getId());
    QLabel *imageLabel = new QLabel(this);
    QPixmap image(imagePath);
    imageLabel->setPixmap(image.scaledToHeight(150, Qt::SmoothTransformation)); // Adjust image size
    imageLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(imageLabel);

    QLabel *brandLabel = new QLabel(car.getBrand(), this);
    QLabel *modelLabel = new QLabel(car.getModel(), this);

    brandLabel->setAlignment(Qt::AlignCenter);
    modelLabel->setAlignment(Qt::AlignCenter);

    cardLayout->addWidget(brandLabel);
    cardLayout->addWidget(modelLabel);

    brandLabel->setStyleSheet("color: black;");
    modelLabel->setStyleSheet("color: black;");

    cardLayout->addWidget(brandLabel);
    cardLayout->addWidget(modelLabel);


    QPushButton *cardButton = new QPushButton("View Details", this);
    cardButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px;");
    cardLayout->addWidget(cardButton);

    connect(cardButton, &QPushButton::clicked, this, [car, this]() {
        showCarDetails(car);
    });

    cardWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    return cardWidget;
}

void CarCatalogPage::showCarDetails(const Car &car) {
    QDialog *detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Car Details");

    int catalogPageWidth = this->width();
    int catalogPageHeight = this->height();
    int detailsPageWidth = catalogPageWidth * 0.2;
    int detailsPageHeight = catalogPageHeight * 0.2;

    detailsDialog->setFixedSize(detailsPageWidth, detailsPageHeight);

    QVBoxLayout *mainLayout = new QVBoxLayout(detailsDialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout *photoInfoLayout = new QHBoxLayout();

    QVBoxLayout *leftLayout = new QVBoxLayout();

    QString imagePath = QString("/Users/noriksaroyan/CLionProjects/CarLeasingService/UI/photos/a4.jpeg").arg(car.getId());
    QLabel *imageLabel = new QLabel(detailsDialog);
    QPixmap image(imagePath);
    imageLabel->setPixmap(image.scaled(100, 75, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignLeft);
    leftLayout->addWidget(imageLabel);

    photoInfoLayout->addLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout();

    QLabel *brandModelLabel = new QLabel(QString("%1 %2").arg(car.getBrand()).arg(car.getModel()), detailsDialog);
    rightLayout->addWidget(brandModelLabel);

    QLabel *volumeLabel = new QLabel("Volume: " + car.getVolume(), detailsDialog);
    rightLayout->addWidget(volumeLabel);

    QLabel *bodyTypeLabel = new QLabel("Body Type: " + QString::number(car.getBodyType()).toUpper(), detailsDialog);
    rightLayout->addWidget(bodyTypeLabel);

    QLabel *transmissionLabel = new QLabel("Transmission: " + QString::number(car.getTransmission()).toUpper(), detailsDialog);
    rightLayout->addWidget(transmissionLabel);

    QLabel *rateLabel = new QLabel("Rate: " + QString::number(car.getRate()), detailsDialog);
    rightLayout->addWidget(rateLabel);

    QLabel *hasCarSeatLabel = new QLabel("Has Car Seat: " + QString(car.isHasCarSeat() ? "Yes" : "No"), detailsDialog);
    rightLayout->addWidget(hasCarSeatLabel);

    photoInfoLayout->addLayout(rightLayout);

    mainLayout->addLayout(photoInfoLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *reserveButton = new QPushButton("Reserve", detailsDialog);
    connect(reserveButton, &QPushButton::clicked, this, [car]() {

    });
    buttonLayout->addWidget(reserveButton);

    QPushButton *backButton = new QPushButton("Back to Catalog", detailsDialog);
    connect(backButton, &QPushButton::clicked, detailsDialog, &QDialog::accept);
    buttonLayout->addWidget(backButton);

    mainLayout->addLayout(buttonLayout);

    detailsDialog->exec();
}



void CarCatalogPage::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    QScrollArea *scrollArea = findChild<QScrollArea*>("scrollArea");
    if (scrollArea)
        scrollArea->setFixedHeight(event->size().height());
}
