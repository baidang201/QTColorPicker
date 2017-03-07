#ifndef _TCOLORPICKER_H
#define _TCOLORPICKER_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include <Qt>
#include "TColorPickerPopup.h"

class TColorPicker : public QPushButton
{
	Q_OBJECT
public:
	explicit TColorPicker(QWidget *parent = Q_NULLPTR);
	explicit TColorPicker(const QString &text, QWidget *parent = Q_NULLPTR);	

	QColor GetColor(
		const QColor &initial = Qt::white,		
		const QPoint &pos = QPoint(0, 0)
		);

protected:
	void Init();

	void paintEvent(QPaintEvent* event);

	void SetColor(QColor c){ mSelectedColor = c; }
	QColor GetCurColor() const{ return mSelectedColor; }

public slots:
	void OnPopupSelected(QColor color);

private:
	TColorPickerPopup *mPopup;
	QColor mSelectedColor;
};

#endif