#ifndef CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H
#define CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "../../../Entities/car/Car.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QCarReservationDialog; }
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

    void setupLayout();

    QWidget *createInputField(const QString &labelText);

    QWidget *createDateInputField(const QString &labelText, const QDate &date);
};

#endif // CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H
