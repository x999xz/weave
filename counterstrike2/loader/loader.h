#pragma once

#include <memory>

class c_loader {
public:
	void Setup();
public:
	char token[33];
	char username[256];
};

inline auto g_loader = std::make_unique<c_loader>();