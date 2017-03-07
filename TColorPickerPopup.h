#ifndef _TCOLORPICKERPOPUP_H
#define _TCOLORPICKERPOPUP_H

#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include "TColorKeyInfo.h"

class TColorPickerPopup : public QFrame
{
   Q_OBJECT

public:
	TColorPickerPopup(QWidget* parent);

protected:
	void InitColor();

	void CreateUI();

	void PaintButton(QPainter* painter, QRectF rc, QString text, bool hover);//»æÖÆ°´Å¥

	void paintEvent(QPaintEvent* );//ÑÕÉ«¿ò	

	void mouseMoveEvent(QMouseEvent* );

	void mousePressEvent(QMouseEvent* event);

signals:
	void sigSelected(QColor color);

private:
    QColor mHoverColor;    
    QList<TColorKeyInfo> mListColorInfos;

	QStringList mListThemeColors;
	QStringList mListStandardColors;

    int mWidth;
    int mHeight;

	int mBaseTop;
};

#endif