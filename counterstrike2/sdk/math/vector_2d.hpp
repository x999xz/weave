#pragma once

typedef float vec_t;
// 2D vector
class vector_2d
{
public:
    // Members
    vec_t x, y;

    // Construction/destruction:
    vector_2d(void);
    vector_2d(vec_t X, vec_t Y);
    vector_2d(vec_t* clr);

    vector_2d::vector_2d(const vector_2d &vOther)
    {
        x = vOther.x; y = vOther.y;
    }

    // Initialization
    void init(vec_t ix = 0.0f, vec_t iy = 0.0f);
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
    bool operator==(const vector_2d& v) const;
    bool operator!=(const vector_2d& v) const;

    // arithmetic operations
    vector_2d& operator+=(const vector_2d& v)
    {
        x += v.x; y += v.y;
        return *this;
    }

    vector_2d& operator-=(const vector_2d& v)
    {
        x -= v.x; y -= v.y;
        return *this;
    }

    vector_2d& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        return *this;
    }

    vector_2d& operator*=(const vector_2d& v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    vector_2d& operator/=(const vector_2d& v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    // this ought to be an opcode.
    vector_2d& operator+=(float fl)
    {
        x += fl;
        y += fl;
        return *this;
    }

    // this ought to be an opcode.
    vector_2d& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        return *this;
    }
    vector_2d& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        return *this;
    }

    // negate the vector components
    void negate();

    // Get the vector's magnitude.
    vec_t length() const;

    // Get the vector's magnitude squared.
    vec_t length_sqr(void) const
    {
        return (x*x + y*y);
    }

    // return true if this vector is (0,0,0) within tolerance
    bool is_zero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance &&
            y > -tolerance && y < tolerance);
    }

    vec_t normalized_in_place();
    vector_2d normalized() const;
    bool is_length_greater_than(float val) const;
    bool is_length_less_than(float val) const;

    // check if a vector is within the box defined by two other vectors
    bool within_a_box(vector_2d const &boxmin, vector_2d const &boxmax);

    // Get the distance from this vector to the other one.
    vec_t distance_to(const vector_2d &vOther) const;

    // Get the distance from this vector to the other one squared.
    // NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
    // may be able to tidy this up after switching to VC7
    vec_t distance_to_sqr(const vector_2d &vOther) const
    {
        vector_2d delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;

        return delta.length_sqr();
    }

    // Copy
    void copy_to_array(float* rgfl) const;

    // Multiply, add, and assign to this (ie: *this = a + b * scalar). This
    // is about 12% faster than the actual vector equation (because it's done per-component
    // rather than per-vector).
    void mul_add(const vector_2d& a, const vector_2d& b, float scalar);

    // dot product.
    vec_t dot(const vector_2d& vOther) const;

    // assignment
    vector_2d& operator=(const vector_2d &vOther);

    // 2d
    vec_t length_2d(void) const;
    vec_t length_2d_sqr(void) const;
	vec_t length_drop() const;
	vector_2d normalize_drop() const 
	{
		vector_2d reses = *this;
		float l = reses.length_drop();
		if (l != 0.0f)  //-V550
			reses /= l;
		else 
			reses.x = reses.y = 0.0f;
		return reses;
	}
	vec_t dist_to_drop(const vector_2d &vOther) const
	{
		vector_2d deltar;

		deltar.x = x - vOther.x;
		deltar.y = y - vOther.y;

		return deltar.length_drop();
	}

    /// Get the component of this vector parallel to some other given vector
    vector_2d  project_onto(const vector_2d& onto);

    // copy constructors
    // vector_2d(const vector_2d &vOther);

    // arithmetic operations
    vector_2d operator-(void) const;

    vector_2d operator+(const vector_2d& v) const;
    vector_2d operator-(const vector_2d& v) const;
    vector_2d operator*(const vector_2d& v) const;
    vector_2d operator/(const vector_2d& v) const;
    vector_2d operator*(float fl) const;
    vector_2d operator/(float fl) const;

    // cross product between two vectors.
    vector_2d cross(const vector_2d &vOther) const;

    // Returns a vector with the Min or Max in X, Y, and Z.
    vector_2d Min(const vector_2d &vOther) const;
    vector_2d Max(const vector_2d &vOther) const;
};