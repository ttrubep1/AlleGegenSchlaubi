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

#ifndef FRAGEBEARBEITEN_H
#define FRAGEBEARBEITEN_H

#include <QDialog>

#include "frage.h"
#include "ui_fragebearbeiten.h"

class SteuerFenster; // Vorwärsdeklaration

class FrageBearbeiten : public QDialog
{
  Q_OBJECT
private:
    Frage& _frage;
    SteuerFenster& _steuerung;
    Ui::FrageBearbeiten _ui;
    FrageBearbeiten(Frage& frage, SteuerFenster& steuerung);
public:
    static bool bearbeiteFrage(Frage& frage, SteuerFenster& steuerung);
    virtual ~FrageBearbeiten();
    FrageBearbeiten ( const FrageBearbeiten& other ) = delete;
    FrageBearbeiten ( FrageBearbeiten&& other ) = delete;
    FrageBearbeiten& operator= ( const FrageBearbeiten& other ) = delete;
    FrageBearbeiten& operator= ( FrageBearbeiten&& other ) = delete;
};

#endif // FRAGEBEARBEITEN_H
