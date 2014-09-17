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

#ifndef FRAGENLISTE_H
#define FRAGENLISTE_H

#include <QAbstractItemModel>

#include "frage.h"

class FragenListe : public QAbstractListModel
{
public:
    typedef std::vector<Frage> FragenVektor;
private:
    FragenVektor _fragen;
public:
    FragenListe();
    virtual ~FragenListe();
    virtual QVariant data ( const QModelIndex& queriedindex, int queriedrole ) const;
    virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
    FragenListe ( const FragenListe& other ) = delete;
    FragenListe ( FragenListe&& other ) = delete;
    FragenListe& operator= ( const FragenListe& other ) = delete;
    FragenListe& operator= ( FragenListe&& other ) = delete;
    void neueFrage ( const Frage& frage );
    void neueFrage ( Frage&& frage );
    Frage& holeFrage ( const size_t nummer );
    void geaendertFrage ( const size_t nummer );
    void loescheFrage ( const size_t nummer );
    void loescheAlles();
    void schiebeFrageHoch ( const size_t nummer );
    void schiebeFrageRunter ( const size_t nummer );
    FragenListe::FragenVektor::iterator begin();
    FragenListe::FragenVektor::iterator end();
    FragenListe::FragenVektor::const_iterator begin() const;
    FragenListe::FragenVektor::const_iterator end() const;
};

#endif // FRAGENLISTE_H
