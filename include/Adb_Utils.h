//
// Created by 86133 on 25-6-4.
//

#ifndef ADB_UTILS_H
#define ADB_UTILS_H
#include <qstring.h>
#include <string>
#include <vector>


class Adb_Utils {
public:
    explicit Adb_Utils(const std::string &adb_path);

    ~Adb_Utils() = default;

    std::string exec_cmd(const std::string &cmd);

    std::string adb_connect_device(const std::string &port);

    std::vector<std::string> get_adb_device();

    // bool has_content_after(const std::string &str, const std::string &target);

    bool close_adb();

    std::pair<int,int>get_device_size(const QString &selected_device);

private:
    std::string adb_path;
    // std::string port;
};


#endif //ADB_UTILS_H
