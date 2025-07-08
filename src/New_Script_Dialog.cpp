//
// Created by 86133 on 25-6-1.
//

#include "../include/New_Script_Dialog.h"

#include <qcoreapplication.h>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDir>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonObject>

New_Script_Dialog::New_Script_Dialog(QWidget *parent) {
    setupUI();
}

void New_Script_Dialog::setupUI() {
    setWindowTitle("新建脚本");
    name_edit = new QLineEdit;
    author_edit = new QLineEdit;
    description_edit = new QLineEdit;

    QFormLayout *layout_form = new QFormLayout;
    layout_form->addRow("脚本名称:", name_edit);
    layout_form->addRow("作者：", author_edit);
    layout_form->addRow("描述：", description_edit);

    QDialogButtonBox *btn_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btn_box, &QDialogButtonBox::accepted, this, New_Script_Dialog::new_script_json);
    connect(btn_box, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(layout_form);
    v_layout->addWidget(btn_box);
    setLayout(v_layout);
}

void New_Script_Dialog::new_script_json() {
    QString name = name_edit->text().trimmed();
    QString author = author_edit->text().trimmed();
    QString description = description_edit->text().trimmed();
    if (name.isEmpty() || author.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "警告", "字段均不能为空");
        return;
    }
    QDir script_dir = QCoreApplication::applicationDirPath() + "/scripts/";
    if (script_dir.exists(name)) {
        QMessageBox::warning(this, "警告", "该名称脚本已存在");
        return;
    }
    if (!script_dir.mkdir(name)) {
        QMessageBox::warning(this, "错误", "创建脚本文件夹失败");
        qCritical() << "[ERROR]" << "Failed to create the script folder: " << name;
        return;
    }
    QJsonObject info;
    info["name"] = name;
    info["author"] = author;
    info["description"] = description;
    QFile info_file(script_dir.absolutePath() + "/" + name + "/info.json");
    if (info_file.open(QIODevice::WriteOnly)) {
        info_file.write(QJsonDocument(info).toJson());
        info_file.close();
    } else {
        QMessageBox::warning(this, "错误", "写入" + name + "的info.json失败");
        qCritical() << "[ERROR]" << "Failed to write to file: " << name << "/" << "info.json";
        return;
    }
    QMessageBox::information(this, "成功", "脚本创建成功");
    qInfo() << "[INFO]" << "Script " << name << " is created";
    emit script_created();
    accept();
}
