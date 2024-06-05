#include "qaddcardialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QUuid>
#include <QMessageBox>
#include <QFileDialog>

QAddCarDialog::QAddCarDialog(QWidget *parent) : QDialog(parent), carService(), pathService() {
    setWindowTitle("Добавление машины");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add checkboxes
    checkbox1 = new QCheckBox("Показать всё", this);
    checkbox2 = new QCheckBox("Показать без трансмиссии и типа кузова", this);
    checkbox1->setChecked(true);
    mainLayout->addWidget(checkbox1);
    mainLayout->addWidget(checkbox2);

    QLabel *brandLabel = new QLabel("Марка:", this);
    brandEdit = new QLineEdit(this);
    mainLayout->addWidget(brandLabel);
    mainLayout->addWidget(brandEdit);

    QLabel *modelLabel = new QLabel("Модель:", this);
    modelEdit = new QLineEdit(this);
    mainLayout->addWidget(modelLabel);
    mainLayout->addWidget(modelEdit);

    QLabel *volumeLabel = new QLabel("Объем:", this);
    volumeEdit = new QLineEdit(this);
    mainLayout->addWidget(volumeLabel);
    mainLayout->addWidget(volumeEdit);

    bodyTypeLabel = new QLabel("Тип кузова:", this);
    bodyTypeCombo = new QComboBox(this);
    bodyTypeCombo->addItem("Седан", SEDAN);
    bodyTypeCombo->addItem("Купе", COUPE);
    bodyTypeCombo->addItem("Хэтчбек", HATCHBACK);
    bodyTypeCombo->addItem("Кабриолет", CONVERTIBLE);
    bodyTypeCombo->addItem("Внедорожник", SUV);
    bodyTypeCombo->addItem("Грузовик", TRUCK);
    bodyTypeCombo->addItem("Фургон", VAN);
    mainLayout->addWidget(bodyTypeLabel);
    mainLayout->addWidget(bodyTypeCombo);

    transmissionLabel = new QLabel("Трансмиссия:", this);
    transmissionCombo = new QComboBox(this);
    transmissionCombo->addItem("Механическая", MANUAL);
    transmissionCombo->addItem("Автоматическая", AUTOMATIC);
    transmissionCombo->addItem("Вариатор", VARIATOR);
    mainLayout->addWidget(transmissionLabel);
    mainLayout->addWidget(transmissionCombo);

    QLabel *rateLabel = new QLabel("Цена:", this);
    rateEdit = new QLineEdit(this);
    mainLayout->addWidget(rateLabel);
    mainLayout->addWidget(rateEdit);

    hasCarSeatCheck = new QCheckBox("Есть детское кресло", this);
    mainLayout->addWidget(hasCarSeatCheck);

    QPushButton *chooseFileButton = new QPushButton("Выбрать файл...", this);
    mainLayout->addWidget(chooseFileButton);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *saveButton = new QPushButton("Сохранить", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &QAddCarDialog::onSaveButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(chooseFileButton, &QPushButton::clicked, this, &QAddCarDialog::onChooseFileButtonClicked);

    // Connect checkboxes to the slot
    connect(checkbox1, &QCheckBox::stateChanged, this, &QAddCarDialog::onCheckboxChanged);
    connect(checkbox2, &QCheckBox::stateChanged, this, &QAddCarDialog::onCheckboxChanged);
}

QAddCarDialog::~QAddCarDialog() {
}

void QAddCarDialog::onChooseFileButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл"), QDir::homePath(),
                                                    tr("Изображения (*.jpg *.jpeg *.png)"));
    if (!filePath.isEmpty()) {
        imagePath = filePath;
    }
}

void QAddCarDialog::onSaveButtonClicked() {
    QString id = QUuid::createUuid().toString();
    QString brand = brandEdit->text();
    QString model = modelEdit->text();
    QString volume = volumeEdit->text();
    BodyType bodyType = static_cast<BodyType>(bodyTypeCombo->currentData().toInt());
    Transmission transmission = static_cast<Transmission>(transmissionCombo->currentData().toInt());
    double rate = rateEdit->text().toDouble();
    bool hasCarSeat = hasCarSeatCheck->isChecked();

    Car newCar(id, brand, model, volume, bodyType, transmission, hasCarSeat, rate);

    carService.insertCar(newCar);

    // Copy the selected image to the specified directory
    QFileInfo fileInfo(imagePath);
    QString extension = fileInfo.completeSuffix();
    QString newImagePath = "/Users/noriksaroyan/CLionProjects/CarService/UI/static/img/" + id + "." + extension;

    if (QFile::copy(imagePath, newImagePath)) {
        pathService.addPath(newImagePath.toStdString(), id.toStdString());
        QMessageBox::information(this, "Успех", "Машина успешно добавлена!");
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось скопировать изображение.");
    }
}

void QAddCarDialog::onCheckboxChanged(int state) {
    Q_UNUSED(state); // Unused parameter

    if (checkbox1->isChecked() && checkbox2->isChecked()) {
        // Ensure mutual exclusivity
        if (sender() == checkbox1) {
            checkbox2->setChecked(false);
        } else if (sender() == checkbox2) {
            checkbox1->setChecked(false);
        }
    }

    if (checkbox1->isChecked()) {
        transmissionLabel->show();
        transmissionCombo->show();
        bodyTypeLabel->show();
        bodyTypeCombo->show();
    } else if (checkbox2->isChecked()) {
        transmissionLabel->hide();
        transmissionCombo->hide();
        bodyTypeLabel->hide();
        bodyTypeCombo->hide();
    }
}
