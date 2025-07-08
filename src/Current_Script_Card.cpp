#include "../include/Current_Script_Card.h"

#include <QDialogButtonBox>
#include <QDir>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDialog>
#include <QMessageBox>

Current_Script_Card::Current_Script_Card(const QString &path, QWidget *parent, int width,
                                         int height): script_path(path), Script_Card(parent), width(width),
                                                      height(height) {
    setupUI();
}

void Current_Script_Card::setupUI() {
    setFixedWidth(width);
    setFixedHeight(height);
    QList<QPair<QString, QString> > script_info = read_script_info();
    QString introduce_text = "脚本：" + script_info[0].second + "\n" + "作者：" + script_info[1].second + "\n" + "描述：" +
                             script_info[2].second;
    // QString q_introduce_text = QString::fromStdString(introduce_text);
    QTextEdit *script_introduce = new QTextEdit(this);
    script_introduce->setText(introduce_text);
    QPushButton *btn_edit = new QPushButton("编辑", this);
    QPushButton *btn_delete = new QPushButton("删除", this);
    connect(btn_delete, &QPushButton::clicked, this, &Current_Script_Card::delete_script_card);
    QPushButton *button_run = new QPushButton("运行", this);
    QVBoxLayout *v_layout = new QVBoxLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;
    v_layout->addWidget(script_introduce);
    h_layout->addWidget(btn_edit);
    h_layout->addWidget(button_run);
    v_layout->addLayout(h_layout);
    v_layout->addWidget(btn_delete);
    setLayout(v_layout);
}

QList<QPair<QString, QString> > Current_Script_Card::read_script_info() {
    QList<QPair<QString, QString> > script_info;
    QFile info(script_path + "/info.json");
    if (!info.open(QIODevice::ReadOnly)) {
        qWarning() << "[WARNING]" << "Cannot open info.json in " << script_path;
        return script_info;
    }
    QByteArray json = info.readAll();
    info.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if (!doc.isObject()) {
        qWarning() << "[WARNING]" << "Cannot read info.json in " << script_path;
        return script_info;
    }
    QJsonObject obj = doc.object();
    script_info.append(QPair<QString, QString>("name", obj.value("name").toString()));
    script_info.append(QPair<QString, QString>("author", obj.value("author").toString()));
    script_info.append(QPair<QString, QString>("description", obj.value("description").toString()));
    return script_info;
}

void Current_Script_Card::delete_script_card() {
    QDir dir(script_path);
    if (!dir.exists()) {
        qWarning() << "[WARNING]" << "Cannot open directory " << script_path;
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this, // 父窗口（当前窗口）
        "确认删除", // 对话框标题
        "确定要删除脚本 " + QFileInfo(script_path).fileName() + " 吗？", // 提示信息
        QMessageBox::Yes | QMessageBox::No // 按钮选项
    );
    if (reply == QMessageBox::Yes) {
        if (dir.removeRecursively()) {
            qInfo() << "[INFO]" << "Deleting script " << script_path;
            emit script_deleted();
            return;
        } else {
            qWarning() << "[WARNING]" << "Cannot delete script " << script_path;
            return;
        }
    }
}
