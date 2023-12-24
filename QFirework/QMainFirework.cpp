#include "QMainFirework.h"

QMainFirework::QMainFirework(QObject* parent) 
	: QGravity(parent, HI::state()) {
	initializeState();
}

QMainFirework::~QMainFirework() {
	/* there's nothing to do here */
}

void QMainFirework::initializeState() {
	QMainWindow* parent_window = (QMainWindow*)parent();

	st.gravity = HI::gravity;
	st.vx = 0;
	st.vy = -(HI::vy_dif * rand() / RAND_MAX + HI::vy_avg);
	st.x = rand() % parent_window->width();
	st.y = parent_window->height();

	st.left_time = (rand() % 2 ? -1 : 1) * rand() % HI::left_time_dif + HI::left_time_avg;

	st.color = HI::firework_color[rand() % HI::MAX_FIREWORK_COLOR];
}

void QMainFirework::proceed(QList<HI::QGravity*>& list) {
	HI::QGravity::proceed(list);

	// here explode
	if (st.left_time <= 0) {
		explode(list);
	}
}

void QMainFirework::explode(QList<HI::QGravity*>& list) {
	HI::state state_to_set;
	state_to_set.gravity = st.gravity;
	state_to_set.color = st.color;
	state_to_set.x = st.x;
	state_to_set.y = st.y;
	state_to_set.left_time = HI::sub_left_time;

	const double pi = 3.14;

	for (int i = 0; i < HI::total_num; ++i) {
		int angle = rand() % 360;
		state_to_set.vx = HI::v * cos(angle / pi);
		state_to_set.vy = HI::v * sin(angle / pi);
		HI::QGravity* new_fire = new QSubFirework(nullptr, state_to_set);
		list.push_back(new_fire);
	}
}