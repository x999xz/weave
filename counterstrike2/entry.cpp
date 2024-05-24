#include "utilities/tls/tls.h"
#include <chrono>
#include <thread>
#include "sdk/interfaces/interfaces.hpp"
#include "sdk/schema_system/schema_system.hpp"
#include "utilities/debug_console/debug.hpp"
#include "hooks/hooks.hpp"
#include "Logging.h"
#include "GUI/GUI.h"
#include <tinyformat/tinyformat.h>
#include "utilities/channel_system.h"
#include "utilities/input_system/input_system.h"
#include "utilities/hotkey_system/hotkey_system.h"
#include "utilities/cloud/user.h"
#include "utilities/cloud/utils.h"
#include "feature/misc/hitmarker.h"
#include "loader/loader.h"
#include "utilities/service/flatbuffers.hpp"
#include <future>
#include "utilities/exception/weave_error.h"
#include "sdk/vtex/VTexParser.h"
#include "feature/inventory_changer/inventory_changer.h"
#include <fstream>
#include <filesystem>
#include "feature/misc/hitsound.h"
#include "load_network_balancer/load_network_balancer.h"
#include "utilities/hash.h"
#include "utilities/crash_handler/crash_handler.h"
#include "utilities/multithread/multithread.hpp"

__crt_bool __cdecl __acrt_initialize(void) {
	return true;
}
__crt_bool __cdecl __acrt_uninitialize(
	_In_ __crt_bool _Terminating
) {
	return 1;
}
__crt_bool __cdecl __acrt_uninitialize_critical(
	_In_ __crt_bool _Terminating
) {
	return 1;
}
__crt_bool __cdecl __acrt_thread_attach(void) {
	return 1;
}
__crt_bool __cdecl __acrt_thread_detach(void) {
	return 1;
}
__vcrt_bool __cdecl __vcrt_initialize(void) {
	return 1;
}
__vcrt_bool __cdecl __vcrt_uninitialize(_In_ __vcrt_bool _Terminating) {
	return 1;
}
__vcrt_bool __cdecl __vcrt_uninitialize_critical(void) {
	return 1;
}
__vcrt_bool __cdecl __vcrt_thread_attach(void) {
	return 1;
}
__vcrt_bool __cdecl __vcrt_thread_detach(void) {
	return 1;
}
int __cdecl _is_c_termination_complete(void) {
	return 0;
}

void initialize()
{
	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::RenderInitilization;
	hooks::render_initilization();

	LogInfo("Processing Auth");

	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::ProcessingAuth;

	g_user->Processing(EProcessingType::Auth);
}

DWORD APIENTRY release()
{
	hooks::release();

#if defined(_DEBUG) || defined(_DebugDev) 
	g_debug.release();
#endif

	return TRUE;
}

Semaphore dispatchSem;
SharedMutex smtx;

using ThreadIDFn = int(_cdecl*)();

ThreadIDFn AllocateThreadID;
ThreadIDFn FreeThreadID;

int AllocateThreadIDWrapper() {
	return AllocateThreadID();
}

int FreeThreadIDWrapper() {
	return FreeThreadID();
}

template<typename T, T& Fn>
static void AllThreadsStub(void*) {
	dispatchSem.Post();
	smtx.rlock();
	smtx.runlock();
	Fn();
}


// TODO: Build this into the threading library
template<typename T, T& Fn>
static void DispatchToAllThreads(void* data) {
	smtx.wlock();

	for (size_t i = 0; i < Threading::numThreads; i++)
		Threading::QueueJobRef(AllThreadsStub<T, Fn>, data);

	for (size_t i = 0; i < Threading::numThreads; i++)
		dispatchSem.Wait();

	smtx.wunlock();

	Threading::FinishQueue();
}

BOOL APIENTRY entry_point(c_loader* loader_interface, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

#if !defined(_DEBUG)
		AddVectoredExceptionHandler(false, crash_handler::exception_handler);
#endif

#if defined(_DEBUG) || defined(_DebugDev) 
		g_debug.initialize(xorstr_("weave debug env"));
#endif

		//AllocateThreadID = (ThreadIDFn)GetProcAddress(GetModuleHandleA(xorstr_("tier0.dll")), xorstr_("AllocateThreadID"));

		//Threading::InitThreads();

		//DispatchToAllThreads<ThreadIDFn, AllocateThreadID>(nullptr);

		g_cs2 = std::make_unique<cs2>();

		g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Memory;

		g_cs2->base_handle = (std::uintptr_t*)loader_interface;
		g_schema_system = std::make_unique<schema_system>();
		g_d3d11_helper = std::make_unique<d3d11_helper>();
		g_utils = std::make_unique<utilities>();
		g_gui = std::make_unique<c_gui>();
		g_chams = std::make_unique<c_chams>();
		g_event = std::make_unique<c_event>();
		g_visuals = std::make_unique<c_visuals>();
		g_ragebot = std::make_unique<c_rage_bot>();
		g_legit_bot = std::make_unique<c_legit_bot>();
		g_firebullet = std::make_unique<c_firebullet>();
		g_firebullet_cs2 = std::make_unique<c_firebullet_cs2>();
		g_fx_firebullet = std::make_unique<c_fx_firebullet>();
		g_stack_trace = std::make_unique<c_stack_trace>();
		g_misc = std::make_unique<c_misc>();
		g_antiaim = std::make_unique<c_antiaim>();
		g_prediction_system = std::make_unique<c_prediction_system>();
		g_movement = std::make_unique<c_movement>();
		g_channel_system = std::make_unique<c_channel_system>();
		g_lagcompensation = std::make_unique<c_lagcompensation>();
		g_input_system = std::make_unique<c_input_system>();
		g_hotkey = std::make_unique<c_hotkey>();
		g_hotkey->hotkeys_ = std::make_unique< std::unordered_map<std::uint64_t, hotkeys>>();
		g_web_utils = std::make_unique<web_utils>();
		g_user = std::make_unique<CUser>();
		g_inventory_changer = std::make_unique<c_inventory_changer>();
		g_hitmarker = std::make_unique<c_hitmarker>();
		g_hitsounds = std::make_unique<hitsound>();
		g_tls_client = std::make_unique<c_tls_client>();
		g_pSchemaOffset = std::make_unique<CSchemaOffset>();
		g_load_network_balancer = std::make_unique<load_network_balancer>();

		g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::LoaderData;

#if !defined(_DEBUG)
		g_loader = std::unique_ptr<c_loader>(loader_interface);
#else 
		g_loader = std::make_unique<c_loader>();
		strncpy(g_loader->username, xorstr_("ev0j1ix"), sizeof("ev0j1ix"));
		strncpy(g_loader->token, xorstr_("180al6iil5i58i1522a11988l8a2a0al"), sizeof("180al6iil5i58i1522a11988l8a2a0al"));
#endif

		//g_loader = new c_loader;
		//strncpy(g_loader->username, xorstr_("ev0j1ix"), sizeof("ev0j1ix"));
		//strncpy(g_loader->token, xorstr_("ce4a42640ac90o42980545ac6464e0l5"), sizeof("ce4a42640ac90o42980545ac6464e0l5"));

		g_loader->Setup();

		g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::LoadNetworkBalancer;

		//->setup();

		g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::TLSConnect;

		//if (!g_tls_client->connect())
		//{
		//	MessageBoxA(0, xorstr_("failed to connect to the server write a ticket for our team to quickly solve this problem"), 0, MB_TOPMOST);
		//	exit(0);
		//}

		g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::CreateThread;

		std::thread(initialize).detach();
	}

	return TRUE;
}