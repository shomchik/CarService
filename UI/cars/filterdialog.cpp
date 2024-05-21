//
// Created by Norik Saroyan on 21.05.24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FilterDialog.h" resolved

#include "filterdialog.h"

#include <QVBoxLayout>

#include "../../serializers/car/CarSerializer.h"


FilterDialog::FilterDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Filter Cars");

    bodyTypeLabel = new QLabel("Body Type:", this);
    transmissionLabel = new QLabel("Transmission:", this);

    bodyTypeComboBox = new QComboBox(this);
    transmissionComboBox = new QComboBox(this);

    bodyTypeComboBox->addItem("Any");
    transmissionComboBox->addItem("Any");

    // for (int i = 0; i < static_cast<int>(BodyType); ++i) {
    //
    //     bodyTypeComboBox->addItem(CarSerializer::bodyTypeToString(static_cast<BodyType>(i)));
    // }
    //
    // for (int i = 0; i < static_cast<int>(Transmission::COUNT); ++i) {
    //     transmissionComboBox->addItem(transmissionToString(static_cast<Transmission>(i)));
    // }

    applyButton = new QPushButton("Apply", this);

    connect(applyButton, &QPushButton::clicked, this, &FilterDialog::applyFilter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(bodyTypeLabel);
    layout->addWidget(bodyTypeComboBox);
    layout->addWidget(transmissionLabel);
    layout->addWidget(transmissionComboBox);
    layout->addWidget(applyButton);
}

void FilterDialog::applyFilter() {
    BodyType selectedBodyType = static_cast<BodyType>(bodyTypeComboBox->currentIndex());
    Transmission selectedTransmission = static_cast<Transmission>(transmissionComboBox->currentIndex());
    emit filterApplied(selectedBodyType, selectedTransmission);
}
