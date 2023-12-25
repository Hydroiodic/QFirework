#include "QFirework.h"

QFirework::QFirework(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	// random seed
	srand(time(NULL));

	// create timer here
	timer = new QTimer;
	connect(timer, &QTimer::timeout, this, &QFirework::proceed);
	timer->start(10);

	// create painter
	painter = new QPainter;

	// initialize two pixmaps
	initializePainting();
}

QFirework::~QFirework() {
	// delete timer
	if (timer) delete timer;

	// delete painter
	if (painter) delete painter;
}

void QFirework::paintEvent(QPaintEvent* event) {
	// begin painting
	painter->begin(this);

	// paint the background
	painter->drawPixmap(0, 0, bg_map);

	if (show_text) {
		painter->drawPixmap(0, 0, text_map);
	}

	// paint each pixmap on the main window
	double opa = 1.;
	for (QQueue<QPixmap>::iterator it = map_queue.end();
		it-- != map_queue.begin(); opa -= 1. / MAX_MAPS) {
		painter->setOpacity(opa);
		painter->drawPixmap(0, 0, *it);
	}

	// end painting
	painter->end();
}

void QFirework::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Up:
		if (add_firework_cycle > 5) {
			--add_firework_cycle;
		}
		break;

	case Qt::Key_Down:
		if (add_firework_cycle < 50) {
			++add_firework_cycle;
		}
		break;

	case Qt::Key_T:
		show_text = !show_text;
		update();
		break;

	default:
		QMainWindow::keyPressEvent(event);
	}
}

void QFirework::initializePainting() {
	bg_map = QPixmap(width(), height());
	bg_map.fill(HI::bg_color);

	text_map = QPixmap(width(), height());
	text_map.fill(Qt::transparent);

	painter->begin(&text_map);

	painter->setFont(QFont("宋体", 50, QFont::Bold));
	painter->setPen(Qt::yellow);
	painter->drawText(0, 0, width(), height(), Qt::AlignCenter | Qt::AlignHCenter,
		QString::fromLocal8Bit("新年快乐！"));

	painter->end();
}

void QFirework::cleanList() {
	// iterate all of the list and clean those with a left_time less than 0
	for (int i = 0; i < list.size(); ++i) {
		HI::state st = list[i]->getState();
		if (st.left_time <= 0) {
			delete list[i];
			list.removeAt(i--);
		}
	}
}

void QFirework::proceed() {
	HI::QGravity* firework = nullptr;

	// proceed all objects
	foreach(firework, list) {
		firework->proceed(this->list);
	}

	// create new object
	static size_t count = 50;
	if (++count >= add_firework_cycle) {
		firework = new QMainFirework(this);
		list.push_back(firework);
		count = 0;
	}

	// clean objects
	cleanList();

	// update map_queue
	requestMap();
}

void QFirework::requestMap() {
	map_queue.push_back(map_painter.paintMap(list, width(), height()));

	if (map_queue.size() > MAX_MAPS) {
		map_queue.pop_front();
	}

	update();
}

void QFirework::popAbout() const {
	QMessageBox msg(QMessageBox::Information, "About", "This program is made by Hydroiodic_Acid");
	msg.exec();
}
