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

private slots:
    void onSelectionChange(const QItemSelection &selected);

private:
    QFileSystemModel *rightPartModel;
    QFileSystemModel *leftPartModel;
    QTreeView *treeView;
    QTableView *tableView;
    QHBoxLayout *hLayout;
};

#endif // FILESVIEW_H
