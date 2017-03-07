#include <QRectF>
#include <QToolTip>
#include "TColorPickerPopup.h"

#define COLORBLOCKSIZE 20
#define COLS 10
#define SPACE 4
#define MARGINY 19
#define MARGINX 4

TColorPickerPopup::TColorPickerPopup(QWidget* parent) : QFrame(parent, Qt::Popup)
{
	InitColor();
	CreateUI();
}

void TColorPickerPopup::InitColor()
{
	//主题色
	QString rgThemeColors[] {
		    "#ffffff", "#000000", "#eeece1", "#1f497d", "#4f81bd", "#c0504d", "#9bbb59", "#8064a2", "#4bacc6", "#f79646",
			"#f2f2f2", "#7f7f7f", "#ddd9c3", "#c6d9f0", "#dbe5f1", "#f2dcdb", "#ebf1dd", "#e5e0ec", "#dbeef3", "#fdeada",
			"#d8d8d8", "#595959", "#c4bd97", "#8db3e2", "#b8cce4", "#e5b9b7", "#d7e3bc", "#ccc1d9", "#b7dde8", "#fbd5b5",
			"#bfbfbf", "#3f3f3f", "#938953", "#548dd4", "#95b3d7", "#d99694", "#c3d69b", "#b2a2c7", "#92cddc", "#fac08f",
			"#a5a5a5", "#262626", "#494429", "#17365d", "#366092", "#953734", "#76923c", "#5f497a", "#31859b", "#e36c09",
			"#7f7f7f", "#0c0c0c", "#1d1b10", "#0f243e", "#244061", "#632423", "#4f6128", "#3f3151", "#205867", "#974806"
	};
	//标准色
	QString rgStandardColors[] = { "#c00000", "#ff0000", "#ffc000", "#ffff00", "#92d050", "#00b050", "#00b0f0", "#0070c0", "#002060", "#7030a0" };
	
	for each(QString strColor in rgThemeColors)
	{
		mListThemeColors.append(strColor);
	}

	for each (QString strColor in rgStandardColors)
	{
		mListStandardColors.append(strColor);
	}

	int colorCount = mListThemeColors.size() + mListStandardColors.size();
	mBaseTop = ((colorCount / COLS))  * COLORBLOCKSIZE + 2 * SPACE;

	mListColorInfos.clear();
	int col, row;
	for (int i = 0; i < mListThemeColors.size(); i++)
	{
		QRectF rc;
		col = i % COLS;
		row = (int)(i / COLS);

		rc.setLeft(col * COLORBLOCKSIZE + SPACE + MARGINX);
		rc.setTop(row * COLORBLOCKSIZE + SPACE + MARGINY + 5);
		rc.setWidth(COLORBLOCKSIZE - SPACE);
		rc.setHeight(COLORBLOCKSIZE - SPACE);

		QColor c(mListThemeColors.at(i));
		mListColorInfos.append(TColorKeyInfo(c, rc));
	}//for	

	for (int i = 0; i < mListStandardColors.size(); i++)
	{
		QRectF rc;
		col = i % COLS;
		row = (int)(i / COLS);

		rc.setLeft(col * COLORBLOCKSIZE + SPACE + MARGINX);
		rc.setTop(row * COLORBLOCKSIZE + SPACE + MARGINY + mBaseTop);

		rc.setWidth(COLORBLOCKSIZE - SPACE);
		rc.setHeight(COLORBLOCKSIZE - SPACE);

		QColor c(mListStandardColors.at(i));

		//colorRects[c] = rc;
		mListColorInfos.append(TColorKeyInfo(c, rc));
	}//for

	
}

void TColorPickerPopup::CreateUI()
{
	this->setWindowFlags(Qt::Popup);
	setMouseTracking(true);
	this->setStyleSheet("QFrame{background-color: rgb(255, 255, 255);border-color: rgb(0, 0, 0);}");

	int colorCount = mListThemeColors.size() + mListStandardColors.size();

	int mWidth = COLS;
	int mHeight = (int)(colorCount / COLS) + 1;

	mWidth = mWidth * COLORBLOCKSIZE + SPACE + MARGINX + 4;
	mHeight = mHeight * COLORBLOCKSIZE + SPACE + MARGINY + 16;

	setFrameShape(QFrame::StyledPanel);
	setFrameShadow(QFrame::Plain);
	resize(mWidth, mHeight);
}

void TColorPickerPopup::PaintButton(QPainter* painter, QRectF rc, QString text, bool hover) //绘制按钮
{
	if (!hover)
	{
		painter->setPen(Qt::black);
		painter->fillRect(rc, Qt::lightGray);
	}
	else
	{
		painter->setPen(Qt::blue);
		painter->fillRect(rc, Qt::yellow);
	}

	painter->drawRect(rc);
	painter->drawText(rc, text, Qt::AlignHCenter | Qt::AlignVCenter);
}

void TColorPickerPopup::paintEvent(QPaintEvent* ) //颜色框
{
	QPainter painter(this);
	//绘制整个弹出框页面
	painter.drawRect(0, 0, width() - 1, height() - 1);

	//绘制文本标题背景
	painter.fillRect(QRectF(3, 5, width() - 8, 19), QBrush(QColor("#dde7ee")));
	painter.fillRect(QRectF(3, mBaseTop + 1, width() - 8, 19), QBrush(QColor("#dde7ee")));

	//绘制文本标题
	painter.setFont(QFont("Arial", 8, QFont::Bold));	
	QPen penText(QColor("#1e307f"));
	painter.setPen(penText);
	painter.drawText(
		            QRect(10, 5, this->width(), 19),
					tr("Theme color"),
					Qt::AlignLeft | Qt::AlignVCenter);
	painter.drawText(
					QRect(10, 1 + mBaseTop, this->width(), 19),
					tr("Standard color"),
					Qt::AlignLeft | Qt::AlignVCenter);

	//绘制色块
	for each (TColorKeyInfo colorInfo in mListColorInfos)
	{
		painter.fillRect(colorInfo.mRect, QBrush(colorInfo.mColor));
	}

	QPointF mousePos = this->mapFromGlobal(QCursor::pos());

	//hoverColor = 0;
	QString strBorderColor = "#faa843";
	//鼠标移动，绘制当前选中颜色的边框
	for (int i = 0; i < mListColorInfos.count(); i++)
	{
		if (mListColorInfos[i].mRect.contains(mousePos))
		{
			QPainter painter(this);

			mHoverColor = mListColorInfos[i].mColor;
			QRectF rc = mListColorInfos[i].mRect;

			rc.setTop(rc.top() - 2);
			rc.setLeft(rc.left() - 2);
			rc.setBottom(rc.bottom() + 2);
			rc.setRight(rc.right() + 2);

			painter.setPen(QPen(QColor(strBorderColor), 2));
			painter.drawRect(rc);

			QToolTip::showText(
				QPoint(QCursor::pos().x(), QCursor::pos().y() + 5),
				mHoverColor.name(),
				this);
		}
	}
	


}

void TColorPickerPopup::mouseMoveEvent(QMouseEvent* )
{
	this->repaint();
}

void TColorPickerPopup::mousePressEvent(QMouseEvent* event) //鼠标按下，窗体消失
{
	if (!rect().contains(event->pos()))
	{
		this->close();
	}

	for (int i = 0; i < mListColorInfos.count(); i++)
	if (mListColorInfos[i].mRect.contains(event->pos()))
	{
		mHoverColor = mListColorInfos.at(i).mColor;
		emit sigSelected(mHoverColor);
		this->close();
	}//for     

	//qApp->sendEvent( parent(), event );
}
