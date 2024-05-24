// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "utilities.hpp"
#include "../core.hpp"

#include <vector>
#include <Windows.h>

#include <winternl.h>
#include "dx11_helper/dx11_helper.hpp"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <deque>
#include <chrono>

std::vector<std::uint32_t> pattern_to_byte(const char* pattern)
{
	std::vector<std::uint32_t> bytes;
	char* start = const_cast<char*>(pattern);
	char* end = const_cast<char*>(pattern) + std::strlen(pattern);

	for (char* current = start; current < end; current++)
	{
		if (*current == '?')
		{
			current++;

			if (*current == '?')
				current++;


			bytes.emplace_back(std::uint32_t(-1));
		}
		else
		{
			bytes.emplace_back(std::uint32_t(std::strtoul(current, &current, 16)));
		}
	}

	return bytes;
}

c_address utilities::pattern_scan(std::uintptr_t module, const char* signature)
{
	PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dos_header->e_lfanew);

	std::size_t size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	std::uintptr_t image_base = module;

	uintptr_t first_match = 0;
	auto pattern = signature;
	for (uintptr_t current = image_base; current < image_base + size_of_image; current++)
	{
		if (!*pattern) 
			return first_match;

		if (*(PBYTE)pattern == ('\?') || *(BYTE*)current == get_byte(pattern))
		{
			if (!first_match) 
				first_match = current;

			if (!pattern[2])
				return first_match;

			if (*(PWORD)pattern == ('\?\?') || *(PBYTE)pattern != ('\?')) 
				pattern += 3;
			else 
				pattern += 2;
		}
		else
		{
			pattern = signature;
			first_match = 0;
		}
	}

	return 0;
}

std::uintptr_t utilities::resolve_rip(std::uintptr_t address, std::uintptr_t offset)
{
	if (!address)
		return 0;
	
	auto new_address = address + offset;

	std::uintptr_t rva = *reinterpret_cast<std::uint32_t*>(new_address);
	std::uintptr_t rip = new_address + sizeof(std::uint32_t);

	return rip + rva;
}

void utilities::random_seed(unsigned int seed)
{
	using random_seed_fn = void(__cdecl*)(unsigned int);
	random_seed_fn random_seed = g_cs2->m_patterns[FNV32("random_seed")].as<random_seed_fn>();
	random_seed(seed);
}

float utilities::random_float(float min, float max)
{
	using random_float_fn = float(__cdecl*)(float,float);
	random_float_fn random_float = g_cs2->m_patterns[FNV32("random_float")].as<random_float_fn>();
	return random_float(min,max);
}

inline IMAGE_NT_HEADERS* get_nt_headers(uintptr_t mod_base)
{
	return reinterpret_cast<IMAGE_NT_HEADERS*>(mod_base + reinterpret_cast<IMAGE_DOS_HEADER*>(mod_base)->e_lfanew);
}

uintptr_t utilities::get_module_base(const wchar_t* mod_name)
{
	PEB* peb = reinterpret_cast<PEB*>(__readgsqword(0x60));

	for (LIST_ENTRY* list_entry = reinterpret_cast<LIST_ENTRY*>(peb->Ldr->InMemoryOrderModuleList.Flink);
		list_entry != reinterpret_cast<LIST_ENTRY*>(&peb->Ldr->InMemoryOrderModuleList);
		list_entry = reinterpret_cast<LIST_ENTRY*>(list_entry->Flink))
	{
		LDR_DATA_TABLE_ENTRY* entry = CONTAINING_RECORD(list_entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
		if (!_wcsicmp(((UNICODE_STRING*)(&entry->Reserved4))->Buffer, mod_name))
			return (uintptr_t)entry->DllBase;
	}

	return 0;
}
uintptr_t utilities::get_proc_address(uintptr_t mod, char* name)
{
	IMAGE_NT_HEADERS* nt = get_nt_headers(mod);

	IMAGE_EXPORT_DIRECTORY* export_dir = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(mod + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	uint32_t* function_table = reinterpret_cast<uint32_t*>(mod + export_dir->AddressOfFunctions);
	uint32_t* names_table = reinterpret_cast<uint32_t*>(mod + export_dir->AddressOfNames);
	uint16_t* ordinals_table = reinterpret_cast<uint16_t*>(mod + export_dir->AddressOfNameOrdinals);

	for (uint32_t i = 0; i < export_dir->NumberOfNames; ++i)
		if (!_stricmp(reinterpret_cast<char*>(mod + names_table[i]), name))
			return mod + function_table[ordinals_table[i]];

	return 0;
}

void utilities::create_thread(void* target)
{

	typedef NTSTATUS(NTAPI* pfnNtCreateThreadEx)
		(
			OUT PHANDLE hThread,
			IN ACCESS_MASK DesiredAccess,
			IN PVOID ObjectAttributes,
			IN HANDLE ProcessHandle,
			IN PVOID lpStartAddress,
			IN PVOID lpParameter,
			IN ULONG Flags,
			IN SIZE_T StackZeroBits,
			IN SIZE_T SizeOfStackCommit,
			IN SIZE_T SizeOfStackReserve,
			OUT PVOID lpBytesBuffer);


	auto ntdll = get_module_base(xorstr_(L"ntdll.dll"));
	if (!ntdll)
		return;
	pfnNtCreateThreadEx NtCreateThreadEx = (pfnNtCreateThreadEx)get_proc_address(ntdll, xorstr_("NtCreateThreadEx"));
	if (!NtCreateThreadEx)
		return;

	HANDLE ThreadHandle = NULL;
#if defined(_DEBUG) || defined(_DebugDev) 
	NtCreateThreadEx(&ThreadHandle, THREAD_ALL_ACCESS, nullptr, ((HANDLE)(LONG_PTR)-1), (LPTHREAD_START_ROUTINE)target, nullptr, 0, 0, 0, 0, nullptr);
#else
	NtCreateThreadEx(&ThreadHandle, THREAD_ALL_ACCESS, nullptr, ((HANDLE)(LONG_PTR)-1), (LPTHREAD_START_ROUTINE)target, nullptr, 0x00000004 | 0x00000040, 0, 0, 0, nullptr);
#endif

}

void* utilities::get_virtual(void* class_pointer, std::uint32_t index)
{
	void** vtable = *static_cast<void***>(class_pointer);
	return vtable[index];
}

void utilities::create_hook_steam(__int64 iAddr, __int64 iFunction, __int64* iOriginal) {
	using function_t = void(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng);
	function_t hook = g_cs2->m_patterns[FNV32("create_hook")].as<function_t>();
	hook(iAddr, iFunction, iOriginal, 1);
}

std::vector<uint8_t> utilities::get_image_in_vtex_c(std::vector<uint8_t> binare)
{
	std::vector<uint8_t> new_binare{};

	for (int i{}; i < binare.size() - 8; i++)
	{
		if (binare[i] == 137 && binare[i + 1] == 80 && binare[i + 2] == 78 && binare[i + 3] == 71 && binare[i + 4] == 13 && binare[i + 5] == 10 && binare[i + 6] == 26 && binare[i + 7] == 10)
		{
			for (int j = i; j < binare.size(); j++)
			{
				new_binare.push_back(binare[j]);
			}
			break;
		}
	}

	return new_binare;
}

ID3D11ShaderResourceView* utilities::create_image_path(std::string path)
{
	std::vector< std::uint8_t > raw_image;

	std::ifstream file(path, std::ios::binary);
	file.unsetf(std::ios::skipws);
	file.seekg(0, std::ios::end);

	const auto raw_size = file.tellg();

	file.seekg(0, std::ios::beg);
	raw_image.reserve(static_cast<uint32_t>(raw_size));
	raw_image.insert(raw_image.begin(), std::istream_iterator< std::uint8_t >(file), std::istream_iterator< std::uint8_t >());

	file.close();

	return create_image_memory(raw_image.data(), raw_image.size());
}

std::string get_day(int day) {
	switch (day) {
	case 0:
		return xorstr_("Monday");
		break;
	case 1:
		return xorstr_("Tuesday");
		break;
	case 2:
		return xorstr_("Wednesday");
		break;
	case 3:
		return xorstr_("Thursday");
		break;
	case 4:
		return xorstr_("Friday");
		break;
	case 5:
		return xorstr_("Saturday");
		break;
	case 6:
		return xorstr_("Sunday");
		break;
	}

	return xorstr_("unk");
}

int time_offset()
{
	time_t gmt, rawtime = time(NULL);
	struct tm* ptm;

#if !defined(WIN32)
	struct tm gbuf;
	ptm = gmtime_r(&rawtime, &gbuf);
#else
	ptm = gmtime(&rawtime);
#endif
	// Request that mktime() looksup dst in timezone database
	ptm->tm_isdst = -1;
	gmt = mktime(ptm);

	return (int)difftime(rawtime, gmt);
}

std::string utilities::get_time_date(messages& message) {
	if (message.unixtime <= 0)
		return xorstr_("time error");

	const auto currentTime = std::chrono::system_clock::now();
	auto unix_time = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();

	const std::time_t epoch_plus_11h = 60 * 60 * 11;
	const int local_time = localtime(&epoch_plus_11h)->tm_hour;
	const int gm_time = gmtime(&epoch_plus_11h)->tm_hour;
	const int tz_diff = local_time - gm_time;

	UnixTime current_time_stamp(tz_diff);
	current_time_stamp.getDateTime(unix_time);

	UnixTime time_stamp(tz_diff);
	time_stamp.getDateTime(message.unixtime);

	std::string month = std::to_string(time_stamp.month);

	if (time_stamp.month < 10) {
		month = xorstr_("0") + std::to_string(time_stamp.month);
	}

	std::string time_date = std::to_string(time_stamp.day) + xorstr_(".") + std::to_string(time_stamp.month) + xorstr_(" at ");

	if (current_time_stamp.day == time_stamp.day && current_time_stamp.month == time_stamp.month) {
		time_date = xorstr_("Today at ");
	}

	int max_days{};

	if (time_stamp.month == 2) {
		max_days = 29;
	}
	else {
		switch (time_stamp.month % 2) {
		case 0:
			max_days = 31;
		case 1:
			max_days = 30;
			break;
		}
	}

	if ((current_time_stamp.day - 1) == time_stamp.day || (current_time_stamp.day == 1 && time_stamp.day == max_days && (current_time_stamp.month - 1) == time_stamp.month )) {
		time_date = xorstr_("Yesterday at ");
	}

	std::string minutes = std::to_string(time_stamp.minute);

	if (time_stamp.minute < 10) {
		minutes = xorstr_("0") + std::to_string(time_stamp.minute);
	}

	time_date += std::to_string(time_stamp.hour) + xorstr_(":") + minutes;

	return time_date;
}

ID3D11ShaderResourceView* utilities::create_image_memory(uint8_t* data, int size)
{
	ID3D11ShaderResourceView* image;
	int c = 0, * int_delays = NULL;
	int weight{}, height{};

	stbi_set_flip_vertically_on_load(0);
	stbi_set_flip_vertically_on_load_thread(0);
	auto image_data = stbi_load_from_memory((unsigned char*)data, size, &weight, &height, NULL, 4);

	if (!image_data)
		return nullptr;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = weight;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = weight * sizeof(uint32_t);
	subResource.SysMemSlicePitch = 0;
	g_d3d11_helper->get_device()->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_d3d11_helper->get_device()->CreateShaderResourceView(pTexture, &srvDesc, &image);
	pTexture->Release();

	stbi_image_free(image_data);
	stbi_image_free(int_delays);

	return image;
}