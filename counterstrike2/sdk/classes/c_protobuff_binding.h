#pragma once
#include "../sdk.hpp"

class c_protobuff_binding
{
public:
	virtual const char* GetName(void) = 0;
	virtual int GetSize(void) = 0;
	virtual const char* ToString(void* msg, c_utl_string* storage) = 0;
	virtual const char* GetGroup(void) = 0;
	virtual void GetGroupColor(void) = 0;
	virtual void GetBufType(void) = 0;
	virtual bool ReadFromBuffer(void* msg, void*) = 0; // true if parsing O = 0K
	virtual bool WriteToBuffer(void* msg, void*) = 0; // true if parsing O = 0K
	virtual void* AllocateMessage(void) = 0;
	virtual void DeallocateMessage(void*) = 0;
	virtual void* AllocateAndCopyConstructNetMessage(void const* otherProtobufMsg) = 0;
	virtual bool OkToRedispatch(void) = 0;
	virtual void Copy(void const*, void*) = 0;
};