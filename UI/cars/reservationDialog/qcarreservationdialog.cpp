//
// Created by Norik Saroyan on 24.04.24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QCarReservationDialog.h" resolved

#include "qcarreservationdialog.h"
#include "ui_QCarReservationDialog.h"


QCarReservationDialog::QCarReservationDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::QCarReservationDialog) {
    ui->setupUi(this);
}

QCarReservationDialog::~QCarReservationDialog() {
    delete ui;
}
