#pragma once
#define M_PI 3.14159265358979323846f

typedef float vec_t;
// 3D vector_4d
class vector_4d //-V690
{
public:
    // Members
    vec_t x, y, z, w;

    // Construction/destruction:
    vector_4d(void);
    vector_4d(vec_t X, vec_t Y, vec_t Z, vec_t W);
    vector_4d(vec_t* clr);

    // Initialization
    void init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f, vec_t iw = 0.0f);
    // TODO (Ilya): Should there be an init that takes a single float for consistency?

    // Got any nasty NAN's?
    bool is_valid() const;
    void invalidate();

    // array access...
    vec_t operator[](int i) const;
    vec_t& operator[](int i);

    // base address...
    vec_t* base();
    vec_t const* base() const;

    // Initialization methods
    void random(vec_t minVal, vec_t maxVal);
    void zero(); ///< zero out a vector

                 // equality
    bool operator==(const vector_4d& v) const;
    bool operator!=(const vector_4d& v) const;

    // arithmetic operations
    vector_4d& operator+=(const vector_4d& v)
    {
        x += v.x; y += v.y; z += v.z; w += v.w;
        return *this;
    }

    vector_4d& operator-=(const vector_4d& v)
    {
        x -= v.x; y -= v.y; z -= v.z; w -= v.w;
        return *this;
    }

    vector_4d& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        w *= fl;
        return *this;
    }

    vector_4d& operator*=(const vector_4d& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    vector_4d& operator/=(const vector_4d& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    // this ought to be an opcode.
    vector_4d& operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        w += fl;
        return *this;
    }

    // this ought to be an opcode.
    vector_4d& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl;
        w /= fl;
        return *this;
    }
    vector_4d& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        w -= fl;
        return *this;
    }

    // negate the vector components
    void negate();

    // Get the vector's magnitude.
    vec_t length() const;

    // Get the vector's magnitude squared.
    vec_t length_sqr(void) const
    {
        return (x*x + y*y + z*z);
    }

    // return true if this vector is (0,0,0) within tolerance
    bool is_zero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance &&
            y > -tolerance && y < tolerance &&
            z > -tolerance && z < tolerance &&
            w > -tolerance && w < tolerance);
    }

    vec_t normalized_in_place();
    vector_4d normalized() const;
    bool is_length_greater_than(float val) const;
    bool is_length_less_than(float val) const;

    // check if a vector is within the box defined by two other vectors
    bool within_a_box(vector_4d const &boxmin, vector_4d const &boxmax);

    // Get the distance from this vector to the other one.
    vec_t distance_to(const vector_4d &vOther) const;

    // Get the distance from this vector to the other one squared.
    // NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
    // may be able to tidy this up after switching to VC7
    vec_t distance_to_sqr(const vector_4d &vOther) const
    {
        vector_4d delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;
        delta.w = w - vOther.w;

        return delta.length_sqr();
    }

    // Copy
    void copy_to_array(float* rgfl) const;

    // Multiply, add, and assign to this (ie: *this = a + b * scalar). This
    // is about 12% faster than the actual vector equation (because it's done per-component
    // rather than per-vector).
    void mul_add(const vector_4d& a, const vector_4d& b, float scalar);

    // dot product.
    vec_t dot(const vector_4d& vOther) const;

    // assignment
    vector_4d& operator=(const vector_4d &vOther);

    // 2d
    vec_t length_2d(void) const;
    vec_t length_2d_sqr(void) const;

    /// Get the component of this vector parallel to some other given vector
    vector_4d  project_onto(const vector_4d& onto);

    // copy constructors
    // vector_4d(const vector_4d &vOther);

    // arithmetic operations
    vector_4d operator-(void) const;

    vector_4d operator+(const vector_4d& v) const;
    vector_4d operator-(const vector_4d& v) const;
    vector_4d operator*(const vector_4d& v) const;
    vector_4d operator/(const vector_4d& v) const;
    vector_4d operator*(float fl) const;
    vector_4d operator/(float fl) const;

    // Returns a vector with the Min or Max in X, Y, and Z.
    vector_4d Min(const vector_4d &vOther) const;
    vector_4d Max(const vector_4d &vOther) const;
};