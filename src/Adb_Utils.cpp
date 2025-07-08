//
// Created by 86133 on 25-6-4.
//

#include "../include/Adb_Utils.h"
#include <QProcess>
#include <QDebug>
#include <regex>


Adb_Utils::Adb_Utils(const std::string &adb_path): adb_path(adb_path) {
}

std::string Adb_Utils::exec_cmd(const std::string &cmd) {
    qInfo() << "[INFO]" << "Try running command: " << QString::fromStdString(cmd);

    QProcess process;
#if defined(Q_OS_WIN)
    process.start("cmd", QStringList() << "/c" << QString::fromStdString(cmd));
#else

#endif
    bool finished = process.waitForFinished(5000);
    if (!finished) {
        qWarning() << "[WARNING]" << "Command timeout: " << QString::fromStdString(cmd);
        process.kill();
        return "";
    }
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();
    if (!error.isEmpty()) {
        qWarning() << "[WARNING]" << "Command error output: " << error;
    }
    qInfo() << "[INFO]" << "Command output: " << output;
    return output.toStdString();
}


std::string Adb_Utils::adb_connect_device(const std::string &port) {
    std::string ip = "127.0.0.1:";
    std::string cmd = adb_path + " connect " + ip + port;
    std::string output = exec_cmd(cmd);
    bool success = output.find("connected to") != std::string::npos;
    if (success) {
        qInfo() << "[INFO]" << "Successfully connected to " << QString::fromStdString(ip + port);
    } else {
        qWarning() << "[WARNING]" << "Failed to connect to " << QString::fromStdString(ip + port) << "," <<
                QString::fromStdString(output);
        return output;
    }
    return "";
}

std::vector<std::string> Adb_Utils::get_adb_device() {
    std::vector<std::string> devices;
    std::string cmd = adb_path + " devices";
    std::string result = exec_cmd(cmd);

    size_t pos = result.find("List of devices attached");
    if (pos == std::string::npos) {
        qWarning() << "[WARNING]" << "Failed to list devices";
        return devices;
    }
    std::string after = result.substr(pos + std::string("List of devices attached").length());

    std::istringstream iss(after);
    std::string line;
    while (std::getline(iss, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (!line.empty()) {
            devices.push_back(line);
            qInfo() << "[INFO]" << "Found device: " << QString::fromStdString(line);
        }
    }
    return devices;
}

bool Adb_Utils::close_adb() {
    std::string cmd = adb_path + " kill-server";
    std::string result = exec_cmd(cmd);
    if (result.empty()) {
        qInfo() << "[INFO]" << "Successfully to close adb";
        return true;
    }
    qWarning() << "[WARNING]" << "Failed to close adb";
    return false;
}

std::pair<int, int> Adb_Utils::get_device_size(const QString &selected_device) {
    std::string device_id = selected_device.section(' ', 0, 0).toStdString();
    std::string cmd = adb_path + " -s " + device_id + " shell wm size";
    std::string result = exec_cmd(cmd);
    std::regex re("Physical size: (\\d+)x(\\d+)");
    std::smatch match;
    if (std::regex_search(result, match, re)) {
        int height = std::stoi(match[1]); //1080
        int width = std::stoi(match[2]); //1920
        qInfo() << "[INFO]" << "Get" << QString::fromStdString(device_id) << "size: " <<
                QString::fromStdString(std::to_string(height)) << "x" << QString::fromStdString(std::to_string(width));
        return {width, height};
    }
    qWarning() << "[WARNING]" << "Failed to get the size of device: " << QString::fromStdString(device_id);
    return {0, 0};
}
