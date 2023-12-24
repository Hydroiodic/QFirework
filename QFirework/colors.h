#pragma once

#include <QColor>

namespace HI {
	QColor bg_color(0x151FAC);

	const int MAX_FIREWORK_COLOR = 3;

	QColor firework_color[MAX_FIREWORK_COLOR] = {
		QColor(0xA1B9BC),
		QColor(0xB53DE1),
		QColor(0xF2FF35)
	};
}
