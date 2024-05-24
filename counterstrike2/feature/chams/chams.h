#pragma once

class c_chams
{
	enum chams
	{
		flat,
		regular,
		metalic,
		glow,
		max_count
	};
public:
	void initilization();
	i_material* get_material(int type, bool invisible) { return invisible ? Materials[type][1] : Materials[type][0]; }
private:
	i_material* create_material(const char* vmat);
protected:
	i_material* Materials[chams::max_count][2];
};

inline auto g_chams = std::make_unique<c_chams>();