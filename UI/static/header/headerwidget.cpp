#include "headerwidget.h"
#include <QFont>
#include <QVBoxLayout>

HeaderWidget::HeaderWidget(const QString &text, QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    headerLabel = new QLabel(text, this);
    setFixedHeight(40);

    QFont font("Arial", 24, QFont::Bold);
    headerLabel->setFont(font);

    headerLabel->setStyleSheet("color: #000;"); // Black color

    headerLabel->setAlignment(Qt::AlignLeft);

    layout->addWidget(headerLabel);

    layout->setSpacing(0);
}
