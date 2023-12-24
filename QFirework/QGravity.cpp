#include "QGravity.h"

namespace HI {
	QGravity::QGravity(QObject* parent, const state& s) 
		: QObject(parent), st(s) {
		/* there's nothing to do here */
	}

	QGravity::~QGravity() {
		/* there's nothing to do here */
	}

	void QGravity::proceed(QList<HI::QGravity*>& list) {
		st.x += st.vx;
		st.y += st.vy;
		st.vy += st.gravity;
		st.left_time -= 1;
	}

	state QGravity::getState() const {
		return st;
	}
}
