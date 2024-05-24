#pragma once

#include <limits>
#include <DirectXMath.h>
#include "../sdk.hpp"

class quaternion
{
public:
	float x, y, z, w;
};

class cplane_t {
public:
	vector normal;
	float dist;
	uint8_t type;   // for fast side tests
	uint8_t signbits;  // signx + (signy<<1) + (signz<<1)
	uint8_t pad[2];

};

class matrix3x4_t {

public:

	matrix3x4_t() { } //-V730
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23) {
		m_flMatVal[0][0] = m00; m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10; m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20; m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void init(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin) {
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin) {
		init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void set_origin(vector const& p) {
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	inline void invalidate(void) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				m_flMatVal[i][j] = std::numeric_limits<float>::infinity();;
			}
		}
	}

	template<typename T>
	T to_radians(T degrees) {
		return (degrees * (static_cast<T>(RadPi) / static_cast<T>(DegPi)));
	}


	void angle_matrix(const vector& angles)
	{
		float sr, sp, sy, cr, cp, cy;
		DirectX::XMScalarSinCos(&sy, &cy, to_radians(angles[1]));
		DirectX::XMScalarSinCos(&sp, &cp, to_radians(angles[0]));
		DirectX::XMScalarSinCos(&sr, &cr, to_radians(angles[2]));

		m_flMatVal[0][0] = cp * cy;
		m_flMatVal[1][0] = cp * sy;
		m_flMatVal[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;
		m_flMatVal[0][1] = sp * srcy - crsy;
		m_flMatVal[1][1] = sp * srsy + crcy;
		m_flMatVal[2][1] = sr * cp;

		m_flMatVal[0][2] = (sp * crcy + srsy);
		m_flMatVal[1][2] = (sp * crsy - srcy);
		m_flMatVal[2][2] = cr * cp;

		m_flMatVal[0][3] = 0.0f;
		m_flMatVal[1][3] = 0.0f;
		m_flMatVal[2][3] = 0.0f;
	}

	void matrix_set_column(const vector& in, int column)
	{
		m_flMatVal[0][column] = in.x;
		m_flMatVal[1][column] = in.y;
		m_flMatVal[2][column] = in.z;
	}

	void angle_matrix(const vector& angles, const vector& position)
	{
		angle_matrix(angles);
		matrix_set_column(position, 3);
	}

	void quaternion_matrix(const quaternion& q)
	{
		m_flMatVal[0][0] = 1.0 - 2.0 * q.y * q.y - 2.0 * q.z * q.z;
		m_flMatVal[1][0] = 2.0 * q.x * q.y + 2.0 * q.w * q.z;
		m_flMatVal[2][0] = 2.0 * q.x * q.z - 2.0 * q.w * q.y;

		m_flMatVal[0][1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
		m_flMatVal[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		m_flMatVal[2][1] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;

		m_flMatVal[0][2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
		m_flMatVal[1][2] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		m_flMatVal[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;

		m_flMatVal[0][3] = 0.0f;
		m_flMatVal[1][3] = 0.0f;
		m_flMatVal[2][3] = 0.0f;
	}

	void quaternion_matrix(const quaternion& q, const vector& pos)
	{
		quaternion_matrix(q);

		m_flMatVal[0][3] = pos.x;
		m_flMatVal[1][3] = pos.y;
		m_flMatVal[2][3] = pos.z;
	}

	matrix3x4_t matrix3x4_t::concat_transforms(matrix3x4_t in) const
	{
		matrix3x4_t out;

		out[0][0] = m_flMatVal[0][0] * in[0][0] + m_flMatVal[0][1] * in[1][0] + m_flMatVal[0][2] * in[2][0];
		out[0][1] = m_flMatVal[0][0] * in[0][1] + m_flMatVal[0][1] * in[1][1] + m_flMatVal[0][2] * in[2][1];
		out[0][2] = m_flMatVal[0][0] * in[0][2] + m_flMatVal[0][1] * in[1][2] + m_flMatVal[0][2] * in[2][2];
		out[0][3] = m_flMatVal[0][0] * in[0][3] + m_flMatVal[0][1] * in[1][3] + m_flMatVal[0][2] * in[2][3] + m_flMatVal[0][3];
		out[1][0] = m_flMatVal[1][0] * in[0][0] + m_flMatVal[1][1] * in[1][0] + m_flMatVal[1][2] * in[2][0];
		out[1][1] = m_flMatVal[1][0] * in[0][1] + m_flMatVal[1][1] * in[1][1] + m_flMatVal[1][2] * in[2][1];
		out[1][2] = m_flMatVal[1][0] * in[0][2] + m_flMatVal[1][1] * in[1][2] + m_flMatVal[1][2] * in[2][2];
		out[1][3] = m_flMatVal[1][0] * in[0][3] + m_flMatVal[1][1] * in[1][3] + m_flMatVal[1][2] * in[2][3] + m_flMatVal[1][3];
		out[2][0] = m_flMatVal[2][0] * in[0][0] + m_flMatVal[2][1] * in[1][0] + m_flMatVal[2][2] * in[2][0];
		out[2][1] = m_flMatVal[2][0] * in[0][1] + m_flMatVal[2][1] * in[1][1] + m_flMatVal[2][2] * in[2][1];
		out[2][2] = m_flMatVal[2][0] * in[0][2] + m_flMatVal[2][1] * in[1][2] + m_flMatVal[2][2] * in[2][2];
		out[2][3] = m_flMatVal[2][0] * in[0][3] + m_flMatVal[2][1] * in[1][3] + m_flMatVal[2][2] * in[2][3] + m_flMatVal[2][3];

		return out;
	}

	vector get_x_axis()  const { return at(0); }
	vector get_y_axis()  const { return at(1); }
	vector get_z_axis()  const { return at(2); }
	vector get_origin() const { return at(3); }

	vector at(int i) const { return vector{ m_flMatVal[0][i], m_flMatVal[1][i], m_flMatVal[2][i] }; }

	float* operator[](int i) { return m_flMatVal[i]; }
	const float* operator[](int i) const { return m_flMatVal[i]; }
	float* base() { return &m_flMatVal[0][0]; }
	const float* base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4]{};
};

class v_matrix //-V690
{
public:

	v_matrix();
	v_matrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	v_matrix(const vector& forward, const vector& left, const vector& up);

	// Construct from a 3x4 matrix
	v_matrix(const matrix3x4_t& matrix3x4);

	// Set the values in the matrix.
	void  init(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);


	// Initialize from a 3x4
	void  init(const matrix3x4_t& matrix3x4);

	// array access
	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float* base() {
		return &m[0][0];
	}

	inline const float* base() const {
		return &m[0][0];
	}

	void  set_left(const vector& vLeft);
	void  set_up(const vector& vUp);
	void  set_forward(const vector& vForward);

	void  get_basis_vectors(vector& vForward, vector& vLeft, vector& vUp) const;
	void  set_basis_vectors(const vector& vForward, const vector& vLeft, const vector& vUp);

	// Get/Set the translation.
	vector& get_translation(vector& vTrans) const;
	void  set_translation(const vector& vTrans);

	void  pre_translate(const vector& vTrans);
	void  post_translate(const vector& vTrans);

	matrix3x4_t& as_3x4();
	const matrix3x4_t& as_3x4() const;
	void  copy_from_3x4(const matrix3x4_t& m3x4);
	void  set_3x4(matrix3x4_t& matrix3x4) const;

	bool  operator==(const v_matrix& src) const;
	bool  operator!=(const v_matrix& src) const { return !(*this == src); }

	// Access the basis vectors.
	vector  get_left() const;
	vector  get_up() const;
	vector  get_forward() const;
	vector  get_translation() const;


	// Matrix->vector operations.
public:
	// Multiply by a 3D vector (same as operator*).
	void  v3_mul(const vector& vIn, vector& vOut) const;

	// Multiply by a 4D vector.
	//void  V4Mul( const vector4D &vIn, vector4D &vOut ) const;

	// Applies the rotation (ignores translation in the matrix). (This just calls v_mul_3x3).
	vector  apply_rotation(const vector& vVec) const;

	// Multiply by a vector (divides by w, assumes input w is 1).
	vector  operator*(const vector& vVec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	vector  v_mul_3x3(const vector& vVec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	vector  v_mul_3x3_transpose(const vector& vVec) const;

	// Multiply by the upper 3 rows.
	vector  v_mul_4x3(const vector& vVec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	vector  v_mul_4x3_transpose(const vector& vVec) const;


	// Matrix->plane operations.
	//public:
	// Transform the plane. The matrix can only contain translation and rotation.
	//void  TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

	// Just calls TransformPlane and returns the result.
	//VPlane  operator*(const VPlane &thePlane) const;

	// Matrix->matrix operations.
public:

	v_matrix& operator=(const v_matrix& mOther);

	// Add two matrices.
	const v_matrix& operator+=(const v_matrix& other);

	// Add/Subtract two matrices.
	v_matrix  operator+(const v_matrix& other) const;
	v_matrix  operator-(const v_matrix& other) const;

	// Negation.
	v_matrix  operator-() const;

	// Return inverse matrix. Be careful because the results are undefined 
	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
	v_matrix  operator~() const;

	// Matrix operations.
public:
	// Set to identity.
	void  identity();
	bool  is_identity() const;
public:
	// The matrix.
	float  m[4][4]{};
};

inline void matrix_get_column(const matrix3x4_t& src, int nCol, vector& pColumn) {
	pColumn.x = src[0][nCol];
	pColumn.y = src[1][nCol];
	pColumn.z = src[2][nCol];
}

inline void matrix_position(const matrix3x4_t& matrix, vector& position) {
	matrix_get_column(matrix, 3, position);
}