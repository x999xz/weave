// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <cmath>
#include "vector_2d.hpp"

vector_2d::vector_2d(void)
{
    x = y = 0.0f;
}

vector_2d::vector_2d(vec_t X, vec_t Y)
{
    x = X; y = Y;
}

vector_2d::vector_2d(vec_t* clr)
{
    x = clr[0]; y = clr[1];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void vector_2d::init(vec_t ix, vec_t iy)
{
    x = ix; y = iy;
}

void vector_2d::random(float minVal, float maxVal)
{
    x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

vec_t vector_2d_length_drop(const vector_2d& v)
{
	return (vec_t)sqrt(v.x*v.x + v.y*v.y);
}

vec_t vector_2d::length_drop(void) const
{
	return vector_2d_length_drop(*this);
}


void vector_2d_clear(vector_2d& a)
{
    a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

vector_2d& vector_2d::operator=(const vector_2d &vOther)
{
    x = vOther.x; y = vOther.y;
    return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

vec_t& vector_2d::operator[](int i)
{
    return ((vec_t*)this)[i];
}

vec_t vector_2d::operator[](int i) const
{
    return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// base address...
//-----------------------------------------------------------------------------

vec_t* vector_2d::base()
{
    return (vec_t*)this;
}

vec_t const* vector_2d::base() const
{
    return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// is_valid?
//-----------------------------------------------------------------------------

bool vector_2d::is_valid() const
{
    return !isinf(x) && !isinf(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool vector_2d::operator==(const vector_2d& src) const
{
    return (src.x == x) && (src.y == y);
}

bool vector_2d::operator!=(const vector_2d& src) const
{
    return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

void vector_2d_copy(const vector_2d& src, vector_2d& dst)
{
    dst.x = src.x;
    dst.y = src.y;
}

void vector_2d::copy_to_array(float* rgfl) const
{
    rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

void vector_2d::negate()
{
    x = -x; y = -y;
}

void vector_2d_add(const vector_2d& a, const vector_2d& b, vector_2d& c)
{
    c.x = a.x + b.x;
    c.y = a.y + b.y;
}

void vector_2d_subtract(const vector_2d& a, const vector_2d& b, vector_2d& c)
{
    c.x = a.x - b.x;
    c.y = a.y - b.y;
}

void vector_2d_multiply(const vector_2d& a, vec_t b, vector_2d& c)
{
    c.x = a.x * b;
    c.y = a.y * b;
}

void vector_2d_multiply(const vector_2d& a, const vector_2d& b, vector_2d& c)
{
    c.x = a.x * b.x;
    c.y = a.y * b.y;
}


void vector_2d_divide(const vector_2d& a, vec_t b, vector_2d& c)
{
    vec_t oob = 1.0f / b;
    c.x = a.x * oob;
    c.y = a.y * oob;
}

void vector_2d_divide(const vector_2d& a, const vector_2d& b, vector_2d& c)
{
    c.x = a.x / b.x;
    c.y = a.y / b.y;
}

void vector_2d_dma(const vector_2d& start, float s, const vector_2d& dir, vector_2d& result)
{
    result.x = start.x + s*dir.x;
    result.y = start.y + s*dir.y;
}

// FIXME: Remove
// For backwards compatability
void vector_2d::mul_add(const vector_2d& a, const vector_2d& b, float scalar)
{
    x = a.x + b.x * scalar;
    y = a.y + b.y * scalar;
}

void vector_2d_lerp(const vector_2d& src1, const vector_2d& src2, vec_t t, vector_2d& dest)
{
    dest[0] = src1[0] + (src2[0] - src1[0]) * t;
    dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
vec_t dot_product_2d(const vector_2d& a, const vector_2d& b)
{
    return(a.x*b.x + a.y*b.y);
}

// for backwards compatability
vec_t vector_2d::dot(const vector_2d& vOther) const
{
    return dot_product_2d(*this, vOther);
}

vec_t vector_2d_normalize(vector_2d& v)
{
    vec_t l = v.length();
    if(l != 0.0f) {
        v /= l;
    } else {
        v.x = v.y = 0.0f;
    }
    return l;
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
vec_t vector_2d_length(const vector_2d& v) //-V524
{
    return (vec_t)sqrt(v.x*v.x + v.y*v.y);
}

vec_t vector_2d::normalized_in_place()
{
    return vector_2d_normalize(*this);
}

bool vector_2d::is_length_greater_than(float val) const
{
    return length_sqr() > val*val;
}

bool vector_2d::is_length_less_than(float val) const
{
    return length_sqr() < val*val;
}

vec_t vector_2d::length(void) const
{
    return vector_2d_length(*this);
}


void vector_2d_min(const vector_2d &a, const vector_2d &b, vector_2d &result)
{
    result.x = (a.x < b.x) ? a.x : b.x;
    result.y = (a.y < b.y) ? a.y : b.y;
}


void vector_2d_max(const vector_2d &a, const vector_2d &b, vector_2d &result)
{
    result.x = (a.x > b.x) ? a.x : b.x;
    result.y = (a.y > b.y) ? a.y : b.y;
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
void compute_closest_point_2d(const vector_2d& vecStart, float flMaxDist, const vector_2d& vecTarget, vector_2d *pResult)
{
    vector_2d vecDelta;
    vector_2d_subtract(vecTarget, vecStart, vecDelta);
    float flDistSqr = vecDelta.length_sqr();
    if(flDistSqr <= flMaxDist * flMaxDist) {
        *pResult = vecTarget;
    } else {
        vecDelta /= sqrt(flDistSqr);
        vector_2d_dma(vecStart, flMaxDist, vecDelta, *pResult);
    }
}

//-----------------------------------------------------------------------------
// Returns a vector_2d with the Min or Max in X, Y, and Z.
//-----------------------------------------------------------------------------

vector_2d vector_2d::Min(const vector_2d &vOther) const
{
    return vector_2d(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

vector_2d vector_2d::Max(const vector_2d &vOther) const
{
    return vector_2d(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

vector_2d vector_2d::operator-(void) const
{
    return vector_2d(-x, -y);
}

vector_2d vector_2d::operator+(const vector_2d& v) const
{
    vector_2d res;
    vector_2d_add(*this, v, res);
    return res;
}

vector_2d vector_2d::operator-(const vector_2d& v) const
{
    vector_2d res;
    vector_2d_subtract(*this, v, res);
    return res;
}

vector_2d vector_2d::operator*(float fl) const
{
    vector_2d res;
    vector_2d_multiply(*this, fl, res);
    return res;
}

vector_2d vector_2d::operator*(const vector_2d& v) const
{
    vector_2d res;
    vector_2d_multiply(*this, v, res);
    return res;
}

vector_2d vector_2d::operator/(float fl) const
{
    vector_2d res;
    vector_2d_divide(*this, fl, res);
    return res;
}

vector_2d vector_2d::operator/(const vector_2d& v) const
{
    vector_2d res;
    vector_2d_divide(*this, v, res);
    return res;
}

vector_2d operator*(float fl, const vector_2d& v)
{
    return v * fl;
}







































