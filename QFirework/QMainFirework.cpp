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

void QMainFirework::explode(QList<HI::QGravity*>& list) const {
	// basic settings here
	HI::state state_to_set;
	state_to_set.gravity = st.gravity;
	state_to_set.color = st.color;
	state_to_set.x = st.x;
	state_to_set.y = st.y;
	state_to_set.left_time = HI::sub_left_time;

	// play the sound
	explodeSound();

	// choose the no of the shape function
	int function_no;
	if (HI::cur_func >= static_cast<unsigned long long>(HI::shape_num)) {
		function_no = rand() % HI::shape_num;
	}
	else {
		function_no = HI::cur_func;
	}

	// create sub-firework and add them to the list
	for (int i = 0; i < HI::total_num; ++i) {
		HI::shape_functions[function_no](state_to_set);
		HI::QGravity* new_fire = new QSubFirework(nullptr, state_to_set);
		list.push_back(new_fire);
	}
}

void QMainFirework::explodeSound() const {
	static const int MAX_SOUNDS = 2;

	// create objects and manage the memory
	QObjectTimer* delete_timer = new QObjectTimer(nullptr, 3000);
	QSoundEffect* sound_effect = new QSoundEffect(delete_timer);

	// start to play the sound
	sound_effect->setSource(QUrl::fromLocalFile(":/QFirework/sounds/firework/" +
		QString::number(rand() % MAX_SOUNDS + 1) + ".wav"));
	sound_effect->setLoopCount(1);
	sound_effect->setVolume(1.0f);
	sound_effect->play();
}
