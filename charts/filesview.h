#ifndef FILESVIEW_H
#define FILESVIEW_H
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QHBoxLayout>

class FilesView : public QWidget {
    Q_OBJECT
public:
    FilesView(QWidget *parent);
    ~FilesView() {};

    QItemSelectionModel *selectionModel;
public slots:
    void onSelectionChange(QString folderPath);

private:
    QFileSystemModel *model;
    QTableView *tableView;
    QHBoxLayout *hLayout;
};

#endif // FILESVIEW_H
