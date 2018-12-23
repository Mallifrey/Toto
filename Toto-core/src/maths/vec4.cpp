#include "vec4.h"

namespace toto { namespace maths {



	//operators
	vec4 operator+(vec4 left, const vec4& right) {
		return left.add(right);
	}

	vec4 operator-(vec4 left, const vec4& right) {
		return left.subtract(right);
	}

	vec4 operator*(vec4 left, const vec4& right) {
		return left.multiply(right);
	}

	vec4 operator/(vec4 left, const vec4& right) {
		return left.divide(right);
	}

	//operators with =
	vec4& vec4::operator+=(const vec4& other){
		*this = *this + other;
		return *this; //nebo jenom return add(other)
	}

	vec4& vec4::operator-=(const vec4& other){
		*this = *this - other;
		return *this;
	}

	vec4& vec4::operator*=(const vec4& other){
		*this = *this * other;
		return *this;
	}

	vec4& vec4::operator/=(const vec4& other){
		*this = *this / other;
		return *this;
	}

	//call
	vec4::vec4(const float& x, const float& y, const float& z, const float& w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//functions
	vec4& vec4::add(const vec4& other){
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vec4& vec4::subtract(const vec4& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	vec4& vec4::multiply(const vec4& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	vec4& vec4::divide(const vec4& other){
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	bool vec4::operator==(const vec4& other) {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool vec4::operator!=(const vec4& other) {
		return !(x == other.x && y == other.y && z == other.z && w == other.w);
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector){
		stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z <<", " << vector.w << ")";
		return stream;
	}

}}