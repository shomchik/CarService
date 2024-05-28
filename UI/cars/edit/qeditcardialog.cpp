#include "qeditcardialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QUuid>
#include <QMessageBox>

QEditCarDialog::QEditCarDialog(const Car &car, QWidget *parent)
    : QDialog(parent), carService(), currentCar(car) {
    setWindowTitle("Редактирование машины");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *brandLabel = new QLabel("Марка:", this);
    brandEdit = new QLineEdit(car.getBrand(), this);
    mainLayout->addWidget(brandLabel);
    mainLayout->addWidget(brandEdit);

    QLabel *modelLabel = new QLabel("Модель:", this);
    modelEdit = new QLineEdit(car.getModel(), this);
    mainLayout->addWidget(modelLabel);
    mainLayout->addWidget(modelEdit);

    QLabel *volumeLabel = new QLabel("Объем:", this);
    volumeEdit = new QLineEdit(car.getVolume(), this);
    mainLayout->addWidget(volumeLabel);
    mainLayout->addWidget(volumeEdit);

    QLabel *bodyTypeLabel = new QLabel("Тип кузова:", this);
    bodyTypeCombo = new QComboBox(this);
    bodyTypeCombo->addItem("Седан", SEDAN);
    bodyTypeCombo->addItem("Купе", COUPE);
    bodyTypeCombo->addItem("Хэтчбек", HATCHBACK);
    bodyTypeCombo->addItem("Кабриолет", CONVERTIBLE);
    bodyTypeCombo->addItem("Внедорожник", SUV);
    bodyTypeCombo->addItem("Грузовик", TRUCK);
    bodyTypeCombo->addItem("Фургон", VAN);
    bodyTypeCombo->setCurrentIndex(static_cast<int>(car.getBodyType()));
    mainLayout->addWidget(bodyTypeLabel);
    mainLayout->addWidget(bodyTypeCombo);

    QLabel *transmissionLabel = new QLabel("Трансмиссия:", this);
    transmissionCombo = new QComboBox(this);
    transmissionCombo->addItem("Механическая", MANUAL);
    transmissionCombo->addItem("Автоматическая", AUTOMATIC);
    transmissionCombo->addItem("Вариатор", VARIATOR);
    transmissionCombo->setCurrentIndex(static_cast<int>(car.getTransmission()));
    mainLayout->addWidget(transmissionLabel);
    mainLayout->addWidget(transmissionCombo);

    QLabel *rateLabel = new QLabel("Цена:", this);
    rateEdit = new QLineEdit(QString::number(car.getRate(), 'f', 2), this);
    mainLayout->addWidget(rateLabel);
    mainLayout->addWidget(rateEdit);

    hasCarSeatCheck = new QCheckBox("Есть детское кресло", this);
    hasCarSeatCheck->setChecked(car.getHasCarSeat());
    mainLayout->addWidget(hasCarSeatCheck);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *saveButton = new QPushButton("Сохранить", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &QEditCarDialog::onSaveButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QEditCarDialog::~QEditCarDialog() {}

void QEditCarDialog::onSaveButtonClicked() {
    currentCar.setBrand(brandEdit->text());
    currentCar.setModel(modelEdit->text());
    currentCar.setVolume(volumeEdit->text());
    currentCar.setBodyType(static_cast<BodyType>(bodyTypeCombo->currentData().toInt()));
    currentCar.setTransmission(static_cast<Transmission>(transmissionCombo->currentData().toInt()));
    currentCar.setRate(rateEdit->text().toDouble());
    currentCar.setHasCarSeat(hasCarSeatCheck->isChecked());

    carService.editCar(currentCar);

    QMessageBox::information(this, "Успех", "Машина успешно отредактирована!");
    accept();
}
