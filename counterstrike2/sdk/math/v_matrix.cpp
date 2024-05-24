// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "v_matrix.hpp"

//-----------------------------------------------------------------------------
// v_matrix inlines.
//-----------------------------------------------------------------------------
inline v_matrix::v_matrix( ) { } //-V730

inline v_matrix::v_matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33 ) {
	init(
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
	);
}


inline v_matrix::v_matrix( const matrix3x4_t& matrix3x4 ) {
	init( matrix3x4 );
}


//-----------------------------------------------------------------------------
// Creates a matrix where the X axis = forward
// the Y axis = left, and the Z axis = up
//-----------------------------------------------------------------------------
inline v_matrix::v_matrix( const vector& xAxis, const vector& yAxis, const vector& zAxis ) {
	init(
		xAxis.x, yAxis.x, zAxis.x, 0.0f,
		xAxis.y, yAxis.y, zAxis.y, 0.0f,
		xAxis.z, yAxis.z, zAxis.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}


inline void v_matrix::init(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33
) {
	m[ 0 ][ 0 ] = m00;
	m[ 0 ][ 1 ] = m01;
	m[ 0 ][ 2 ] = m02;
	m[ 0 ][ 3 ] = m03;

	m[ 1 ][ 0 ] = m10;
	m[ 1 ][ 1 ] = m11;
	m[ 1 ][ 2 ] = m12;
	m[ 1 ][ 3 ] = m13;

	m[ 2 ][ 0 ] = m20;
	m[ 2 ][ 1 ] = m21;
	m[ 2 ][ 2 ] = m22;
	m[ 2 ][ 3 ] = m23;

	m[ 3 ][ 0 ] = m30;
	m[ 3 ][ 1 ] = m31;
	m[ 3 ][ 2 ] = m32;
	m[ 3 ][ 3 ] = m33;
}


//-----------------------------------------------------------------------------
// Initialize from a 3x4
//-----------------------------------------------------------------------------
inline void v_matrix::init( const matrix3x4_t& matrix3x4 ) {
	memcpy( m, matrix3x4.base( ), sizeof( matrix3x4_t ) );

	m[ 3 ][ 0 ] = 0.0f;
	m[ 3 ][ 1 ] = 0.0f;
	m[ 3 ][ 2 ] = 0.0f;
	m[ 3 ][ 3 ] = 1.0f;
}

//-----------------------------------------------------------------------------
// vector_3d_multiply_position treats src2 as if it's a point (adds the translation)
//-----------------------------------------------------------------------------
// NJS: src2 is passed in as a full vector rather than a reference to prevent the need
// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
// reference is the same as the dst reference ).
inline void vector_3d_multiply_position( const v_matrix& src1, const vector& src2, vector& dst ) {
	dst[ 0 ] = src1[ 0 ][ 0 ] * src2.x + src1[ 0 ][ 1 ] * src2.y + src1[ 0 ][ 2 ] * src2.z + src1[ 0 ][ 3 ];
	dst[ 1 ] = src1[ 1 ][ 0 ] * src2.x + src1[ 1 ][ 1 ] * src2.y + src1[ 1 ][ 2 ] * src2.z + src1[ 1 ][ 3 ];
	dst[ 2 ] = src1[ 2 ][ 0 ] * src2.x + src1[ 2 ][ 1 ] * src2.y + src1[ 2 ][ 2 ] * src2.z + src1[ 2 ][ 3 ];
}

//-----------------------------------------------------------------------------
// Methods related to the basis vectors of the matrix
//-----------------------------------------------------------------------------

inline vector v_matrix::get_forward( ) const {
	return vector( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ] );
}

inline vector v_matrix::get_left( ) const {
	return vector( m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ] );
}

inline vector v_matrix::get_up( ) const {
	return vector( m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ] );
}

inline void v_matrix::set_forward( const vector &vForward ) {
	m[ 0 ][ 0 ] = vForward.x;
	m[ 1 ][ 0 ] = vForward.y;
	m[ 2 ][ 0 ] = vForward.z;
}

inline void v_matrix::set_left( const vector &vLeft ) {
	m[ 0 ][ 1 ] = vLeft.x;
	m[ 1 ][ 1 ] = vLeft.y;
	m[ 2 ][ 1 ] = vLeft.z;
}

inline void v_matrix::set_up( const vector &vUp ) {
	m[ 0 ][ 2 ] = vUp.x;
	m[ 1 ][ 2 ] = vUp.y;
	m[ 2 ][ 2 ] = vUp.z;
}

inline void v_matrix::get_basis_vectors( vector &vForward, vector &vLeft, vector &vUp ) const {
	vForward.init( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ] );
	vLeft.init( m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ] );
	vUp.init( m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ] );
}

inline void v_matrix::set_basis_vectors( const vector &vForward, const vector &vLeft, const vector &vUp ) {
	set_forward( vForward );
	set_left( vLeft );
	set_up( vUp );
}


//-----------------------------------------------------------------------------
// Methods related to the translation component of the matrix
//-----------------------------------------------------------------------------

inline vector v_matrix::get_translation( ) const {
	return vector( m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ] );
}

inline vector& v_matrix::get_translation( vector &vTrans ) const {
	vTrans.x = m[ 0 ][ 3 ];
	vTrans.y = m[ 1 ][ 3 ];
	vTrans.z = m[ 2 ][ 3 ];
	return vTrans;
}

inline void v_matrix::set_translation( const vector &vTrans ) {
	m[ 0 ][ 3 ] = vTrans.x;
	m[ 1 ][ 3 ] = vTrans.y;
	m[ 2 ][ 3 ] = vTrans.z;
}


//-----------------------------------------------------------------------------
// appply translation to this matrix in the input space
//-----------------------------------------------------------------------------
inline void v_matrix::pre_translate( const vector &vTrans ) {
	vector tmp;
	vector_3d_multiply_position( *this, vTrans, tmp );
	m[ 0 ][ 3 ] = tmp.x;
	m[ 1 ][ 3 ] = tmp.y;
	m[ 2 ][ 3 ] = tmp.z;
}


//-----------------------------------------------------------------------------
// appply translation to this matrix in the output space
//-----------------------------------------------------------------------------
inline void v_matrix::post_translate( const vector &vTrans ) {
	m[ 0 ][ 3 ] += vTrans.x;
	m[ 1 ][ 3 ] += vTrans.y;
	m[ 2 ][ 3 ] += vTrans.z;
}

inline const matrix3x4_t& v_matrix::as_3x4( ) const {
	return *( ( const matrix3x4_t* )this ); //-V1027
}

inline matrix3x4_t& v_matrix::as_3x4( ) {
	return *( ( matrix3x4_t* )this ); //-V1027
}

inline void v_matrix::copy_from_3x4( const matrix3x4_t &m3x4 ) {
	memcpy( m, m3x4.base( ), sizeof( matrix3x4_t ) ); //-V512
	m[ 3 ][ 0 ] = m[ 3 ][ 1 ] = m[ 3 ][ 2 ] = 0;
	m[ 3 ][ 3 ] = 1;
}

inline void v_matrix::set_3x4( matrix3x4_t& matrix3x4 ) const {
	memcpy( matrix3x4.base( ), m, sizeof( matrix3x4_t ) ); //-V512
}


//-----------------------------------------------------------------------------
// Matrix math operations
//-----------------------------------------------------------------------------
inline const v_matrix& v_matrix::operator+=( const v_matrix &other ) {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			m[ i ][ j ] += other.m[ i ][ j ];
		}
	}

	return *this;
}

inline v_matrix v_matrix::operator+( const v_matrix &other ) const {
	v_matrix ret;
	for ( int i = 0; i < 16; i++ ) {
		( ( float* )ret.m )[ i ] = ( ( float* )m )[ i ] + ( ( float* )other.m )[ i ];
	}
	return ret;
}

inline v_matrix v_matrix::operator-( const v_matrix &other ) const {
	v_matrix ret;

	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			ret.m[ i ][ j ] = m[ i ][ j ] - other.m[ i ][ j ];
		}
	}

	return ret;
}

inline v_matrix v_matrix::operator-( ) const {
	v_matrix ret;
	for ( int i = 0; i < 16; i++ ) {
		( ( float* )ret.m )[ i ] = -( ( float* )m )[ i ];
	}
	return ret;
}

//-----------------------------------------------------------------------------
// vector transformation
//-----------------------------------------------------------------------------


inline vector v_matrix::operator*( const vector &vVec ) const {
	vector vRet;
	vRet.x = m[ 0 ][ 0 ] * vVec.x + m[ 0 ][ 1 ] * vVec.y + m[ 0 ][ 2 ] * vVec.z + m[ 0 ][ 3 ];
	vRet.y = m[ 1 ][ 0 ] * vVec.x + m[ 1 ][ 1 ] * vVec.y + m[ 1 ][ 2 ] * vVec.z + m[ 1 ][ 3 ];
	vRet.z = m[ 2 ][ 0 ] * vVec.x + m[ 2 ][ 1 ] * vVec.y + m[ 2 ][ 2 ] * vVec.z + m[ 2 ][ 3 ];

	return vRet;
}

inline vector v_matrix::v_mul_4x3( const vector &vVec ) const {
	vector vResult;
	vector_3d_multiply_position( *this, vVec, vResult );
	return vResult;
}


inline vector v_matrix::v_mul_4x3_transpose( const vector &vVec ) const {
	vector tmp = vVec;
	tmp.x -= m[ 0 ][ 3 ];
	tmp.y -= m[ 1 ][ 3 ];
	tmp.z -= m[ 2 ][ 3 ];

	return vector(
		m[ 0 ][ 0 ] * tmp.x + m[ 1 ][ 0 ] * tmp.y + m[ 2 ][ 0 ] * tmp.z,
		m[ 0 ][ 1 ] * tmp.x + m[ 1 ][ 1 ] * tmp.y + m[ 2 ][ 1 ] * tmp.z,
		m[ 0 ][ 2 ] * tmp.x + m[ 1 ][ 2 ] * tmp.y + m[ 2 ][ 2 ] * tmp.z
	);
}

inline vector v_matrix::v_mul_3x3( const vector &vVec ) const {
	return vector(
		m[ 0 ][ 0 ] * vVec.x + m[ 0 ][ 1 ] * vVec.y + m[ 0 ][ 2 ] * vVec.z,
		m[ 1 ][ 0 ] * vVec.x + m[ 1 ][ 1 ] * vVec.y + m[ 1 ][ 2 ] * vVec.z,
		m[ 2 ][ 0 ] * vVec.x + m[ 2 ][ 1 ] * vVec.y + m[ 2 ][ 2 ] * vVec.z
	);
}

inline vector v_matrix::v_mul_3x3_transpose( const vector &vVec ) const {
	return vector(
		m[ 0 ][ 0 ] * vVec.x + m[ 1 ][ 0 ] * vVec.y + m[ 2 ][ 0 ] * vVec.z,
		m[ 0 ][ 1 ] * vVec.x + m[ 1 ][ 1 ] * vVec.y + m[ 2 ][ 1 ] * vVec.z,
		m[ 0 ][ 2 ] * vVec.x + m[ 1 ][ 2 ] * vVec.y + m[ 2 ][ 2 ] * vVec.z
	);
}


inline void v_matrix::v3_mul( const vector &vIn, vector &vOut ) const {
	float rw;

	rw = 1.0f / ( m[ 3 ][ 0 ] * vIn.x + m[ 3 ][ 1 ] * vIn.y + m[ 3 ][ 2 ] * vIn.z + m[ 3 ][ 3 ] );
	vOut.x = ( m[ 0 ][ 0 ] * vIn.x + m[ 0 ][ 1 ] * vIn.y + m[ 0 ][ 2 ] * vIn.z + m[ 0 ][ 3 ] ) * rw;
	vOut.y = ( m[ 1 ][ 0 ] * vIn.x + m[ 1 ][ 1 ] * vIn.y + m[ 1 ][ 2 ] * vIn.z + m[ 1 ][ 3 ] ) * rw;
	vOut.z = ( m[ 2 ][ 0 ] * vIn.x + m[ 2 ][ 1 ] * vIn.y + m[ 2 ][ 2 ] * vIn.z + m[ 2 ][ 3 ] ) * rw;
}

//-----------------------------------------------------------------------------
// Other random stuff
//-----------------------------------------------------------------------------
inline void v_matrix::identity( ) {
	m[ 0 ][ 0 ] = 1.0f; m[ 0 ][ 1 ] = 0.0f; m[ 0 ][ 2 ] = 0.0f; m[ 0 ][ 3 ] = 0.0f;
	m[ 1 ][ 0 ] = 0.0f; m[ 1 ][ 1 ] = 1.0f; m[ 1 ][ 2 ] = 0.0f; m[ 1 ][ 3 ] = 0.0f;
	m[ 2 ][ 0 ] = 0.0f; m[ 2 ][ 1 ] = 0.0f; m[ 2 ][ 2 ] = 1.0f; m[ 2 ][ 3 ] = 0.0f;
	m[ 3 ][ 0 ] = 0.0f; m[ 3 ][ 1 ] = 0.0f; m[ 3 ][ 2 ] = 0.0f; m[ 3 ][ 3 ] = 1.0f;
}


inline bool v_matrix::is_identity( ) const {
	return
		m[ 0 ][ 0 ] == 1.0f && m[ 0 ][ 1 ] == 0.0f && m[ 0 ][ 2 ] == 0.0f && m[ 0 ][ 3 ] == 0.0f &&
		m[ 1 ][ 0 ] == 0.0f && m[ 1 ][ 1 ] == 1.0f && m[ 1 ][ 2 ] == 0.0f && m[ 1 ][ 3 ] == 0.0f &&
		m[ 2 ][ 0 ] == 0.0f && m[ 2 ][ 1 ] == 0.0f && m[ 2 ][ 2 ] == 1.0f && m[ 2 ][ 3 ] == 0.0f &&
		m[ 3 ][ 0 ] == 0.0f && m[ 3 ][ 1 ] == 0.0f && m[ 3 ][ 2 ] == 0.0f && m[ 3 ][ 3 ] == 1.0f;
}

inline vector v_matrix::apply_rotation( const vector &vVec ) const {
	return v_mul_3x3( vVec );
}







































