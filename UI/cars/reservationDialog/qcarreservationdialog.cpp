#include "qcarreservationdialog.h"
#include "ui_qcarreservationdialog.h"

QCarReservationDialog::QCarReservationDialog(const Car &car, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QCarReservationDialog),
        m_car(car)
{
    ui->setupUi(this);
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    setupLayout();
}

QCarReservationDialog::~QCarReservationDialog() {
    delete ui;
}

void QCarReservationDialog::setupLayout() {
    auto *mainLayout = new QVBoxLayout(this);

    auto *carInfoLabel = new QLabel("Информация о машине:", this);
    mainLayout->addWidget(carInfoLabel);

    auto *carDetailsLabel = new QLabel(QString("Марка: %1, Модель: %2").arg(m_car.getBrand()).arg(m_car.getModel()), this);
    mainLayout->addWidget(carDetailsLabel);

    mainLayout->addWidget(createInputField("Паспорт клиента:"));
    mainLayout->addWidget(createInputField("Водительское удостоверение клиента:"));

    auto *startDateInput = createDateInputField("Дата начала:", QDate::currentDate());
    auto *endDateInput = createDateInputField("Дата окончания:", QDate::currentDate().addDays(1));
    mainLayout->addWidget(startDateInput);
    mainLayout->addWidget(endDateInput);

    auto *calculatePriceButton = new QPushButton("Рассчитать цену", this);
    auto *priceLabel = new QLabel("Цена:", this);
    auto *priceLineEdit = new QLineEdit(this);
    priceLineEdit->setReadOnly(true);
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
    auto *cancelButton = new QPushButton("Отмена", this);
    buttonLayout->addWidget(reserveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(reserveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

int QCarReservationDialog::calculateDays(const QDate &startDate, const QDate &endDate) {
    return startDate.daysTo(endDate);
}

QWidget *QCarReservationDialog::createInputField(const QString &labelText) {
    auto *widget = new QWidget(this);
    auto *label = new QLabel(labelText, widget);
    auto *lineEdit = new QLineEdit(widget);
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    return widget;
}

QWidget *QCarReservationDialog::createDateInputField(const QString &labelText, const QDate &date) {
    auto *widget = new QWidget(this);
    auto *label = new QLabel(labelText, widget);
    auto *dateEdit = new QDateEdit(date, widget);
    dateEdit->setMinimumDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(label);
    layout->addWidget(dateEdit);
    return widget;
}
