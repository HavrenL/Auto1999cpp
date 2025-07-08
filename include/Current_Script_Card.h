#ifndef CURRENT_SCRIPT_CARD_H
#define CURRENT_SCRIPT_CARD_H
#include "Script_Card.h"


class Current_Script_Card : public Script_Card {
    Q_OBJECT

public:
    explicit Current_Script_Card(const QString &path, QWidget *parent = nullptr, int width = 250, int height = 200);

    ~Current_Script_Card() = default;

    void setupUI() override;

    QList<QPair<QString, QString> > read_script_info();

    void delete_script_card();

private:
    int width;
    int height;
    QString script_path;
signals:
    void script_deleted();
};


#endif //CURRENT_SCRIPT_CARD_H
