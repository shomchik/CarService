#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QLabel>

class HeaderWidget : public QWidget {
Q_OBJECT
public:
    explicit HeaderWidget(const QString& text, QWidget *parent = nullptr);

private:
    QLabel *headerLabel;
};

#endif // HEADERWIDGET_H
