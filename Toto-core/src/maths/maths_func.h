#pragma once

#include "vec4.h"


#define _USE_MATH_DEFINES
#include <math.h>


namespace toto {namespace maths {
		inline float toRadians(float degrees){
			return degrees * (M_PI / 180.0f);
		}

		inline int hashColor(const maths::vec4& color) {
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;
			return a << 24 | b << 16 | g << 8 | r;
		}
}}