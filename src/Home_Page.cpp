//
// Created by 86133 on 25-5-30.
//

#include "../include/Home_Page.h"

#include <QDir>

#include "../include/Current_Script_Card.h"
#include "../include/Add_Script_Card.h"
#include <QGridLayout>
#include <QScrollArea>

Home_Page::Home_Page(QWidget *parent): QWidget(parent) {
    setupUI();
}

void Home_Page::setupUI() {
    QScrollArea *scrollsrea = new QScrollArea(this);
    content = new QWidget(scrollsrea);

    auto script_paths = get_all_scripts_dir();

    g_layout = new QGridLayout;
    for (int n = 0; n < script_paths.size(); ++n) {
        int row = n / 3;
        int col = n % 3;
        // const QString &script_path=script_paths[n].second;
        auto *script_card = new Current_Script_Card(script_paths[n].second, content);
        connect(script_card, &Current_Script_Card::script_deleted, this, &Home_Page::refresh_page);
        g_layout->addWidget(script_card, row, col);
    }

    Add_Script_Card *add_script_card = new Add_Script_Card(content);
    g_layout->addWidget(add_script_card, script_paths.size() / 3, script_paths.size() % 3);

    connect(add_script_card, &Add_Script_Card::script_created, this, &Home_Page::refresh_page);

    content->setLayout(g_layout);

    scrollsrea->setWidget(content);
    scrollsrea->setWidgetResizable(true);

    QVBoxLayout *v_layout = new QVBoxLayout(this);
    v_layout->addWidget(scrollsrea);
    setLayout(v_layout);
}

// TODO:按照创建时间顺序排序返回
QList<QPair<QString, QString> > Home_Page::get_all_scripts_dir(const QString &path) {
    QList<QPair<QString, QString> > result;
    QDir dir(path);
    if (!dir.exists()) {
        qWarning() << "[WARNING]" << "Script directory does not exist: " << path;
        return result;
    }
    QStringList script_files = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    if (script_files.empty()) {
        qInfo() << "[Info]" << "No script files found";
        return result;
    }
    for (const QString &script_file: script_files) {
        QString abspath = dir.absoluteFilePath(script_file);
        result.append(QPair<QString, QString>(script_file, abspath));
    }
    return result;
}

void Home_Page::refresh_page() {
    // 清空 g_layout
    while (g_layout->count() > 0) {
        QLayoutItem *item = g_layout->takeAt(0);
        if (item->widget()) delete item->widget();
        delete item;
    }
    // 重新添加卡片
    auto script_paths = get_all_scripts_dir();
    for (int n = 0; n < script_paths.size(); ++n) {
        int row = n / 3;
        int col = n % 3;
        auto *card = new Current_Script_Card(script_paths[n].second, content);
        g_layout->addWidget(card, row, col);
    }
    Add_Script_Card *add_script_card = new Add_Script_Card(content);
    g_layout->addWidget(add_script_card, script_paths.size() / 3, script_paths.size() % 3);
    connect(add_script_card, &Add_Script_Card::script_created, this, &Home_Page::refresh_page);
}
