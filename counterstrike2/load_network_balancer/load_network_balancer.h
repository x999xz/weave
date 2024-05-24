#pragma once

#include <vector>

class load_network_balancer
{
public:
	void setup();
	unsigned long& get_server();
private:
	int send_request(unsigned long ip);
	std::vector<unsigned long> m_pools;
	unsigned long best_server;
};

inline auto g_load_network_balancer = std::make_unique<load_network_balancer>();

