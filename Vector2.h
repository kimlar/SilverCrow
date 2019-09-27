#pragma once

#include <math.h> // sqrt
#include <sstream> // std::ostream, std::istream

class Vector2
{
public:
	// Members
	float x;
	float y;

	// Constructors
	Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

	// Methods
	float LengthSq() const { return sqrt(x * x + y * y); }
	float Length() const { return sqrt(LengthSq()); }
	const Vector2& Skew() { x -= y; y += x; x -= y; return *this; }
	const Vector2& Normalize()
	{
		float len = Length();
		if (len < FLT_EPSILON)
		{
			x = y = 0;
			return *this;
		}
		else
		{
			float invLen = 1.0f / len;
			x *= invLen;
			y *= invLen;
			return *this;
		}
	}

	// Assignment operators
	Vector2& operator=(const Vector2& v) { x = v.x; y = v.y; return *this; }
	Vector2& operator=(const float& s) { x = s; y = s; return *this; }
	Vector2& operator-(void) { x = -x; y = -y; return *this; }

	// Equality operators
	bool operator==(const Vector2& v) const { return (x == v.x) && (y == v.y); }
	bool operator!=(const Vector2& v) const { return !(*this == v); }

	// Comparison operators
	bool operator<(const Vector2& v) const { return (x < v.x) || ((x == v.x) && (y < v.y)); }
	bool operator>(const Vector2& v) const { return !(*this < v) && !(*this == v); }

	// Vector2 to this operators
	Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator*=(const Vector2& v) { x *= v.x; y *= v.y; return *this; }
	Vector2& operator/=(const Vector2& v) { x /= v.x; y /= v.y; return *this; }

	// Vector2 to Vector2 operators
	const Vector2 operator+(const Vector2& v) const { Vector2 r(*this); return r += v; }
	const Vector2 operator-(const Vector2& v) const { Vector2 r(*this); return r -= v; }
	const Vector2 operator*(const Vector2& v) const { Vector2 r(*this); return r *= v; }
	const Vector2 operator/(const Vector2& v) const { Vector2 r(*this); return r /= v; }

	// Scalar to this operators
	Vector2& operator+=(float s) { x += s; y += s; return *this; }
	Vector2& operator-=(float s) { x -= s; y -= s; return *this; }
	Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
	Vector2& operator/=(float s) { x /= s; y /= s; return *this; }

	// Scalar to Vector2 operators
	const Vector2 operator+(float s) const { Vector2 r(*this); return r += s; }
	const Vector2 operator-(float s) const { Vector2 r(*this); return r -= s; }
	const Vector2 operator*(float s) const { Vector2 r(*this); return r *= s; }
	const Vector2 operator/(float s) const { Vector2 r(*this); return r /= s; }

	// /*Static*/ arithmetic
	/*static*/ const Vector2 Add(const Vector2& v1, const Vector2& v2) { return v1 + v2; }
	/*static*/ const Vector2 Sub(const Vector2& v1, const Vector2& v2) { return v1 - v2; }
	/*static*/ const Vector2 Mul(const Vector2& v1, const Vector2& v2) { return v1 * v2; }
	/*static*/ const Vector2 Div(const Vector2& v1, const Vector2& v2) { return v1 / v2; }

	// /*Static*/ methods
	/*static*/ float DistanceSq(const Vector2& v1, const Vector2& v2) { return ((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)); }
	/*static*/ float Distance(const Vector2& v1, const Vector2& v2) { return sqrt(DistanceSq(v1, v2)); }
	/*static*/ float Dot(const Vector2& v1, const Vector2& v2) { return ((v1.x * v2.x) + (v1.y * v2.y)); }
	/*static*/ const Vector2 Min(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y); }
	/*static*/ const Vector2 Max(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y); }
	/*static*/ const Vector2 Clamp(const Vector2& v, const Vector2& min, const Vector2& max) { return Min(Max(v, min), max); }
	
	// Friend operators
	friend std::ostream& operator<<(std::ostream& os, const Vector2& v) { return os << "{" << v.x << ", " << v.y << "}"; }
	friend std::istream& operator>>(std::istream& is, Vector2& v)
	{
		char tmp1 = ' ';
		char tmp2 = ' ';
		char tmp3 = ' ';
		is >> tmp1 >> v.x >> tmp2 >> v.y >> tmp3;

		if ((tmp1 != '{') || (tmp2 != ',') || (tmp3 != '}'))
			is.setstate(std::ios::failbit);

		return is;
	}
};

/*
//====================================================================
// WEBSOURCE: https://codereview.stackexchange.com/questions/11934/c-vector2-class-review?rq=1
//
void TestVector2()
{
	//using
	using std::cout;
	using std::endl;

	//locals
	Vector2 v1 = Vector2(20, 20);
	Vector2 v2 = Vector2(10, 10);
	Vector2 v3 = Vector2();

	//test
	cout << "-> Vector2 Class Testing" << endl << endl;

	//value
	cout << "-> Testing Vector2 Starting Values" << endl;
	cout << "v1 = " << v1 << endl;
	cout << "v2 = " << v2 << endl;
	cout << "v3 = " << v3 << endl;
	cout << endl;

	//vector2 arithmetic
	cout << "-> Testing Vector2 Arithmetic" << endl;
	cout << "v1 + v2 = " << v1 + v2 << endl;
	cout << "v1 - v2 = " << v1 - v2 << endl;
	cout << "v1 * v2 = " << v1 * v2 << endl;
	cout << "v1 / v2 = " << v1 / v2 << endl;
	cout << endl;

	//vector2 assingment arithmetic
	cout << "-> Testing Vector2 Arithmetic to Assingment" << endl;
	v3 += v1; cout << "v3 += v1; v3 = " << v3 << endl;
	v3 -= v2; cout << "v3 -= v2; v3 = " << v3 << endl;
	v3 *= v1; cout << "v3 *= v1; v3 = " << v3 << endl;
	v3 /= v2; cout << "v3 /= v2; v3 = " << v3 << endl;
	cout << endl;

	//vector2 assingment
	cout << "-> Testing Vector2 Assingment" << endl;
	v3 = v2; cout << "v3 = v2; v3 = " << v3 << "; v2 = " << v2 << endl;
	cout << "-(v3) = " << -v3 << endl;
	v3 = 0; cout << "v3 = 0; v3 = " << v3 << endl;
	cout << endl;

	//vector2 comparison
	cout << "-> Testing Vector2 Comparison" << endl;
	if (!(v1 == v2)) { cout << "v1 == v2 is False" << endl; }
	if (v1 != v2) { cout << "v1 != v2 is True" << endl; }
	if (!(v1 < v2)) { cout << "v1 < v2 is False" << endl; }
	if (v1 > v2) { cout << "v1 > v2 is True" << endl; }
	cout << endl;

	//scaler arithmetic
	cout << "-> Testing Vector2 Scaler Arithmetic" << endl;
	cout << "v1 + 10 = " << v1 + 10 << endl;
	cout << "v1 - 10 = " << v1 - 10 << endl;
	cout << "v2 * 10 = " << v2 * 10 << endl;
	cout << "v2 / 10 = " << v2 / 10 << endl;
	cout << endl;

	//scaler assingment arithmetic
	cout << "-> Testing Vector2 Scaler Arithmetic to Assingment" << endl;
	v3 += 20; cout << "v3 += 20; v3 = " << v3 << endl;
	v3 -= 10; cout << "v3 -= 10; v3 = " << v3 << endl;
	v3 *= 20; cout << "v3 *= 20; v3 = " << v3 << endl;
	v3 /= 10; cout << "v3 /= 10; v3 = " << v3 << endl;
	cout << endl;

	//static arithmetic
	cout << "-> Testing Vector2 Static Arithmetic" << endl;
	cout << "Vector2::Add(v1, v2) = " << Vector2::Add(v1, v2) << endl;
	cout << "Vector2::Sub(v1, v2) = " << Vector2::Sub(v1, v2) << endl;
	cout << "Vector2::Mul(v1, v2) = " << Vector2::Mul(v1, v2) << endl;
	cout << "vector2::Div(v1, v2) = " << Vector2::Div(v1, v2) << endl;
	cout << endl;

	//static member functions
	cout << "-> Testing Vector2 Static Member Functions" << endl;
	cout << "Vector2::Distance(v2, v1) = " << Vector2::Distance(v2, v1) << endl;
	cout << "Vector2::DistanceSq(v2, v1) = " << Vector2::DistanceSq(v2, v1) << endl;
	cout << "Vector2::Dot(v2, v1) = " << Vector2::Dot(v2, v1) << endl;
	cout << "Vector2::Min(v1, v2) = " << Vector2::Min(v1, v2) << endl;
	cout << "Vector2::Max(v1, v2) = " << Vector2::Max(v1, v2) << endl;
	cout << "Vector2::Clamp(Vector2(5, 30), v2, v1) = " << Vector2::Clamp(Vector2(5, 30), v2, v1) << endl;
	cout << endl;

	//member functions
	cout << "-> Testing Vector2 Member Functions" << endl;
	cout << "v1.Length() = " << v1.Length() << endl;
	cout << "v1.LengthSquared() = " << v1.LengthSq() << endl;
	cout << "v2.Skew() = " << v2.Skew() << endl;
	cout << "v2.Normalize() = " << v2.Normalize() << endl;
	cout << endl;

	//testing cpp copy
	cout << "-> Testing Vector2 Default Copy Ctor" << endl;
	Vector2 * vec = new Vector2(v2);
	cout << "v2 = " << v2 << endl;
	cout << "Vector2 * vec = new Vector2(v2);" << endl;
	cout << "v4 = " << *vec << endl;
	cout << endl;

	//free
	delete vec;
}
*/
