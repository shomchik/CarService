#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include "../../Entities/car/BodyType.h"
#include "../../Entities/car/Transmission.h"

class FilterDialog : public QDialog {
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);

signals:
    void filterApplied(BodyType bodyType, Transmission transmission);

private slots:
    void applyFilter();

private:
    QLabel *bodyTypeLabel;
    QLabel *transmissionLabel;
    QComboBox *bodyTypeComboBox;
    QComboBox *transmissionComboBox;
    QPushButton *applyButton;
};
