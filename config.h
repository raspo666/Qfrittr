#ifndef CONFIG_H
#define CONFIG_H

#include "project.h"
#include <QDialog>



namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = nullptr);
    void accept();
    ~Config();

private slots:
    void on_button_test_clicked();

    void on_buttonsave_clicked();

    void on_logcheck_toggled(bool checked);

private:
    Ui::Config *ui;
};

#endif // CONFIG_H
