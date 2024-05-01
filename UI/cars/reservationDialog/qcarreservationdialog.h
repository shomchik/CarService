//
// Created by Norik Saroyan on 24.04.24.
//

#ifndef CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H
#define CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class QCarReservationDialog; }
QT_END_NAMESPACE

class QCarReservationDialog : public QDialog {
Q_OBJECT

public:
    explicit QCarReservationDialog(QWidget *parent = nullptr);

    ~QCarReservationDialog() override;

private:
    Ui::QCarReservationDialog *ui;
};


#endif //CARLEASINGSERVICE_QCARRESERVATIONDIALOG_H
