#ifndef QADDCARDIALOG_H
#define QADDCARDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include "../../../Services/car/CarService.h"
#include "../../../Entities/car/BodyType.h"
#include "../../../Entities/car/Transmission.h"
#include "../../../Services/path/PathService.h"

class QAddCarDialog : public QDialog {
    Q_OBJECT

public:
    explicit QAddCarDialog(QWidget *parent = nullptr);

    ~QAddCarDialog();

private slots:
    void onSaveButtonClicked();

    void onChooseFileButtonClicked();

private:
private:
    QLineEdit *brandEdit;
    QLineEdit *modelEdit;
    QLineEdit *volumeEdit;
    QComboBox *bodyTypeCombo;
    QComboBox *transmissionCombo;
    QLineEdit *rateEdit;
    QCheckBox *hasCarSeatCheck;
    QString imagePath; // Changed to QString object
    CarService carService;
    PathService pathService; // Included PathService header
};

#endif // QADDCARDIALOG_H
