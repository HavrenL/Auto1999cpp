//
// Created by 86133 on 25-6-6.
//

#ifndef SCRCPY_UTILS_H
#define SCRCPY_UTILS_H
#include <qobject.h>
#include <QProcess>
#include <qwindowdefs.h>
// #include <QWindow>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

class Scrcpy_Utils : public QObject {
    Q_OBJECT

public:
    explicit Scrcpy_Utils(QObject *parent = nullptr);

    ~Scrcpy_Utils();

    bool start_and_embed(QWidget *target_widget, QString selected_device,
                         const QString &scrcpy_path =
                                 "C:/Users/86133/Desktop/Auto1999cpp/cmake-build-debug/scrcpy/scrcpy.exe",
                         const QString &window_title = "ScrcpyCatch", int width = 300);

    void stop();

    bool is_running();

private:
    QProcess *scrcpy_process = nullptr;
    QWidget *scrcpy_container = nullptr;
    QString current_title;

    WId find_scrcpy_window(const QString &window_title);

signals:
    void scrcpy_started();

    void scrcpy_stopped();

    void scrcpy_failed();
};


#endif //SCRCPY_UTILS_H
