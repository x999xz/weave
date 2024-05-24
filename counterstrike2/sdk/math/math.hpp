#pragma once
#include "../../sdk/sdk.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include <DirectXMath.h>
#include <minmax.h>
#include "v_matrix.hpp"

#define M_RADPI 57.295779513082f
#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)
#define M_PI 3.14159265358979323846
#define PI_F	((float)(M_PI)) 

#define deg_to_rad(x)  ((float)(x) * (float)(M_PI / 180.f))
#define rad_to_deg(x)  ((float)(x) * (float)(180.f / M_PI))

#define TICK_INTERVAL			(Interfaces::globals->interval_per_ticks)
#define TIME_TO_TICKS( dt )		( (int)( 0.5 + (float)(dt) / Interfaces::globals->interval_per_ticks ) )
#define TICKS_TO_TIME( t )		( Interfaces::globals->interval_per_ticks *( t ) )

namespace math
{
	inline vector normalize(vector angs)
	{
		while (angs.y < -180.0f)
			angs.y += 360.0f;
		while (angs.y > 180.0f)
			angs.y -= 360.0f;
		if (angs.x > 89.0f)
			angs.x = 89.0f;
		if (angs.x < -89.0f)
			angs.x = -89.0f;
		return angs;
	}

	inline float normalize_yaw(float yaw) {
		while (yaw < -180.0f)
			yaw += 360.0f;
		while (yaw > 180.0f)
			yaw -= 360.0f;

		return yaw;
	}

	inline float fast_sqrt(float x)
	{
		unsigned int i = *(unsigned int*)&x;

		i += 127 << 23;
		// approximation of square root
		i >>= 1;
		return *(float*)&i;
	}
	inline float distance_point_to_line(vector Point, vector LineOrigin, vector Dir)
	{
		auto PointDir = Point - LineOrigin;

		auto TempOffset = PointDir.dot(Dir) / (Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z);
		if (TempOffset < 0.000001f)
			return FLT_MAX;

		auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

		return (Point - PerpendicularPoint).length();
	}
	inline float grd_to_bog(float GRD) {
		return (M_PI / 180) * GRD;
	}

	inline float get_pi()
	{
		return 3.14159265358f;
	}

 	inline vector_4d angle_quaternion(const vector& angles) {
        float sin_yaw = std::sin(angles.y);
        float cos_yaw = std::cos(angles.y);
        float sin_roll = std::sin(angles.z);
        float cos_roll = std::cos(angles.z);
        float sin_pitch = std::sin(angles.x);
        float cos_pitch = std::cos(angles.x);
    
        float x = sin_yaw * (cos_roll * cos_pitch) - cos_yaw * (sin_roll * sin_pitch);
        float y = sin_yaw * (cos_pitch * sin_roll) + cos_yaw * (cos_roll * sin_pitch);
        float z = cos_yaw * (cos_roll * sin_pitch) + sin_yaw * (cos_pitch * sin_roll);
        float w = cos_yaw * (cos_roll * cos_pitch) - sin_yaw * (sin_roll * sin_pitch);
    
        return vector_4d(x, y, z, w);
    }

	inline void sin_cos(float rad, float* sine, float* cosine) {
		*sine = std::sinf(rad);
		*cosine = std::cosf(rad);
	}

	inline float rad2deg(float rad) {
		float result = rad * (180.0f / get_pi());
		return result;
	}

	inline float deg2rad(float deg) {
		float result = deg * (get_pi() / 180.0f);
		return result;
	}

	inline void correct_move(vector old_angle, c_user_cmd_base* cmd)
	{
		
		auto move_2d = vector_2d(cmd->forwardmove, cmd->sidemove);

		if (const auto speed_2d = move_2d.length()) {
			auto delta = cmd->view->angles.y - old_angle.y;

			vector_2d v1;

			math::sin_cos(
				math::deg2rad(
					remainderf(math::rad2deg(std::atan2(move_2d.y / speed_2d, move_2d.x / speed_2d)) + delta, 360.f)
				), &v1.x, &v1.y
			);

			const auto cos_x = std::cos(
				math::deg2rad(remainderf(math::rad2deg(std::atan2(0.f, speed_2d)), 360.f))
			);

			move_2d.x = cos_x * v1.y * speed_2d;
			move_2d.y = cos_x * v1.x * speed_2d;

			//if (globals::m_local->get_move_type() == MOVE_TYPE_LADDER) {
			//	if (old_angle.x < 45.f
			//		&& std::fabsf(delta) <= 65.f
			//		&& globals::m_cur_cmd->m_view_angles.x >= 45.f) {
			//		move_2d.x *= -1.f;
			//	}
			//}
			if (std::fabsf(cmd->view->angles.x) > 90.f) {
				move_2d.x *= -1.f;
			}
		}

		cmd->forwardmove = std::clamp(move_2d.y, -1.f, 1.f);
		cmd->sidemove = std::clamp(move_2d.x, -1.f, 1.f);
	}

	inline void angle_vectors(const vector& angles, vector* forward, vector* right, vector* up) {
		float sp, sy, sr, cp, cy, cr;

		sin_cos(angles.x * 0.017453292f, &sp, &cp);
		sin_cos(angles.y * 0.017453292f, &sy, &cy);
		sin_cos(angles.z * 0.017453292f, &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = sr * sp * cy - cr * sy;
			right->y = cr * cy + sr * sp * sy;
			right->z = sr * cp;
		}

		if (up)
		{
			up->x = sr * sy + cr * sp * cy;
			up->y = cr * sp * sy - sr * cy;
			up->z = cr * cp;
		}
	}

	inline void vector_angles(const vector& vecForward, vector& vecAngles) {
		vector vecView;
		if (vecForward.y == 0 && vecForward.x == 0)
		{
			vecView.x = 0.f;
			vecView.y = 0.f;
		}
		else
		{
			vecView.y = atan2(vecForward.y, vecForward.x) * 180.f / 3.14f;

			if (vecView.y < 0.f)
				vecView.y += 360.f;

			auto tmp = vecForward.length_2d();

			vecView.x = atan2(-vecForward.z, tmp) * 180.f / 3.14f;

			if (vecView.x < 0.f)
				vecView.x += 360.f;
		}

		vecAngles.x = vecView.x;
		vecAngles.y = vecView.y;
		vecAngles.z = 0.f;
	}

	inline void normalize_angles(vector& angles)
	{
		while (angles.x > 89.0f)
			angles.x -= 180.0f;

		while (angles.x < -89.0f)
			angles.x += 180.0f;

		while (angles.y < -180.0f)
			angles.y += 360.0f;

		while (angles.y > 180.0f)
			angles.y -= 360.0f;

		angles.z = 0.0f;
	}

	inline float get_fov(const vector& view_angle, const vector& aim_angle)
	{
		vector delta = aim_angle - view_angle;
		normalize_angles(delta);

		return std::min(sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f)), 180.0f);
	}

	inline vector calc_angle(const vector& src, const vector& dst)
	{
		vector angles;

		vector delta = src - dst;
		float hyp = delta.length();

		angles.y = std::atanf(delta.y / delta.x) * M_RADPI;
		angles.x = std::atanf(-delta.z / hyp) * -M_RADPI;
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		return angles;
	}

	inline vector calculate_angle(vector& source, vector& destination, vector& view_angles)
	{
		vector delta = source - destination;
		vector angles;

		angles.x = rad_to_deg(std::atanf(delta.z / std::hypotf(delta.x, delta.y))) - view_angles.x;
		angles.y = rad_to_deg(std::atanf(delta.y / delta.x)) - view_angles.y;
		angles.z = 0.0f;

		if (delta.x >= 0.0)
		{
			angles.y += 180.0f;
		}

		return angles;
	}

	extern bool screen_transform(vector world_position, vector& screen_position);
	extern bool world_to_screen(vector& origin, vector& screen);

	inline void angle_vectors(const vector& angles, vector& forward)
	{
		float	sp, sy, cp, cy;

		sin_cos(DEG2RAD(angles[1]), &sy, &cy);
		sin_cos(DEG2RAD(angles[0]), &sp, &cp);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	template<class T>
	void normalize_3(T& vec)
	{
		for (auto i = 0; i < 2; i++) {
			while (vec[i] < -180.0f) vec[i] += 360.0f;
			while (vec[i] > 180.0f) vec[i] -= 360.0f;
		}
		vec[2] = 0.f;
	}

	template<class T, class U>
	T clamp(const T& in, const U& low, const U& high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}

	template <typename t>
	t interpolate(const t& t1, const t& t2, float progress)
	{
		if (t1 == t2)
			return t1;

		return t2 * progress + t1 * (1.0f - progress);
	}

	template <typename t>
	t lerp(const t& t1, const t& t2, float progress)
	{
		return t1 + (t2 - t1) * progress;
	}

	template <typename t>
	t lerp2(float progress, const t& t1, const t& t2)
	{
		return t1 + (t2 - t1) * progress;
	}
}