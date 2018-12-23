#include "vec3.h"

namespace toto { namespace maths {

	vec3::vec3(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	//operators
	vec3 operator+(vec3 left, const vec3& right) {
		return left.add(right);
	}

	vec3 operator-(vec3 left, const vec3& right) {
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, const vec3& right) {
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, const vec3& right) {
		return left.divide(right);
	}

	//operators with =
	vec3& vec3::operator+=(const vec3& other){
		*this = *this + other;
		return *this; //nebo jenom return add(other)
	}

	vec3& vec3::operator-=(const vec3& other){
		*this = *this - other;
		return *this;
	}

	vec3& vec3::operator*=(const vec3& other){
		*this = *this * other;
		return *this;
	}

	vec3& vec3::operator/=(const vec3& other){
		*this = *this / other;
		return *this;
	}

	//call
	vec3::vec3(const float& x, const float& y, const float& z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//functions
	vec3& vec3::add(const vec3& other){
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3& vec3::subtract(const vec3& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3& vec3::multiply(const vec3& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	vec3& vec3::divide(const vec3& other){
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	bool vec3::operator==(const vec3& other) {
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3& other) {
		return !(x == other.x && y == other.y && z == other.z);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector){
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

}}