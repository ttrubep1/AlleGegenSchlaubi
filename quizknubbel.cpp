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
      _gruppeA ( this ),
      _gruppeB ( this )
{
    _text.setText ( QString::fromUtf8 ( "###TEST###" ) );
    _gruppeA.setText ( QString::fromUtf8 ( "A" ) );
    _gruppeB.setText ( QString::fromUtf8 ( "B" ) );
    _gruppeA.setFont ( QFont ( QString::fromUtf8 ( "sans-serif" ), schriftGroesseGruppenBuchstabe ) );
    _gruppeB.setFont ( QFont ( QString::fromUtf8 ( "sans-serif" ), schriftGroesseGruppenBuchstabe ) );
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
    //zeichner.drawRect ( 0, 0, width()-1, height()-1 );
    QPoint rahmen[] = {polypunkt1, polypunkt2, polypunkt3, polypunkt4, polypunkt5, polypunkt6};
    zeichner.drawConvexPolygon ( rahmen, 6 );
    zeichner.drawLine ( gruppeAPunktMitte, gruppeAPunktOben );
    zeichner.drawLine ( gruppeAPunktMitte, gruppeAPunktUnten );
    zeichner.drawLine ( gruppeAPunktOben, polypunkt2 );
    zeichner.drawLine ( gruppeAPunktUnten, polypunkt6 );
    zeichner.drawLine ( gruppeBPunktMitte, gruppeBPunktOben );
    zeichner.drawLine ( gruppeBPunktMitte, gruppeBPunktUnten );
    zeichner.drawLine ( gruppeBPunktOben, polypunkt3 );
    zeichner.drawLine ( gruppeBPunktUnten, polypunkt5 );
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
    _gruppeA.setGeometry (
        breiteSchraege - versatzGruppenBuchstabe,
        hoeheTextRand,
        breiteGruppenBuchstabe,
        height() - 2*hoeheTextRand
    );
    _gruppeB.setGeometry (
        width() - breiteSchraege - 1,
        hoeheTextRand,
        breiteGruppenBuchstabe,
        height() - 2*hoeheTextRand
    );
    polypunkt1.setX ( breiteGruppenBuchstabe );
    polypunkt1.setY ( ( height()-1 ) /2 );
    polypunkt2.setX ( breiteGruppenBuchstabe + breiteSchraege );
    polypunkt2.setY ( 0 );
    polypunkt3.setX ( width() - breiteGruppenBuchstabe - breiteSchraege - 1 );
    polypunkt3.setY ( 0 );
    polypunkt4.setX ( width() - breiteGruppenBuchstabe - 1 );
    polypunkt4.setY ( ( height()-1 ) /2 );
    polypunkt5.setX ( width() - breiteGruppenBuchstabe - breiteSchraege - 1 );
    polypunkt5.setY ( height() - 1 );
    polypunkt6.setX ( breiteGruppenBuchstabe + breiteSchraege );
    polypunkt6.setY ( height() - 1 );
    gruppeAPunktMitte.setX ( 0 );
    gruppeAPunktMitte.setY ( ( height()-1 ) /2 );
    gruppeAPunktOben.setX ( breiteSchraege );
    gruppeAPunktOben.setY ( 0 );
    gruppeAPunktUnten.setX ( breiteSchraege );
    gruppeAPunktUnten.setY ( height() - 1 );
    gruppeBPunktMitte.setX ( width() - 1 );
    gruppeBPunktMitte.setY ( ( height()-1 ) /2 );
    gruppeBPunktOben.setX ( width() - breiteSchraege - 1 );
    gruppeBPunktOben.setY ( 0 );
    gruppeBPunktUnten.setX ( width() - breiteSchraege - 1 );
    gruppeBPunktUnten.setY ( height() - 1 );
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

#include "quizknubbel.moc"
