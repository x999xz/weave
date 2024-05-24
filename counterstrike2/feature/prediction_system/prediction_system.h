#pragma once

struct prediction_storage
{
	float real_time;
	float current_time;
	float tick_count;

	float spread;
	float accuracy;

	bool command_prediction;
	bool game_prediction;
	bool prediction;
	bool first_prediction;
	bool on_ground;
};

class c_prediction_system
{
public:
	void update(c_user_cmd* cmd);
	void begin(c_user_cmd* cmd);
	void end();
public:
	float get_spread() { return storage_.spread; };
	float get_accuracy() { return storage_.accuracy; };
private:
	void movement_processing(c_player_movement_services* movement, c_user_cmd* cmd);
	void set_prediction_data(c_player_movement_services* movement, c_user_cmd* cmd);
	void set_prediction_command(int command);
	void run_prediction();
	void reset_prediction_data();
public:
	prediction_storage storage_;
};

inline auto g_prediction_system = std::make_unique<c_prediction_system>();