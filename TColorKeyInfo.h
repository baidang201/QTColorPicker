#ifndef _TCOLORKEYINFO_H
#define _TCOLORKEYINFO_H

#include <QColor>

class TColorKeyInfo
{
public:
   QColor mColor;
   QRectF mRect;

   TColorKeyInfo( QColor color, QRectF rect )
   {
      this->mColor = color;
      this->mRect = rect;
   }
};

#endif