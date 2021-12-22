/*************************************************************************
 * Copyright 2021 Ralph Spitzner (rasp@spitzner.org)
 *
 * This file is part of Qfrittr - Qt FRitzbox traffic monitot.
 *
 * Qfrittr is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qfrittr  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Qfrittr.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/



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
