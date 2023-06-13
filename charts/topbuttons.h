#ifndef TOPBUTTONS_H
#define TOPBUTTONS_H
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>

class TopButtons : public QWidget {
    Q_OBJECT
public:
    TopButtons(QWidget* parent = nullptr);
    ~TopButtons() {
        delete chartType;
        delete chartTypeLabel;
        delete isBlackAndWhite;
        delete isBlackAndWhiteLabel;
        delete printToPDF;
        delete chooseFolder;
    }
//private:
    QComboBox* chartType;
    QLabel* chartTypeLabel;
    QCheckBox* isBlackAndWhite;
    QLabel* isBlackAndWhiteLabel;
    QPushButton* printToPDF;
    QPushButton* chooseFolder;
};

#endif // TOPBUTTONS_H
