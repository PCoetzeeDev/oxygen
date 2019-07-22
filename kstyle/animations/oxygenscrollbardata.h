#ifndef oxygenscrollbar_data_h
#define oxygenscrollbar_data_h

//////////////////////////////////////////////////////////////////////////////
// oxygenscrollbardata.h
// data container for QScrollBar animations
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "oxygenwidgetstatedata.h"

#include <QStyle>

namespace Oxygen
{

    //* scrollbar data
    class ScrollBarData: public WidgetStateData
    {

        Q_OBJECT
        Q_PROPERTY( qreal addLineOpacity READ addLineOpacity WRITE setAddLineOpacity )
        Q_PROPERTY( qreal subLineOpacity READ subLineOpacity WRITE setSubLineOpacity )

        public:

        //* constructor
        ScrollBarData( QObject* parent, QWidget* target, int );

        //* event filter
        bool eventFilter( QObject*, QEvent* ) override;

        using WidgetStateData::animation;
        using WidgetStateData::opacity;

        //* return animation for a given subcontrol
        const Animation::Pointer& animation( QStyle::SubControl ) const;

        //* return default opacity for a given subcontrol
        qreal opacity( QStyle::SubControl ) const;

        //* return default opacity for a given subcontrol
        bool isHovered( QStyle::SubControl control ) const
        {
            switch( control )
            {
                case QStyle::SC_ScrollBarAddLine: return addLineArrowHovered();
                case QStyle::SC_ScrollBarSubLine: return subLineArrowHovered();
                default: return false;
            }


        }

        //* subControlRect
        QRect subControlRect( QStyle::SubControl control ) const
        {
            switch( control )
            {
                case QStyle::SC_ScrollBarAddLine: return _addLineData._rect;
                case QStyle::SC_ScrollBarSubLine: return _subLineData._rect;
                default: return QRect();
            }
        }


        //* subcontrol rect
        void setSubControlRect( QStyle::SubControl control, const QRect& rect )
        {
            switch( control )
            {
                case QStyle::SC_ScrollBarAddLine:
                _addLineData._rect = rect;
                break;

                case QStyle::SC_ScrollBarSubLine:
                _subLineData._rect = rect;
                break;

                default: break;
            }
        }

        //* duration
        void setDuration( int duration ) override
        {
            WidgetStateData::setDuration( duration );
            addLineAnimation().data()->setDuration( duration );
            subLineAnimation().data()->setDuration( duration );
        }

        //* addLine opacity
        void setAddLineOpacity( qreal value )
        {
            value = digitize( value );
            if( _addLineData._opacity == value ) return;
            _addLineData._opacity = value;
            setDirty();
        }

        //* addLine opacity
        qreal addLineOpacity( void ) const
        { return _addLineData._opacity; }

        //* subLine opacity
        void setSubLineOpacity( qreal value )
        {
            value = digitize( value );
            if( _subLineData._opacity == value ) return;
            _subLineData._opacity = value;
            setDirty();
        }

        //* subLine opacity
        qreal subLineOpacity( void ) const
        { return _subLineData._opacity; }

        //* mouse position
        QPoint position( void ) const
        { return _position; }

        private Q_SLOTS:

        //* clear addLineRect
        void clearAddLineRect( void )
        {
            if( addLineAnimation().data()->direction() == Animation::Backward )
            { _addLineData._rect = QRect(); }
        }

        //* clear subLineRect
        void clearSubLineRect( void )
        {
            if( subLineAnimation().data()->direction() == Animation::Backward )
            { _subLineData._rect = QRect(); }
        }

        private:

        //* hoverMoveEvent
        void hoverMoveEvent( QObject*, QEvent* );

        //* hoverMoveEvent
        void hoverLeaveEvent( QObject*, QEvent* );

        //*@name hover flags
        //@{

        bool addLineArrowHovered( void ) const
        { return _addLineData._hovered; }

        void setAddLineArrowHovered( bool value )
        { _addLineData._hovered = value; }

        bool subLineArrowHovered( void ) const
        { return _subLineData._hovered; }

        void setSubLineArrowHovered( bool value )
        { _subLineData._hovered = value; }

        //@}

        //* update add line arrow
        void updateAddLineArrow( QStyle::SubControl );

        //* update sub line arrow
        void updateSubLineArrow( QStyle::SubControl );

        //*@name timelines
        //@{

        const Animation::Pointer& addLineAnimation( void ) const
        { return _addLineData._animation; }

        const Animation::Pointer& subLineAnimation( void ) const
        { return _subLineData._animation; }

        //* stores arrow data
        class Data
        {

          public:

          //* constructor
          Data( void ):
            _hovered( false ),
            _opacity( AnimationData::OpacityInvalid )
          {}

          //* true if hovered
          bool _hovered;

          //* animation
          Animation::Pointer _animation;

          //* opacity
          qreal _opacity;

          //* rect
          QRect _rect;

        };


        //* add line data (down arrow)
        Data _addLineData;

        //* subtract line data (up arrow)
        Data _subLineData;

        //* mouse position
        QPoint _position;

    };

}

#endif
