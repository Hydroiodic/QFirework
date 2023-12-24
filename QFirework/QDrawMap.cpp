#include "QDrawMap.h"

QDrawMap::QDrawMap(QObject* parent) : QObject(parent) {
	painter = new QPainter;
}

QDrawMap::~QDrawMap() {
	if (painter) delete painter;
}

QPixmap QDrawMap::paintMap(const QList<HI::QGravity*>& list, int width, int height) {
	QPixmap map(width, height);

	map.fill(HI::bg_color);

	painter->begin(&map);

	HI::QGravity* qg = nullptr;
	foreach (qg, list) {
		HI::state st = qg->getState();
		painter->setBrush(QBrush(st.color));
		painter->drawEllipse(st.x, st.y, 4, 4);
	}

	painter->end();

	return map;
}
