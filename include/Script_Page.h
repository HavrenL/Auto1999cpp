//
// Created by 86133 on 25-6-4.
//

#ifndef SCRIPT_PAGE_H
#define SCRIPT_PAGE_H
#include <QComboBox>
#include <QWidget>
#include "Adb_Utils.h"


class Script_Page : public QWidget {
    Q_OBJECT

public:
    explicit Script_Page(QWidget *parent = nullptr);

    ~Script_Page() = default;

    void setupUI();

    void refresh_adb_devices();

private:
    QComboBox *combo_devices;
    Adb_Utils *adb;
signals:
    void refresh_combo_devices();
};


#endif //SCRIPT_PAGE_H
