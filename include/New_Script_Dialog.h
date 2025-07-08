//
// Created by 86133 on 25-6-1.
//

#ifndef NEWSCRIPTDIALOG_H
#define NEWSCRIPTDIALOG_H
#include <QDialog>
#include <QLineEdit>


class New_Script_Dialog : public QDialog {
    Q_OBJECT

public:
    explicit New_Script_Dialog(QWidget *parent = nullptr);

    ~New_Script_Dialog() = default;

    void setupUI();

    void new_script_json();

    QLineEdit *name_edit;
    QLineEdit *author_edit;
    QLineEdit *description_edit;

signals:
    void script_created();
};


#endif //NEWSCRIPTDIALOG_H
