#pragma once

#include "colors.h"
#include "QGravity.h"
#include <QObject>

class QSubFirework : public HI::QGravity
{
	Q_OBJECT

public:
	QSubFirework(QObject* parent, const HI::state& s);
	~QSubFirework();

protected:
	void initializeState();
};
