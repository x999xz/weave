#pragma once 

#include "../sdk.hpp"

class c_base_file_system
{
public:
	int Read(void* pOutput, int size, void* file)
	{
		using Fn = int(__thiscall*)(void*, void*, int, void*);
		return CALL_VIRTUAL(int, 11, this, pOutput, size, file);// call_virtual<Fn>(this, 0)(this, pOutput, size, file);
	}

	// if pathID is NULL, all paths will be searched for the file
	void* Open(const char* pFileName, const char* pOptions, const char* pathID = nullptr)
	{
		using Fn = void* (__thiscall*)(void*, const char*, const char*, const char*);
		return CALL_VIRTUAL(void*, 13, this, pFileName, pOptions, pathID); // call_virtual<Fn>(this, 2)(this, pFileName, pOptions, pathID);
	}

	void Close(void* file)
	{
		using Fn = void(__thiscall*)(void*, void*);
		return CALL_VIRTUAL(void, 14, this, file);
	}

	unsigned int Size(void* file)
	{
		using Fn = unsigned int(__thiscall*)(void*, void*);
		return CALL_VIRTUAL(unsigned int, 18, this, file);
	}

	const char* unk(const char* file, std::uintptr_t* unk)
	{
		return CALL_VIRTUAL(const char*, 60, this, file, unk);
	}
};