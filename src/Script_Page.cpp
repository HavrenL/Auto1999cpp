//
// Created by 86133 on 25-6-4.
//

#include "../include/Script_Page.h"
#include "../include/Adb_Utils.h"
#include  "../include/Scrcpy_Utils.h"
#include <qboxlayout.h>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <thread>
#include <QThread>

#include "../include/Add_Script_Card.h"


Script_Page::Script_Page(QWidget *parent) {
    setupUI();
    emit refresh_combo_devices();
}

void Script_Page::setupUI() {
    adb = new Adb_Utils("C:/Users/86133/Desktop/Auto1999cpp/cmake-build-debug/platform-tools/adb.exe");
    Scrcpy_Utils *scrcpy = new Scrcpy_Utils();
    QVBoxLayout *layout_page = new QVBoxLayout();
    QWidget *bar = new QWidget();
    QHBoxLayout *layout_bar = new QHBoxLayout;
    QLineEdit *ld_port = new QLineEdit(bar);
    ld_port->setPlaceholderText("模拟器端口号");
    ld_port->setFixedWidth(100);
    QPushButton *btn_connect = new QPushButton("连接设备", bar);
    connect(this, &Script_Page::refresh_combo_devices, this, &Script_Page::refresh_adb_devices);
    connect(btn_connect, &QPushButton::clicked, [this,ld_port]() {
        if (std::string result = adb->adb_connect_device(ld_port->text().toStdString()); result == "") {
            QMessageBox::information(nullptr, "成功", "成功连接端口：" + ld_port->text());
            emit refresh_combo_devices();
        } else {
            QMessageBox::warning(nullptr, "失败", "请优先检查端口是否错误或者模拟器是否开启\n" + QString::fromStdString(result));
        }
    });
    combo_devices = new QComboBox(bar);
    combo_devices->setPlaceholderText("下拉选择捕获窗口设备");
    combo_devices->setFixedWidth(300);
    QPushButton *btn_refresh = new QPushButton("刷新设备列表", bar);
    connect(btn_refresh, &QPushButton::clicked, this, &Script_Page::refresh_adb_devices);
    QPushButton *btn_catch = new QPushButton("捕获窗口", bar);

    QHBoxLayout *layout_workspace = new QHBoxLayout();
    QVBoxLayout *layout_script_workspace = new QVBoxLayout();
    QVBoxLayout *layout_scrcpy = new QVBoxLayout();
    QWidget *scrcpy_space = new QWidget();
    scrcpy_space->setFixedWidth(300);
    layout_scrcpy->addWidget(scrcpy_space);
    layout_workspace->addLayout(layout_script_workspace);
    layout_workspace->addLayout(layout_scrcpy);
    QWidget *script_workspace = new QWidget();

    connect(btn_catch, &QPushButton::clicked, this, [scrcpy,scrcpy_space,this]() {
        if (scrcpy_space->layout()) {
            QLayout *old_layout = scrcpy_space->layout();
            QLayoutItem *item;
            while (item = old_layout->takeAt(0)) {
                delete item;
            }
            delete old_layout;
        }
        scrcpy->start_and_embed(scrcpy_space, this->combo_devices->currentText());
    });
    layout_bar->addWidget(ld_port);
    layout_bar->addWidget(btn_connect);
    layout_bar->addWidget(combo_devices);
    layout_bar->addWidget(btn_refresh);
    layout_bar->addWidget(btn_catch);
    bar->setLayout(layout_bar);
    bar->setFixedHeight(50);
    layout_page->addWidget(bar);

    layout_script_workspace->addWidget(script_workspace);
    layout_page->addLayout(layout_workspace);
    setLayout(layout_page);
}

void Script_Page::refresh_adb_devices() {
    QThread *thread = QThread::create([this]() {
        auto devices = adb->get_adb_device();
        QStringList q_devices;
        for (const auto &device: devices) {
            q_devices.append(QString::fromStdString(device));
        }
        QMetaObject::invokeMethod(this, [this,q_devices]() {
            combo_devices->clear();
            combo_devices->addItems(q_devices);
        }, Qt::QueuedConnection);
    });
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}
