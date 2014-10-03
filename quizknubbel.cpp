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

#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QTimer>

#include "quizknubbel.h"

QuizKnubbel::QuizKnubbel ( QWidget* parentwidget )
    : QWidget ( parentwidget ),
      _text ( this ),
      _lblGruppeA ( this ),
      _lblGruppeB ( this )
{
    _text.setText ( QString::fromUtf8 ( "###TEST###" ) );
    _lblGruppeA.setText ( QString::fromUtf8 ( "A" ) );
    _lblGruppeB.setText ( QString::fromUtf8 ( "B" ) );
    _lblGruppeA.setFont ( QFont ( QString::fromUtf8 ( "sans-serif" ), schriftGroesseGruppenBuchstabe ) );
    _lblGruppeB.setFont ( QFont ( QString::fromUtf8 ( "sans-serif" ), schriftGroesseGruppenBuchstabe ) );
    _lblGruppeA.hide();
    _lblGruppeB.hide();
}

QuizKnubbel::~QuizKnubbel()
{

}

QSize QuizKnubbel::sizeHint()
{
    return QSize ( minBreite, minHoehe );
}

QSize QuizKnubbel::minimumSizeHint()
{
    return QSize ( minBreite, minHoehe );
}

void QuizKnubbel::paintEvent ( QPaintEvent* paintargs )
{
    QWidget::paintEvent ( paintargs );
    QPainter zeichner ( this );
    zeichner.setRenderHint ( QPainter::Antialiasing, true );
    zeichner.setRenderHint ( QPainter::HighQualityAntialiasing, true );
    QBrush pinsel ( zeichner.brush() );
    QPen stift ( zeichner.pen() );
    pinsel.setStyle ( Qt::SolidPattern );
    pinsel.setColor ( farbeHintergrund );
    zeichner.setBrush ( pinsel );
    //zeichner.drawRect ( 0, 0, width()-1, height()-1 );
    QPoint rahmen[] = {_polypunkt1, _polypunkt2, _polypunkt3, _polypunkt4, _polypunkt5, _polypunkt6};
    zeichner.drawConvexPolygon ( rahmen, 6 );
    if ( _gruppeAaktiv )
    {
        QPoint gruppeA[] = { _gruppeAPunktMitte, _gruppeAPunktOben, _polypunkt2, _polypunkt1, _polypunkt6, _gruppeAPunktUnten };
        zeichner.drawPolygon ( gruppeA, 6 );
    }
    if ( _gruppeBaktiv )
    {
        QPoint gruppeB[] = { _gruppeBPunktMitte, _gruppeBPunktOben, _polypunkt3, _polypunkt4, _polypunkt5, _gruppeBPunktUnten };
        zeichner.drawPolygon ( gruppeB, 6 );
    }
}

void QuizKnubbel::resizeEvent ( QResizeEvent* resizeargs )
{
    QWidget::resizeEvent ( resizeargs );
    _text.setGeometry (
        breiteGruppenBuchstabe + breiteSchraege,
        hoeheTextRand,
        width() - breiteGruppenBuchstabe - breiteSchraege,
        height() - 2*hoeheTextRand
    );
    _lblGruppeA.setGeometry (
        breiteSchraege - versatzGruppenBuchstabe,
        hoeheTextRand,
        breiteGruppenBuchstabe,
        height() - 2*hoeheTextRand
    );
    _lblGruppeB.setGeometry (
        width() - breiteSchraege - 1,
        hoeheTextRand,
        breiteGruppenBuchstabe,
        height() - 2*hoeheTextRand
    );
    _polypunkt1.setX ( breiteGruppenBuchstabe );
    _polypunkt1.setY ( ( height()-1 ) /2 );
    _polypunkt2.setX ( breiteGruppenBuchstabe + breiteSchraege );
    _polypunkt2.setY ( 0 );
    _polypunkt3.setX ( width() - breiteGruppenBuchstabe - breiteSchraege - 1 );
    _polypunkt3.setY ( 0 );
    _polypunkt4.setX ( width() - breiteGruppenBuchstabe - 1 );
    _polypunkt4.setY ( ( height()-1 ) /2 );
    _polypunkt5.setX ( width() - breiteGruppenBuchstabe - breiteSchraege - 1 );
    _polypunkt5.setY ( height() - 1 );
    _polypunkt6.setX ( breiteGruppenBuchstabe + breiteSchraege );
    _polypunkt6.setY ( height() - 1 );
    _gruppeAPunktMitte.setX ( 0 );
    _gruppeAPunktMitte.setY ( ( height()-1 ) /2 );
    _gruppeAPunktOben.setX ( breiteSchraege );
    _gruppeAPunktOben.setY ( 0 );
    _gruppeAPunktUnten.setX ( breiteSchraege );
    _gruppeAPunktUnten.setY ( height() - 1 );
    _gruppeBPunktMitte.setX ( width() - 1 );
    _gruppeBPunktMitte.setY ( ( height()-1 ) /2 );
    _gruppeBPunktOben.setX ( width() - breiteSchraege - 1 );
    _gruppeBPunktOben.setY ( 0 );
    _gruppeBPunktUnten.setX ( width() - breiteSchraege - 1 );
    _gruppeBPunktUnten.setY ( height() - 1 );
}

void QuizKnubbel::fontChange ( const QFont& fontneu )
{
    QWidget::fontChange ( fontneu );
    _text.setFont ( fontneu );
}

void QuizKnubbel::changeEvent ( QEvent* changeargs )
{
    QWidget::changeEvent ( changeargs );
}

QString QuizKnubbel::text() const
{
    return _text.text();
}

void QuizKnubbel::setText ( const QString& textneu )
{
    _text.setText ( textneu );
}

bool QuizKnubbel::gruppeAaktiv() const
{
    return _gruppeAaktiv;
}

void QuizKnubbel::setGruppeAaktiv ( const bool aktiv )
{
    _gruppeAaktiv = aktiv;
    _lblGruppeA.setVisible ( _gruppeAaktiv );
    update();
}

bool QuizKnubbel::gruppeBaktiv() const
{
    return _gruppeBaktiv;
}

void QuizKnubbel::setGruppeBaktiv ( const bool aktiv )
{
    _gruppeBaktiv = aktiv;
    _lblGruppeB.setVisible ( _gruppeBaktiv );
    update();
}

#include "quizknubbel.moc"
