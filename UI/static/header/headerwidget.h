#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QStringListModel>
#include <QDesktopWidget>
#include <QApplication>
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
    void updateSearchResults(const std::pair<std::vector<Order>, std::vector<Car>> &results);
    void clearSearchResults();
    void handleSearchResultClick(const QModelIndex &index);

private:
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QListView *searchResultsListView;
    QStringListModel *searchResultsModel;
    SearchService searchService;
};
#endif // HEADERWIDGET_H
