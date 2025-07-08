//
// Created by 86133 on 25-5-30.
//

#ifndef HOME_PAGE_H
#define HOME_PAGE_H
#include <qcoreapplication.h>
#include <QWidget>
#include <QGridLayout>


class Home_Page : public QWidget {
    Q_OBJECT

public:
    explicit Home_Page(QWidget *parent = nullptr);

    ~Home_Page() = default;

    void setupUI();

    QList<QPair<QString, QString> > get_all_scripts_dir(
        const QString &path = QCoreApplication::applicationDirPath() + "/scripts");

    void refresh_page();

private:
    int width;
    int height;
    QWidget *content;
    QGridLayout *g_layout;
};


#endif //HOME_PAGE_H
