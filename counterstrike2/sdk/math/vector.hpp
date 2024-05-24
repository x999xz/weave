#pragma once
#include <sstream>
#include <algorithm>

class matrix3x4_t;

constexpr auto RadPi = 3.14159265358979323846;
constexpr auto DegPi = 180.0;

template<typename T>
T to_radians(T degrees)
{
	return (degrees * (static_cast<T>(RadPi) / static_cast<T>(DegPi)));
}

template<typename T>
T to_degrees(T radians)
{
	return (radians * (static_cast<T>(DegPi) / static_cast<T>(RadPi)));
}

#define ZERO vector(0.0f, 0.0f, 0.0f)

class vector //-V690
{
public:
	vector()
	{
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
	}

	vector(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	vector(const float* clr)
	{
		x = clr[0];
		y = clr[1];
		z = clr[2];
	}

	~vector()
	{

	}

	void init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		x = ix;
		y = iy;
		z = iz;
	}

	void mul(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	vector clamp()
	{
		if (x < -89.0f)
			x = -89.0f;

		if (x > 89.0f)
			x = 89.0f;

		while (y < -180.0f)
			y += 360.0f;

		while (y > 180.0f)
			y -= 360.0f;

		z = 0.0f;
		return *this;
	}

	vector transform(matrix3x4_t trans);

	void clamp2()
	{
		x = std::clamp(x, -89.0f, 89.0f);
		y = std::clamp(std::remainder(y, 360.0f), -180.0f, 180.0f);
		z = std::clamp(z, -50.0f, 50.0f);
	}

	void mul_add(const vector& a, const vector& b, float scalar)
	{
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
		z = a.z + b.z * scalar;
	}

	bool is_valid() const
	{
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}

	void invalidate()
	{
		x = y = z = FLT_MAX;
	}

	float& operator[](int i) //-V302
	{
		return ((float*)this)[i]; //-V108
	}

	float operator[](int i) const  //-V302
	{
		return ((float*)this)[i]; //-V108
	}

	bool __inline is_zero()
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	void __inline zero()
	{
		x = y = z = 0.0f;
	}

	bool operator==(const vector& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z); //-V550
	}

	bool operator!=(const vector& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z); //-V550
	}

	vector& operator+=(const vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	vector& operator-=(const vector& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	vector& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;

		return *this;
	}

	vector& operator*=(const vector& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	vector& operator/=(const vector& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;
	}

	vector& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;

		return *this;
	}

	vector& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		z /= fl;

		return *this;
	}

	vector& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;

		return *this;
	}

	void normalize_in_place()
	{
		vector& v = *this;

		float iradius = 1.0f / (this->length() + FLT_EPSILON);

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;
	}

	vector normalized() const
	{
		vector res = *this;
		float l = res.length();

		if (l)  //-V550
			res /= l;
		else
			res.x = res.y = res.z = 0.0f;

		return res;
	}

	float normalize() const
	{
		vector res = *this;
		float l = res.length();

		if (l)  //-V550
			res /= l;
		else
			res.x = res.y = res.z = 0.0f;

		return l;
	}

	void normalize_no_clamp()
	{
		this->x -= floorf(this->x / 360.0f + 0.5f) * 360.0f;
		this->y -= floorf(this->y / 360.0f + 0.5f) * 360.0f;
		this->z -= floorf(this->z / 360.0f + 0.5f) * 360.0f;
	}

	float dist_to(const vector& vOther) const
	{
		vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.length();
	}

	float dist_to_sqr(const vector& vOther) const
	{
		vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.length_sqr();
	}

	float dot(const vector& vOther) const
	{
		return (x * vOther.x + y * vOther.y + z * vOther.z);
	}

	void vector_cross_product(const vector& a, const vector& b, vector& result)
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}

	vector cross(const vector& vOther)
	{
		vector res;
		vector_cross_product(*this, vOther, res);

		return res;
	}

	vector direction()
	{
		return vector(cos(y * 3.141592654f / 180.0f) * cos(x * 3.141592654f / 180.0f), sin(y * 3.141592654f / 180.0f) * cos(x * 3.141592654f / 180.0f), sin(-x * 3.141592654f / 180.0f)).normalized();
	}

	float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float length_sqr() const
	{
		return x * x + y * y + z * z;
	}

	float length_2d() const
	{
		return sqrt(x * x + y * y);
	}

	float length_2d_sqr() const
	{
		return x * x + y * y;
	}

	vector to_euler_angles(vector* pseudoup = nullptr)
	{
		auto pitch = 0.0f;
		auto yaw = 0.0f;
		auto roll = 0.0f;

		auto length = length_2d();

		if (pseudoup)
		{
			auto left = pseudoup->cross(*this);

			left.normalize();

			pitch = to_degrees(std::atan2(-this->z, length));

			if (pitch < 0.0f)
				pitch += 360.0f;

			if (length > 0.001f) {
				yaw = to_degrees(std::atan2(this->y, this->x));

				if (yaw < 0.0f)
					yaw += 360.0f;

				auto up_z = (this->x * left.y) - (this->y * left.x);

				roll = to_degrees(std::atan2(left.z, up_z));

				if (roll < 0.0f)
					roll += 360.0f;
			}
			else {
				yaw = to_degrees(std::atan2(-left.x, left.y));

				if (yaw < 0.0f)
					yaw += 360.0f;
			}
		}
		else {
			if (this->x == 0.0f && this->y == 0.0f) {
				if (this->z > 0.0f)
					pitch = 270.0f;
				else
					pitch = 90.0f;
			}
			else {
				pitch = to_degrees(std::atan2(-this->z, length));

				if (pitch < 0.0f)
					pitch += 360.0f;

				yaw = to_degrees(std::atan2(this->y, this->x));

				if (yaw < 0.0f)
					yaw += 360.0f;
			}
		}

		return { pitch, yaw, roll };
	}

	vector& operator=(const vector& vOther)
	{
		x = vOther.x;
		y = vOther.y;
		z = vOther.z;

		return *this;
	}

	bool vector::operator < (const vector& v) {
		return { this->x < v.x &&
				 this->y < v.y &&
				 this->z < v.z };
	}

	bool vector::operator > (const vector& v) {
		return { this->x > v.x &&
				 this->y > v.y &&
				 this->z > v.z };
	}

	bool vector::operator<=(const vector& v) {
		return { this->x <= v.x &&
				 this->y <= v.y &&
				 this->z <= v.z };
	}

	bool vector::operator>=(const vector& v) {
		return { this->x >= v.x &&
				 this->y >= v.y &&
				 this->z >= v.z };
	}

	vector vector::operator-(void) const
	{
		return vector(-x, -y, -z);
	}

	vector vector::operator+(const vector& v) const
	{
		return vector(x + v.x, y + v.y, z + v.z);
	}

	vector vector::operator+(float fl) const
	{
		return vector(x + fl, y + fl, z + fl);
	}

	vector vector::operator-(const vector& v) const
	{
		return vector(x - v.x, y - v.y, z - v.z);
	}

	vector vector::operator-(float fl) const
	{
		return vector(x - fl, y - fl, z - fl);
	}

	vector vector::operator*(float fl) const
	{
		return vector(x * fl, y * fl, z * fl);
	}

	vector vector::operator*(const vector& v) const
	{
		return vector(x * v.x, y * v.y, z * v.z);
	}

	vector vector::operator/(float fl) const
	{
		return vector(x / fl, y / fl, z / fl);
	}

	vector vector::operator/(const vector& v) const
	{
		return vector(x / v.x, y / v.y, z / v.z);
	}

	float x, y, z;
};

inline vector operator*(float lhs, const vector& rhs)
{
	return rhs * lhs;
}

inline vector operator/(float lhs, const vector& rhs)
{
	return rhs / lhs;
}

class __declspec(align(16)) vector_aligned : public vector //-V690
{

public:

	inline vector_aligned(void)
	{
		w = 0.0f;
	};

	inline vector_aligned(float X, float Y, float Z)
	{
		w = 0.0f;
		init(X, Y, Z);
	}

public:

	explicit vector_aligned(const vector& vOther)
	{
		w = 0.0f;
		init(vOther.x, vOther.y, vOther.z);
	}

	vector_aligned& operator=(const vector& vOther)
	{
		init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	vector_aligned& operator=(const vector_aligned& vOther)
	{
		init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};

typedef unsigned __int32 uint32;

inline uint32 const float_bits(const float& f)
{
	union Convertor_t
	{
		float f;
		uint32 ul;
	} tmp;

	tmp.f = f;
	return tmp.ul;
}

inline bool is_finite(const float& f)
{
	return ((float_bits(f) & 0x7F800000) != 0x7F800000);
}

inline void vector_multiply(const vector& a, float b, vector& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
}

inline void vector_ma(const vector& start, float scale, const vector& direction, vector& dest)
{
	dest.x = start.x + scale * direction.x;
	dest.y = start.y + scale * direction.y;
	dest.z = start.z + scale * direction.z;
}

inline void vector_add(const vector& a, const vector& b, vector& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline void vector_subtcract(const vector& a, const vector& b, vector& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}