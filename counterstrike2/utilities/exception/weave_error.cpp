// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "weave_error.h"
#include <Windows.h>
#include "../xorstr.h"
#include <tinyformat/tinyformat.h>

weave_error::weave_error(std::string _Message) {
	this->Message_ = _Message;

	auto error_msg_ = tfm::format(xorstr_("Weave Error: %s"), this->Message_);
	auto title = xorstr_("Weave Error!");

#ifndef _RELEASE
	MessageBoxA(nullptr, error_msg_.c_str(), title, MB_OK);
#endif

	exit(0);
}