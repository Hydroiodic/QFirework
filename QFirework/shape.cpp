#include "shape.h"

namespace HI {
	void circle(state& st) {
		int angle = rand() % 360;
		st.vx = v * cos(angle / pi);
		st.vy = -v * sin(angle / pi);
	}

	void heart(state& st) {
		int angle = rand() % 360;
		double r = acos(sin(angle));

		st.vx = v * (r * cos(angle) / pi);
		st.vy = -v * (r * sin(angle) / pi + 0.5);
	}

	int cur_func = -1;
}
