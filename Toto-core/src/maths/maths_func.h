#pragma once


//#define _USE_MATH_DEFINES
//#include <math.h>

namespace toto {namespace maths {
		inline float toRadians(float degrees){
			return degrees * (/*M_PI*/3.14159265358979323846f / 180.0f);
		}
}}