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

#include "steuerfenster.h"

#include <QFileDialog>
#include <QMessageBox>

#include "fragebearbeiten.h"

SteuerFenster::SteuerFenster ( QWidget* parentwidget ) : QMainWindow ( parentwidget ),
    _ungespeichert ( false )
{
    _ui.setupUi ( this );

    _ui.lvFragen->setModel ( &_fl );
    connect ( _ui.btnFrageNeu, SIGNAL ( clicked() ), this, SLOT ( neueFrage() ) );
    connect ( _ui.btnFrageEditieren, SIGNAL ( clicked() ), this, SLOT ( bearbeiteFrage() ) );
    connect ( _ui.btnFrageLoeschen, SIGNAL ( clicked() ), this, SLOT ( loescheFrage() ) );
    connect ( _ui.btnNachOben, SIGNAL ( clicked() ), this, SLOT ( schiebeFrageHoch() ) );
    connect ( _ui.btnNachUnten, SIGNAL ( clicked() ), this, SLOT ( schiebeFrageRunter() ) );
    connect ( _ui.actSpeichern, SIGNAL ( triggered() ), this, SLOT ( speichereFragen() ) );
}

SteuerFenster::~SteuerFenster( )
{

}

void SteuerFenster::closeEvent ( QCloseEvent* closeargs )
{
    if ( _ungespeichert )
    {
        const QMessageBox::StandardButton antwort = QMessageBox::question (
                    this,
                    QString::fromUtf8 ( "Ungespeicherte Fragen" ),
                    QString::fromUtf8 ( "In der Liste befinden sich ungespeicherte Fragen.\nSoll das Programm trotzdem geschlossen werden?" ),
                    QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::No
                );
        if ( antwort == QMessageBox::No )
            closeargs->ignore();
    }
}

void SteuerFenster::neueFrage()
{
    Frage neu ( QString(), QString(), QString(), QString(), QString(), QString(), Frage::Arichtig );
    if ( FrageBearbeiten::bearbeiteFrage ( neu, *this ) )
    {
        _fl.neueFrage ( std::move ( neu ) );
        _ungespeichert = true;
    }
}

void SteuerFenster::bearbeiteFrage()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    Frage& frage = _fl.holeFrage ( nummer );
    if ( FrageBearbeiten::bearbeiteFrage ( frage, *this ) )
    {
        _fl.geaendertFrage ( nummer );
        _ungespeichert = true;
    }
}

void SteuerFenster::loescheFrage()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    _fl.loescheFrage ( nummer );
    _ungespeichert = true;
}

void SteuerFenster::schiebeFrageHoch()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    if ( nummer == 0 )
        return; // Erste Frage kann nicht hochgeschoben werden
    _fl.schiebeFrageHoch ( nummer );
    _ui.lvFragen->setCurrentIndex ( _fl.index ( ( int ) nummer - 1 ) );
    _ungespeichert = true;
}

void SteuerFenster::schiebeFrageRunter()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    if ( ( int ) nummer == _fl.rowCount() - 1 )
        return; // Letzte Frage kann nicht runtergeschoben werden
    _fl.schiebeFrageRunter ( nummer );
    _ui.lvFragen->setCurrentIndex ( _fl.index ( ( int ) nummer + 1 ) );
    _ungespeichert = true;
}


void SteuerFenster::speichereFragen()
{
    const QString dateiname = QFileDialog::getSaveFileName (
                                  this,
                                  QString::fromUtf8 ( "Speicherort auswählen..." ),
                                  QString(),
                                  QString::fromUtf8 ( "XML-Dateien (*.xml)" )
                              );
    if ( dateiname == QString() )
        return;
    QFile datei ( dateiname );
    datei.open ( QFile::WriteOnly );
    if ( datei.isOpen() )
    {
        try
        {
            _fl.speichereFragen ( &datei );
            if ( datei.error() != QFile::NoError )
                QMessageBox::critical (
                    this,
                    QString::fromUtf8 ( "Fehler beim Speichern" ),
                    QString::fromUtf8 ( "Beim Schreiben der Datei ist ein Fehler aufgetreten.\n\nFehlermeldung: " )
                    + datei.errorString()
                );
            else
                _ungespeichert = false;
        }
        catch ( std::exception& ex )
        {
            QMessageBox::critical (
                this,
                QString::fromUtf8 ( "Fehler beim Speichern" ),
                QString::fromUtf8 ( "Das Speichern der Datei ist fehlgeschlagen.\n\nFehlermeldung: " )
                + QString::fromUtf8 ( ex.what() )
            );
        }
    }
    else
    {
        QMessageBox::critical (
            this,
            QString::fromUtf8 ( "Fehler beim Speichern" ),
            QString::fromUtf8 ( "Die Datei konnte nicht zum Schreiben geöffnet werden.\n\nFehlermeldung: " )
            + datei.errorString()
        );
    }
    datei.close();
}

#include "steuerfenster.moc"
