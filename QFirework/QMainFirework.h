#pragma once

#include <QObject>
#include <QMainWindow>
#include "QGravity.h"

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
	void explode();
};
