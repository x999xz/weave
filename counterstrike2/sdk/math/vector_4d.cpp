// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "vector_4d.hpp"

#include <cmath>
#include <limits>

void vectorCopy(const vector_4d& src, vector_4d& dst)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
    dst.w = src.w;
}
void vectorLerp(const vector_4d& src1, const vector_4d& src2, vec_t t, vector_4d& dest)
{
    dest.x = src1.x + (src2.x - src1.x) * t;
    dest.y = src1.y + (src2.y - src1.y) * t;
    dest.z = src1.z + (src2.z - src1.z) * t;
    dest.w = src1.w + (src2.w - src1.w) * t;
}
float vectorLength(const vector_4d& v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

vec_t Normalizevector(vector_4d& v)
{
    vec_t l = v.length();
    if(l != 0.0f) {
        v /= l;
    } else {
        v.x = v.y = v.z = v.w = 0.0f;
    }
    return l;
}

vector_4d::vector_4d(void)
{
    invalidate();
}
vector_4d::vector_4d(vec_t X, vec_t Y, vec_t Z, vec_t W)
{
    x = X;
    y = Y;
    z = Z;
    w = W;
}
vector_4d::vector_4d(vec_t* clr)
{
    x = clr[0];
    y = clr[1];
    z = clr[2];
    w = clr[3];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void vector_4d::init(vec_t ix, vec_t iy, vec_t iz, vec_t iw)
{
    x = ix; y = iy; z = iz; w = iw;
}

void vector_4d::random(vec_t minVal, vec_t maxVal)
{
    x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
void vector_4d::zero()
{
    x = y = z = w = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

vector_4d& vector_4d::operator=(const vector_4d &vOther)
{
    x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
    return *this;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
vec_t& vector_4d::operator[](int i)
{
    return ((vec_t*)this)[i];
}

vec_t vector_4d::operator[](int i) const
{
    return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// base address...
//-----------------------------------------------------------------------------
vec_t* vector_4d::base()
{
    return (vec_t*)this;
}

vec_t const* vector_4d::base() const
{
    return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// is_valid?
//-----------------------------------------------------------------------------

bool vector_4d::is_valid() const
{
    return !isinf(x) && !isinf(y) && !isinf(z) && !isinf(w);
}

//-----------------------------------------------------------------------------
// invalidate
//-----------------------------------------------------------------------------

void vector_4d::invalidate()
{
    //#ifdef _DEBUG
    //#ifdef VECTOR_PARANOIA
    x = y = z = w = std::numeric_limits<float>::infinity();
    //#endif
    //#endif
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool vector_4d::operator==(const vector_4d& src) const
{
    return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

bool vector_4d::operator!=(const vector_4d& src) const
{
    return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------
void vector_4d::copy_to_array(float* rgfl) const
{
    rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

void vector_4d::negate()
{
    x = -x; y = -y; z = -z; w = -w;
}

// Get the component of this vector parallel to some other given vector
vector_4d vector_4d::project_onto(const vector_4d& onto)
{
    return onto * (this->dot(onto) / (onto.length_sqr()));
}

// FIXME: Remove
// For backwards compatability
void vector_4d::mul_add(const vector_4d& a, const vector_4d& b, float scalar)
{
    x = a.x + b.x * scalar;
    y = a.y + b.y * scalar;
    z = a.z + b.z * scalar;
    w = a.w + b.w * scalar;
}

vector_4d vectorLerp(const vector_4d& src1, const vector_4d& src2, vec_t t)
{
    vector_4d result;
    vectorLerp(src1, src2, t, result);
    return result;
}

vec_t vector_4d::dot(const vector_4d& b) const
{
    return (x*b.x + y*b.y + z*b.z + w*b.w);
}
void vectorClear(vector_4d& a)
{
    a.x = a.y = a.z = a.w = 0.0f;
}

vec_t vector_4d::length(void) const
{
    return sqrt(x*x + y*y + z*z + w*w);
}

// check a point against a box
bool vector_4d::within_a_box(vector_4d const &boxmin, vector_4d const &boxmax)
{
    return (
        (x >= boxmin.x) && (x <= boxmax.x) &&
        (y >= boxmin.y) && (y <= boxmax.y) &&
        (z >= boxmin.z) && (z <= boxmax.z) &&
        (w >= boxmin.w) && (w <= boxmax.w)
        );
}

//-----------------------------------------------------------------------------
// Get the distance from this vector to the other one 
//-----------------------------------------------------------------------------
vec_t vector_4d::distance_to(const vector_4d &vOther) const
{
    vector_4d delta;
    delta = *this - vOther;
    return delta.length();
}

//-----------------------------------------------------------------------------
// Returns a vector with the Min or Max in X, Y, and Z.
//-----------------------------------------------------------------------------
vector_4d vector_4d::Min(const vector_4d &vOther) const
{
    return vector_4d(x < vOther.x ? x : vOther.x,
        y < vOther.y ? y : vOther.y,
        z < vOther.z ? z : vOther.z,
        w < vOther.w ? w : vOther.w);
}

vector_4d vector_4d::Max(const vector_4d &vOther) const
{
    return vector_4d(x > vOther.x ? x : vOther.x,
        y > vOther.y ? y : vOther.y,
        z > vOther.z ? z : vOther.z,
        w > vOther.w ? w : vOther.w);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

vector_4d vector_4d::operator-(void) const
{
    return vector_4d(-x, -y, -z, -w);
}

vector_4d vector_4d::operator+(const vector_4d& v) const
{
    return vector_4d(x + v.x, y + v.y, z + v.z, w + v.w);
}

vector_4d vector_4d::operator-(const vector_4d& v) const
{
    return vector_4d(x - v.x, y - v.y, z - v.z, w - v.w);
}

vector_4d vector_4d::operator*(float fl) const
{
    return vector_4d(x * fl, y * fl, z * fl, w * fl);
}

vector_4d vector_4d::operator*(const vector_4d& v) const
{
    return vector_4d(x * v.x, y * v.y, z * v.z, w * v.w);
}

vector_4d vector_4d::operator/(float fl) const
{
    return vector_4d(x / fl, y / fl, z / fl, w / fl);
}

vector_4d vector_4d::operator/(const vector_4d& v) const
{
    return vector_4d(x / v.x, y / v.y, z / v.z, w / v.w);
}

vector_4d operator*(float fl, const vector_4d& v)
{
    return v * fl;
}







































