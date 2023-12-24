#pragma once

#include "colors.h"
#include "QGravity.h"
#include <QObject>
#include <QPainter>
#include <QPixmap>

class QDrawMap : public QObject
{
	Q_OBJECT

public:
	QDrawMap(QObject* parent = nullptr);
	~QDrawMap();

private:
	QPainter* painter = nullptr;

public:
	QPixmap paintMap(const QList<HI::QGravity*>& list);
};
