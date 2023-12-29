#pragma once

#include "config.h"
#include "QGravity.h"

namespace HI {
	static const double pi = 3.14;
	const int shape_num = 2;

	void circle(state& st);

	void heart(state& st);

	void(* const shape_functions[shape_num])(state&) = {
		&circle,
		&heart
	};

	extern int cur_func;
}
