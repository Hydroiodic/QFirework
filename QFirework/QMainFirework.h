#pragma once

#include "colors.h"
#include "config.h"
#include "QGravity.h"
#include "QObjectTimer.h"
#include "QSubFirework.h"
#include <QMainWindow>
#include <QObject>
#include <QSoundEffect>

class QMainFirework : public HI::QGravity
{
	Q_OBJECT

public:
	QMainFirework(QObject* parent);
	~QMainFirework();

protected:
	void initializeState();
	void proceed(QList<HI::QGravity*>& list);

private:
	void explode(QList<HI::QGravity*>& list) const;
	void explodeSound() const;
};
