#include "qcarreservationdialog.h"

#include <iostream>

#include "ui_qcarreservationdialog.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QPalette>
#include <QUuid>


#include "../../../Entities/client/Client.h"
#include "../../../Entities/order/Order.h"
#include "../../../Services/order/OrderService.h"

QCarReservationDialog::QCarReservationDialog(const Car &car, QWidget *parent) : QDialog(parent),
    ui(new Ui::QCarReservationDialog),
    m_car(car) {
    ui->setupUi(this);
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    setupLayout();
    applyStyles();
}

QCarReservationDialog::~QCarReservationDialog() {
    delete ui;
}

void QCarReservationDialog::setupLayout() {
    auto *mainLayout = new QVBoxLayout(this);

    auto *carInfoLabel = new QLabel("Информация о машине:", this);
    carInfoLabel->setObjectName("carInfoLabel");
    mainLayout->addWidget(carInfoLabel);

    auto *carDetailsLabel = new QLabel(QString("Марка: %1, Модель: %2").arg(m_car.getBrand()).arg(m_car.getModel()),
                                       this);
    carDetailsLabel->setObjectName("carDetailsLabel");
    mainLayout->addWidget(carDetailsLabel);

    auto *passportField = createInputField("Паспорт клиента:");
    auto *driverLicenseField = createInputField("Водительское удостоверение клиента:");
    mainLayout->addWidget(passportField);
    mainLayout->addWidget(driverLicenseField);

    auto *startDateInput = createDateInputField("Дата начала:", QDate::currentDate());
    auto *endDateInput = createDateInputField("Дата окончания:", QDate::currentDate().addDays(1));
    mainLayout->addWidget(startDateInput);
    mainLayout->addWidget(endDateInput);

    auto *calculatePriceButton = new QPushButton("Рассчитать цену", this);
    calculatePriceButton->setObjectName("calculatePriceButton");
    auto *priceLabel = new QLabel("Цена:", this);
    priceLabel->setObjectName("priceLabel");
    auto *priceLineEdit = new QLineEdit(this);
    priceLineEdit->setReadOnly(true);
    priceLineEdit->setObjectName("priceLineEdit");
    mainLayout->addWidget(calculatePriceButton);
    mainLayout->addWidget(priceLabel);
    mainLayout->addWidget(priceLineEdit);

    connect(calculatePriceButton, &QPushButton::clicked, this, [=]() {
        QDate startDate = startDateInput->findChild<QDateEdit *>()->date();
        QDate endDate = endDateInput->findChild<QDateEdit *>()->date();
        int days = calculateDays(startDate, endDate);
        double price = m_car.getRate() * days;
        priceLineEdit->setText(QString::number(price, 'f', 2));
    });

    mainLayout->addSpacing(20);

    auto *buttonLayout = new QHBoxLayout();
    auto *reserveButton = new QPushButton("Зарезервировать", this);
    reserveButton->setObjectName("reserveButton");
    auto *cancelButton = new QPushButton("Отмена", this);
    cancelButton->setObjectName("cancelButton");
    buttonLayout->addWidget(reserveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(reserveButton, &QPushButton::clicked, this, [=]() {
        if (validateFields(passportField, driverLicenseField)) {
            QString orderId = QUuid::createUuid().toString();
            QDate startDate = startDateInput->findChild<QDateEdit *>()->date();
            QDate endDate = endDateInput->findChild<QDateEdit *>()->date();
            QString carId = m_car.getId();

            QString clientId = passportField->findChild<QLineEdit *>()->text().trimmed();

            cout << clientId.toStdString();

            double price = priceLineEdit->text().toDouble();
            Client client(QUuid::createUuid().toString().toStdString(),
                          passportField->findChild<QLineEdit *>()->text().toStdString(),
                          driverLicenseField->findChild<QLineEdit *>()->text().toStdString());
            tm startTm = {0};
            tm endTm = {0};
            startTm.tm_year = startDate.year() - 1900;
            startTm.tm_mon = startDate.month() - 1;
            startTm.tm_mday = startDate.day();
            endTm.tm_year = endDate.year() - 1900;
            endTm.tm_mon = endDate.month() - 1;
            endTm.tm_mday = endDate.day();

            Order newOrder(orderId, startTm, endTm, carId, QString::fromStdString(client.getId()), price);
            this->orderService.createOrder(newOrder);
            this->clientService.insertClient(client);

            QMessageBox::information(this, "Успех", "Заказ успешно создан!");
            QDialog::accept();
        }
    });
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

int QCarReservationDialog::calculateDays(const QDate &startDate, const QDate &endDate) {
    return startDate.daysTo(endDate);
}

QWidget *QCarReservationDialog::createInputField(const QString &labelText) {
    auto *widget = new QWidget(this);
    auto *label = new QLabel(labelText, widget);
    auto *lineEdit = new QLineEdit(widget);
    lineEdit->setObjectName(labelText);
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    return widget;
}

QWidget *QCarReservationDialog::createDateInputField(const QString &labelText, const QDate &date) {
    auto *widget = new QWidget(this);
    auto *label = new QLabel(labelText, widget);
    auto *dateEdit = new QDateEdit(date, widget);
    dateEdit->setObjectName("dateEdit");
    dateEdit->setMinimumDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(label);
    layout->addWidget(dateEdit);
    return widget;
}

bool QCarReservationDialog::validateFields(QWidget *passportField, QWidget *driverLicenseField) {
    QLineEdit *passportLineEdit = passportField->findChild<QLineEdit *>();
    QLineEdit *driverLicenseLineEdit = driverLicenseField->findChild<QLineEdit *>();

    QString passportNumber = passportLineEdit->text().trimmed();
    QString driverLicenseNumber = driverLicenseLineEdit->text().trimmed();

    QRegularExpression passportRegex("^[0-9]{4}\\s[0-9]{6}$");
    QRegularExpression driverLicenseRegex("^[0-9]{10}$");

    bool isValid = true;

    auto resetField = [](QLineEdit *lineEdit, const QString &placeholderText) {
        lineEdit->clear();
        lineEdit->setPlaceholderText(placeholderText);
        QPalette palette = lineEdit->palette();
        palette.setColor(QPalette::Base, QColor(255, 235, 235)); // Light red background
        lineEdit->setPalette(palette);
    };

    if (!passportRegex.match(passportNumber).hasMatch()) {
        resetField(passportLineEdit, "Формат: 1234 567890");
        isValid = false;
    } else {
        passportLineEdit->setPalette(QPalette());
    }

    if (!driverLicenseRegex.match(driverLicenseNumber).hasMatch()) {
        resetField(driverLicenseLineEdit, "10 цифр");
        isValid = false;
    } else {
        driverLicenseLineEdit->setPalette(QPalette());
    }

    return isValid;
}

void QCarReservationDialog::applyStyles() {
    this->setStyleSheet(R"(
        QDialog {
            background-color: #f0f0f0;
            font-family: Arial, sans-serif;
            font-size: 14px;
        }
        QLabel#carInfoLabel, QLabel#carDetailsLabel, QLabel {
            font-weight: bold;
            color: #333;
        }
        QLineEdit {
            padding: 5px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        QLineEdit[invalid="true"] {
            border: 2px solid red;
        }
        QDateEdit {
            padding: 5px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        QPushButton {
            padding: 8px 15px;
            border: none;
            border-radius: 4px;
            background-color: #5cb85c;
            color: white;
        }
        QPushButton#cancelButton {
            background-color: #d9534f;
        }
        QPushButton#calculatePriceButton {
            background-color: #f0ad4e;
        }
        QPushButton:hover {
            background-color: #4cae4c;
        }
        QPushButton#cancelButton:hover {
            background-color: #c9302c;
        }
        QPushButton#calculatePriceButton:hover {
            background-color: #ec971f;
        }
        QVBoxLayout, QHBoxLayout {
            margin: 0;
            spacing: 10px;
        }
        QCalendarWidget QToolButton {
            height: 25px;
            width: 100px;
            color: white;
            font-size: 12px;
            icon-size: 20px, 20px;
            background-color: #4cae4c; // Green color for buttons
        }
        QCalendarWidget QToolButton:hover {
            background-color: #5cb85c;
        }
        QCalendarWidget QToolButton#qt_calendar_prevmonth {
            qproperty-icon: url(left-arrow.png); // Provide the path to your icon
        }
        QCalendarWidget QToolButton#qt_calendar_nextmonth {
            qproperty-icon: url(right-arrow.png); // Provide the path to your icon
        }
        QCalendarWidget QMenu {
            width: 150px;
            left: 50px;
            color: white;
            font-size: 12px;
            background-color: #4cae4c;
        }
        QCalendarWidget QSpinBox {
            width: 50px;
            font-size: 12px;
            color: white;
            background-color: #4cae4c;
            selection-background-color: #5cb85c;
            selection-color: black;
        }
        QCalendarWidget QWidget {
            alternate-background-color: #d3d3d3;
        }
        QCalendarWidget QAbstractItemView:enabled {
            font-size: 18px;
            color: #333;
            background-color: white;
            selection-background-color: #4cae4c;
            selection-color: white;
        }
    )");
}
