//
// Created by 86133 on 25-5-31.
//

#ifndef ADD_SCRIPT_CARD_H
#define ADD_SCRIPT_CARD_H
#include <QApplication>

#include "Script_Card.h"


class Add_Script_Card : public Script_Card {
    Q_OBJECT

public:
    explicit Add_Script_Card(QWidget *parent = nullptr, int width = 250, int height = 200);

    ~Add_Script_Card() = default;

    void setupUI() override;

    void create_script_card();

    void import_script_card();

    bool copyDirectory(const QString &srcPath,
                       const QString &dstPath = QCoreApplication::applicationDirPath() + "/script");

private:
    int width;
    int height;

signals:
    void script_created();
};


#endif //ADD_SCRIPT_CARD_H
