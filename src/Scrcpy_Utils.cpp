//
// Created by 86133 on 25-6-6.
//

#include "../include/Scrcpy_Utils.h"

#include <QMessageBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWindow>
#include "../include/Add_Script_Card.h"

Scrcpy_Utils::Scrcpy_Utils(QObject *parent): QObject(parent) {
}

Scrcpy_Utils::~Scrcpy_Utils() {
    stop();
}

bool Scrcpy_Utils::start_and_embed(QWidget *target_widget, QString selected_device, const QString &scrcpy_path,
                                   const QString &window_title,
                                   int width) {
    stop();
    current_title = window_title;

    scrcpy_process = new QProcess(this);

    qInfo() << "[INFO] Start scrcpy with device:" << selected_device << ", window_title:" << window_title << ", width:"
            << width;

    QStringList args;
    args << "-s" << selected_device.section('\t', 0, 0)
            << "--window-title=" + window_title
            << "--window-width=" + QString::number(width);

    qInfo() << "[INFO] scrcpy path:" << scrcpy_path;
    qInfo() << "[INFO] scrcpy args:" << args;

    scrcpy_process->start(scrcpy_path, args);

    if (!scrcpy_process->waitForStarted(3000)) {
        qWarning() << "[WARNING] scrcpy process failed to start!";
        return false;
    }
    qInfo() << "[INFO] scrcpy process started successfully.";

    QTimer::singleShot(1200, this, [=]() {
        qInfo() << "[INFO] Try to find scrcpy window with title:" << window_title;
        WId hwnd = find_scrcpy_window(window_title);
        if (hwnd) {
            qInfo() << "[INFO] scrcpy window found, embedding to target widget.";
            QWindow *win = QWindow::fromWinId(hwnd);
            scrcpy_container = QWidget::createWindowContainer(win, target_widget);

            QVBoxLayout *layout = new QVBoxLayout(target_widget);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->addWidget(scrcpy_container);
            target_widget->setLayout(layout);

            qInfo() << "[INFO] scrcpy window embedded successfully.";
            emit scrcpy_started();
        } else {
            emit scrcpy_failed();
            qWarning() << "[WARNING] The scrcpy window was not found, title:" << window_title;
            QMessageBox::warning(target_widget, "错误", "未找到scrcpy窗口");
        }
    });

    connect(scrcpy_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [this](int exitCode, QProcess::ExitStatus exitStatus) {
                qInfo() << "[INFO] scrcpy process finished. Exit code:" << exitCode << ", Exit status:" << exitStatus;
                emit scrcpy_stopped();
            });

    return true;
}

void Scrcpy_Utils::stop() {
    qInfo() << "[INFO] Enter function stop()";
    if (scrcpy_process) {
        qInfo() << "[INFO] Killing scrcpy process...";
        scrcpy_process->kill();
        scrcpy_process->waitForFinished(1000);
        scrcpy_process->deleteLater();
        scrcpy_process = nullptr;
        qInfo() << "[INFO] scrcpy process killed and cleaned up.";
    }
    if (scrcpy_container) {
        qInfo() << "[INFO] Deleting scrcpy container widget.";
        delete scrcpy_container;
        scrcpy_container = nullptr;
    }
    qInfo() << "[INFO] Exit function stop()";
}

bool Scrcpy_Utils::is_running() {
    bool running = scrcpy_process && scrcpy_process->state() == QProcess::Running;
    qInfo() << "[INFO] scrcpy is_running:" << running;
    return running;
}

WId Scrcpy_Utils::find_scrcpy_window(const QString &window_title) {
#ifdef Q_OS_WIN
    qInfo() << "[INFO] Finding scrcpy window, title:" << window_title;
    std::wstring wtitle = window_title.toStdWString();
    HWND hwnd = FindWindowW(NULL, wtitle.c_str());
    if (hwnd) {
        qInfo() << "[INFO] scrcpy window handle found:" << reinterpret_cast<WId>(hwnd);
    } else {
        qWarning() << "[WARNING] scrcpy window handle not found for title:" << window_title;
    }
    return reinterpret_cast<WId>(hwnd);
#else
    // TODO: 平台扩展
    qWarning() << "[WARNING] find_scrcpy_window not implemented for this platform.";
    return 0;
#endif
}
