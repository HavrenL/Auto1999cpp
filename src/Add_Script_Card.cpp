//
// Created by 86133 on 25-5-31.
//

#include "../include/Add_Script_Card.h"

#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>

#include "../include/New_Script_Dialog.h"
#include <QPushButton>
#include <QVBoxLayout>

Add_Script_Card::Add_Script_Card(QWidget *parent, int width, int height): Script_Card(parent), width(width),
                                                                          height(height) {
    setupUI();
}

void Add_Script_Card::setupUI() {
    setFixedWidth(width);
    setFixedHeight(height);
    QVBoxLayout *v_layout = new QVBoxLayout;
    QPushButton *btn_import = new QPushButton("导入", this);
    QPushButton *btn_add = new QPushButton("新建", this);
    connect(btn_import, &QPushButton::clicked, this, &Add_Script_Card::import_script_card);
    connect(btn_add, &QPushButton::clicked, this, Add_Script_Card::create_script_card);
    v_layout->addWidget(btn_import);
    v_layout->addWidget(btn_add);
    setLayout(v_layout);
}

void Add_Script_Card::create_script_card() {
    New_Script_Dialog *new_script = new New_Script_Dialog(this);
    connect(new_script, &New_Script_Dialog::script_created, this, &Add_Script_Card::script_created);
    new_script->exec();
}

void Add_Script_Card::import_script_card() {
    QFileDialog *import_script = new QFileDialog(this);
    import_script->setFileMode(QFileDialog::Directory);
    import_script->setWindowTitle("选择导入脚本");
    if (import_script->exec() != QDialog::Accepted) {
        qInfo() << "[INFO]" << "The script folder selection was canceled";
        return;
    }
    QStringList import_script_dir = import_script->selectedFiles();
    // qDebug()<<import_script_dir;
    if (import_script_dir.isEmpty()) {
        qWarning() << "[WARNING]" << "The script folder is not selected";
        return;
    }
    QString src_dir_path = import_script_dir.first();
    // TODO: QCoreApplication::applicationDirPath()要优化
    QString dest_dir_path = QCoreApplication::applicationDirPath() + "/scripts/" + QFileInfo(src_dir_path).fileName();

    if (copyDirectory(src_dir_path, dest_dir_path)) {
        QMessageBox::information(this, "成功", "脚本导入成功");
        emit script_created();
        qInfo() << "[INFO]" << "Script " + QFileInfo(src_dir_path).fileName() + " was successfully imported";
    }
}

// TODO:检查需要完善
bool Add_Script_Card::copyDirectory(const QString &srcPath, const QString &dstPath) {
    qInfo() << "[INFO]" << "Try to copy the Script " + QFileInfo(srcPath).fileName() + " folder";
    QDir srcDir(srcPath);
    if (!srcDir.exists())
        return false;

    QDir dstDir(dstPath);
    if (!dstDir.exists()) {
        if (!dstDir.mkpath(".")) {
            QMessageBox::warning(nullptr, "失败", "创建（复制）脚本文件夹失败");
            qWarning() << "[WARNING]" << "The Script " + QFileInfo(srcPath).fileName() +
                    " folder creation (copying) failed";
            return false;
        }
    } else {
        QMessageBox::warning(nullptr, "失败", "脚本已存在（请检查脚本文件夹重名问题）");
        qWarning() << "[WARNING]" << "The Script " + QFileInfo(srcPath).fileName() +
                " folder already exists,Please check the script folder duplicate name issue";
        return false;
    }

    QFileInfoList entries = srcDir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for (const QFileInfo &entry: entries) {
        QString srcFilePath = entry.absoluteFilePath();
        QString dstFilePath = dstDir.filePath(entry.fileName());
        if (entry.isDir()) {
            if (!copyDirectory(srcFilePath, dstFilePath))
                return false;
        } else {
            if (QFile::exists(dstFilePath))
                QFile::remove(dstFilePath);
            if (!QFile::copy(srcFilePath, dstFilePath))
                return false;
        }
    }
    return true;
}
