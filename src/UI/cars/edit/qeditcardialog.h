#ifndef QEDITCARDIALOG_H
#define QEDITCARDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include "../../../Services/car/CarService.h"
#include "../../../Entities/car/BodyType.h"
#include "../../../Entities/car/Transmission.h"

class QEditCarDialog : public QDialog {
    Q_OBJECT

public:
    explicit QEditCarDialog(const Car &car, QWidget *parent = nullptr);

    ~QEditCarDialog();

private slots:
    void onSaveButtonClicked();

private:
    QLineEdit *brandEdit;
    QLineEdit *modelEdit;
    QLineEdit *volumeEdit;
    QComboBox *bodyTypeCombo;
    QComboBox *transmissionCombo;
    QLineEdit *rateEdit;
    QCheckBox *hasCarSeatCheck;
    CarService carService;
    Car currentCar;
};

#endif // QEDITCARDIALOG_H
