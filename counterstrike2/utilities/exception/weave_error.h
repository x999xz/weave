#pragma once
#include <string>

class weave_error {
public:
	weave_error(std::string _Message);
private:
	std::string Message_;
};