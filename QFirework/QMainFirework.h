#pragma once

#include "colors.h"
#include "config.h"
#include "QGravity.h"
#include "QSubFirework.h"
#include <QMainWindow>
#include <QObject>

class QMainFirework : public HI::QGravity
{
	Q_OBJECT

public:
	QMainFirework(QObject* parent);
	~QMainFirework();

protected:
	void initializeState();
	void proceed(QList<HI::QGravity*>& list);

public:
	void explode(QList<HI::QGravity*>& list);
};
