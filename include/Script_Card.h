#ifndef SCRIPT_CARD_H
#define SCRIPT_CARD_H
#include <QWidget>


class Script_Card : public QWidget {
    Q_OBJECT

public:
    explicit Script_Card(QWidget *parent = nullptr): QWidget(parent) {
    };

    ~Script_Card() = default;

    virtual void setupUI() =0;
};


#endif //SCRIPT_CARD_H
