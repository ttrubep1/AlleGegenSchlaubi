/*
 * AlleGegenSchlaubi - educational quiz game
 * Copyright (C) 2014  Tobias Triffterer <tobias@ep1.ruhr-uni-bochum.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef STEUERFENSTER_H
#define STEUERFENSTER_H

#include <QMainWindow>

#include "fragenliste.h"
#include "ui_steuerfenster.h"

class SteuerFenster : public QMainWindow
{
    Q_OBJECT
private:
    Ui::SteuerFenster _ui;
    FragenListe _fl;
private slots:
    void neueFrage();
    void bearbeiteFrage();
    void loescheFrage();
public:
    SteuerFenster ( QWidget* parentwidget = nullptr );
    virtual ~SteuerFenster();
    SteuerFenster ( const SteuerFenster& other ) = delete;
    SteuerFenster ( SteuerFenster&& other ) = delete;
    SteuerFenster& operator= ( const SteuerFenster& other ) = delete;
    SteuerFenster& operator= ( SteuerFenster&& other ) = delete;
};

#endif // STEUERFENSTER_H
