#include "../tls/tls.h"
#include "crash_handler.h"

#include <string>
#include "../xorstr.h"
#include <tinyformat/tinyformat.h>
#include "../service/flatbuffers.hpp"
#include "../hash.h"
#include "../../core.hpp"

LONG __stdcall crash_handler::exception_handler(EXCEPTION_POINTERS* ex) {

	auto exception_code_ = ex->ExceptionRecord->ExceptionCode;

	if (exception_code_ != EXCEPTION_ACCESS_VIOLATION &&
		exception_code_ != EXCEPTION_ARRAY_BOUNDS_EXCEEDED &&
		exception_code_ != EXCEPTION_BREAKPOINT &&
		exception_code_ != EXCEPTION_DATATYPE_MISALIGNMENT &&
		exception_code_ != EXCEPTION_FLT_DENORMAL_OPERAND &&
		exception_code_ != EXCEPTION_FLT_DIVIDE_BY_ZERO &&
		exception_code_ != EXCEPTION_FLT_INEXACT_RESULT &&
		exception_code_ != EXCEPTION_FLT_INVALID_OPERATION &&
		exception_code_ != EXCEPTION_FLT_OVERFLOW &&
		exception_code_ != EXCEPTION_FLT_STACK_CHECK &&
		exception_code_ != EXCEPTION_FLT_UNDERFLOW &&
		exception_code_ != EXCEPTION_ILLEGAL_INSTRUCTION &&
		exception_code_ != EXCEPTION_IN_PAGE_ERROR &&
		exception_code_ != EXCEPTION_INT_DIVIDE_BY_ZERO &&
		exception_code_ != EXCEPTION_INT_OVERFLOW &&
		exception_code_ != EXCEPTION_INVALID_DISPOSITION &&
		exception_code_ != EXCEPTION_NONCONTINUABLE_EXCEPTION &&
		exception_code_ != EXCEPTION_PRIV_INSTRUCTION &&
		exception_code_ != EXCEPTION_SINGLE_STEP &&
		exception_code_ != EXCEPTION_STACK_OVERFLOW &&
		exception_code_ != 0xC0000374)
		return EXCEPTION_CONTINUE_SEARCH;

	HMODULE mod{};
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (const char*)ex->ContextRecord->Rip, &mod);

	std::string bytes;
	for (int i = 0; i < 20; i++) {
		const auto addr = ex->ContextRecord->Rip + i;
		bytes += tfm::format(xorstr_("%02X "), *(uint8_t*)addr);
	}

	char module_name[256]{};
	GetModuleFileNameA(mod, module_name, sizeof(module_name));

	auto offset = std::uintptr_t(ex->ExceptionRecord->ExceptionAddress) - std::uintptr_t(g_cs2->base_handle);
#ifdef _RELEASE
	std::string buffer = xorstr_("Release");
#elif _ALPHAB
	std::string buffer = xorstr_("Alpha");
#else
	std::string buffer = xorstr_("Debug");
#endif

	auto msg = tfm::format(xorstr_(R"#(Exception 0x%X at 0x%X offset 0x%X
Module: %s
Last bytes: %s
Username: %s
Build: %s
Initilization: %d
)#"), ex->ExceptionRecord->ExceptionCode, ex->ExceptionRecord->ExceptionAddress, offset, module_name, bytes, g_cs2->username, buffer, g_cs2->m_initilization);

	c_flatbuffers m_buffer;
	m_buffer.create_crash(msg, g_cs2->m_initilization_stage, g_cs2->m_latest_hook);
	m_buffer.create_stream(false);

	c_flatbuffers m_buffer2;
	m_buffer2.create_request(HASH("crash"), 1, m_buffer.m_buffer);
	m_buffer2.create_stream();

	g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());

	return EXCEPTION_CONTINUE_SEARCH;
}