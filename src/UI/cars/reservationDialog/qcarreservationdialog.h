#ifndef CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H
#define CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "../../../Entities/car/Car.h"
#include "../../../Services/car/CarService.h"
#include "../../../Services/client/ClientService.h"
#include "../../../Services/order/OrderService.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class QCarReservationDialog;
}

QT_END_NAMESPACE

class QCarReservationDialog : public QDialog {
    Q_OBJECT

public:
    explicit QCarReservationDialog(const Car &car, QWidget *parent = nullptr);

    ~QCarReservationDialog() override;

private slots:
    int calculateDays(const QDate &startDate, const QDate &endDate);

private:
    Ui::QCarReservationDialog *ui;
    Car m_car;
    OrderService orderService;
    CarService carService;
    ClientService clientService;
    void setupLayout();

    void applyStyles();

    QWidget *createInputField(const QString &labelText);

    QWidget *createDateInputField(const QString &labelText, const QDate &date);

    bool validateFields(QWidget *passportField, QWidget *driverLicenseField);
};

#endif // CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H
