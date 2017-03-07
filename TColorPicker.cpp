#include <QCoreApplication>
#include <QFrame>
#include <QStyleOption>
#include "TColorPicker.h"

TColorPicker::TColorPicker(QWidget* parent) :
    QPushButton( parent )
{
	Init();
}

TColorPicker::TColorPicker(const QString &text, QWidget *parent /*= Q_NULLPTR*/)
: QPushButton(text, parent)
{
	Init();
}


void TColorPicker::Init()
{
	mPopup = new TColorPickerPopup(0);
	mPopup->setObjectName("TColorPickerPopup");
	mPopup->setFrameShape(QFrame::StyledPanel);
	mPopup->setFrameShadow(QFrame::Plain);

	connect(mPopup, SIGNAL(sigSelected(QColor)),
		this, SLOT(OnPopupSelected(QColor)));

	setMaximumSize(25, 20);
	mSelectedColor = Qt::black;

	QMetaObject::connectSlotsByName(this);
}


void TColorPicker::paintEvent ( QPaintEvent* )
{
   QStyleOptionButton option;
   option.initFrom( this );

   option.features = QStyleOptionButton::HasMenu;

   QPixmap icon( 3, 3 );
   QPainter iconPainter( &icon );
   iconPainter.fillRect( 0, 0, 3, 3, mSelectedColor );

   option.text = "A";
   option.icon = icon;

   QString strStyle = QString("TColorPicker {text-align:left; font-weight:bold; font-size:15px; border-width:6px; border-style:none none solid none; border-color:%1;}")
	   .arg(mSelectedColor.name());
   setStyleSheet(strStyle);

   QPainter painter ( this );
   style()->drawControl( QStyle::CE_PushButton, &option, &painter, this );   
}

void TColorPicker::OnPopupSelected( QColor color )
{
   mSelectedColor = color;
   repaint();
}

QColor TColorPicker::GetColor(const QColor &initial /*= Qt::white*/, 	
	const QPoint &pos )
{
	mSelectedColor = initial;

	mPopup->move(pos);
	mPopup->setWindowFlags( Qt::Popup );
	mPopup->show();

	while (mPopup->isVisible() == true)
	{
		QCoreApplication::processEvents();
	}

	return mSelectedColor;
}