#pragma once

#include "../sdk.hpp"

struct bullet_info_t
{

	bullet_info_t()
	{
		position = vector(0, 0, 0);
		time_stamp = 0;
		expire_time = -1;
	}

	bullet_info_t(vector position, float time_stamp, float expire_time)
	{
		position = position;
		time_stamp = time_stamp;
		expire_time = expire_time;
	}

	vector	position{};
	float	time_stamp{};
	float	expire_time{};
};

class c_cs_player_bullet_services
{
public:
    //SCHEMA(CCSPlayer_BulletServices, m_totalHitsOnServer, m_total_hits_on_server, int);
public:
    int m_bullet_count()
    {
        return *reinterpret_cast<int*>(std::uintptr_t(this) + 0x48);
    }
    c_utl_vector<bullet_info_t>& m_bullet_data()
    {
        return *reinterpret_cast<c_utl_vector<bullet_info_t>*>(std::uintptr_t(this) + 0x48);
    }
};