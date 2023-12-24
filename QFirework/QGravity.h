#pragma once

#include <QObject>
#include <QColor>

namespace HI {
	// define the state of an object
	struct state {
		double gravity = 1;
		double x = 0, y = 0;
		double vx = 0, vy = 0;

		int left_time = 10;

		QColor color;
	};

	// simulate an object under gravity
	class QGravity : public QObject
	{
		Q_OBJECT

	public:
		QGravity(QObject* parent, const state& s);
		~QGravity();

	protected:
		state st;
		virtual void initializeState() = 0;

	public:
		virtual void proceed(QList<HI::QGravity*>& list);

	public:
		state getState() const;
	};
}
