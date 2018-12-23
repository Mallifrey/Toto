#include "vec2.h"

namespace toto { namespace maths {

	vec2::vec2(){
		x = 0.0f;
		y = 0.0f;
	}

	//operators
	vec2 operator+(vec2 left, const vec2& right) {
		return left.add(right);
	}

	vec2 operator-(vec2 left, const vec2& right) {
		return left.subtract(right);
	}

	vec2 operator*(vec2 left, const vec2& right) {
		return left.multiply(right);
	}

	vec2 operator/(vec2 left, const vec2& right) {
		return left.divide(right);
	}

	//operators with =
	vec2& vec2::operator+=(const vec2& other){
		*this = *this + other;
		return *this; //nebo jenom return add(other)
	}

	vec2& vec2::operator-=(const vec2& other){
		*this = *this - other;
		return *this;
	}

	vec2& vec2::operator*=(const vec2& other){
		*this = *this * other;
		return *this;
	}

	vec2& vec2::operator/=(const vec2& other){
		*this = *this / other;
		return *this;
	}

	//call
	vec2::vec2(const float& x, const float& y){
		this->x = x;
		this->y = y;
	}

	//functions
	vec2& vec2::add(const vec2& other){
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& other){
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& other){
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& other){
		x /= other.x;
		y /= other.y;

		return *this;
	}

	bool vec2::operator==(const vec2& other) {
		return x == other.x && y == other.y;
	}

	bool vec2::operator!=(const vec2& other) {
		return !(x == other.x && y == other.y);
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector){
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

}}