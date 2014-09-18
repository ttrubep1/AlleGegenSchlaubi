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

#include "fragebearbeiten.h"

SteuerFenster::SteuerFenster ( QWidget* parentwidget ) : QMainWindow ( parentwidget )
{
    _ui.setupUi ( this );

    _ui.lvFragen->setModel ( &_fl );
    connect ( _ui.btnFrageNeu, SIGNAL ( clicked() ), this, SLOT ( neueFrage() ) );
    connect ( _ui.btnFrageEditieren, SIGNAL ( clicked() ), this, SLOT ( bearbeiteFrage() ) );
    connect ( _ui.btnFrageLoeschen, SIGNAL ( clicked() ), this, SLOT ( loescheFrage() ) );
    connect ( _ui.btnNachOben, SIGNAL ( clicked() ), this, SLOT ( schiebeFrageHoch() ) );
    connect ( _ui.btnNachUnten, SIGNAL ( clicked() ), this, SLOT ( schiebeFrageRunter() ) );
}

SteuerFenster::~SteuerFenster( )
{

}

void SteuerFenster::neueFrage()
{
    Frage neu ( QString(), QString(), QString(), QString(), QString(), QString(), Frage::Arichtig );
    if ( FrageBearbeiten::bearbeiteFrage ( neu, *this ) )
        _fl.neueFrage ( std::move ( neu ) );
}

void SteuerFenster::bearbeiteFrage()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    Frage& frage = _fl.holeFrage ( nummer );
    if ( FrageBearbeiten::bearbeiteFrage ( frage, *this ) )
        _fl.geaendertFrage ( nummer );
}

void SteuerFenster::loescheFrage()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    _fl.loescheFrage ( nummer );
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
}

void SteuerFenster::schiebeFrageRunter()
{
    if ( !_ui.lvFragen->currentIndex().isValid() )
        return;
    const size_t nummer = _fl.data ( _ui.lvFragen->currentIndex(), Qt::UserRole ).toUInt();
    if ( (int) nummer == _fl.rowCount() - 1 )
        return; // Letzte Frage kann nicht runtergeschoben werden
    _fl.schiebeFrageRunter ( nummer );
    _ui.lvFragen->setCurrentIndex ( _fl.index ( ( int ) nummer + 1 ) );
}

#include "steuerfenster.moc"
