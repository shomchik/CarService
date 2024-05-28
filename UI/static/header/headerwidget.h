#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QString>
#include <QModelIndex>
#include <vector>
#include <utility>
#include "../../../Services/car/CarService.h"
#include "../../../Entities/car/Car.h"
#include "../../../Entities/order/Order.h"
#include "../../../Services/search/SearchService.h"

class HeaderWidget : public QWidget {
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);

signals:
    void catalogClicked();

    void ordersClicked();

    void searchResultClicked(const QString &result);

private slots:
    void performSearch();

    void handleSearchResultClick(const QModelIndex &index);

private:
    void updateSearchResults(const pair<vector<Order>, vector<Car> > &results);

    void clearSearchResults();

    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QListView *searchResultsListView;
    QStringListModel *searchResultsModel;
    SearchService searchService;
};

#endif // HEADERWIDGET_H
