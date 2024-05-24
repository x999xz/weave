#pragma once

#include <cstdint>
#include <array>
#include <vector>

class CUtlMemoryPool
{
public:
	int Count() const
	{
		return nBlocksAllocated;
	}

	int PeakCount() const
	{
		return nPeakAlloc;
	}

	int BlockSize() const
	{
		return nBlockSize;
	}

protected:
	class CBlob
	{
	public:
		CBlob* pPrev;
		CBlob* pNext;
		int nNumBytes;
		char Data[1];
		char Padding[3];
	};

	int nBlockSize;
	int nBlocksPerBlob;
	int nGrowMode;
	int nBlocksAllocated;
	int nPeakAlloc;

	unsigned short nAlignment;
	unsigned short nNumBlobs;

	void* pHeadOfFreeList;
	void* pAllocOwner;
	CBlob BlobHead;
};

using UtlTSHashHandle_t = std::uintptr_t;

inline unsigned HashIntConventional(const int n)
{
	unsigned hash = 0xAAAAAAAA + (n & 0xFF);
	hash = (hash << 5) + hash + ((n >> 8) & 0xFF);
	hash = (hash << 5) + hash + ((n >> 16) & 0xFF);
	hash = (hash << 5) + hash + ((n >> 24) & 0xFF);

	return hash;
}

template <int nBucketCount, class tKey = std::uintptr_t>
class CUtlTSHashGenericHash
{
public:
	static int Hash(const tKey& Key, int nBucketMask)
	{
		int nHash = HashIntConventional(std::uintptr_t(Key));
		if (nBucketCount <= UINT16_MAX)
		{
			nHash ^= (nHash >> 16);
		}

		if (nBucketCount <= UINT8_MAX)
		{
			nHash ^= (nHash >> 8);
		}

		return (nHash & nBucketMask);
	}

	static bool Compare(const tKey& lhs, const tKey& rhs)
	{
		return lhs == rhs;
	}
};

template <class tElement, int nBucketCount, class tKey = std::uintptr_t, class tHashFuncs = CUtlTSHashGenericHash<nBucketCount, tKey>, int nAlignment = 0>
class CUtlTSHash
{
	static constexpr int nBucketMask = nBucketCount - 1;

public:
	static constexpr UtlTSHashHandle_t InvalidHandle()
	{
		return static_cast<UtlTSHashHandle_t>(0);
	}

	UtlTSHashHandle_t Find(tKey uiKey)
	{
		int iBucket = tHashFuncs::Hash(uiKey, nBucketCount);
		const HashBucket_t& hashBucket = aBuckets[iBucket];
		const UtlTSHashHandle_t hHash = Find(uiKey, hashBucket.pFirst, nullptr);
		return hHash ? hHash : Find(uiKey, hashBucket.pFirstUncommited, hashBucket.pFirst);
	}

	int Count() const
	{
		return EntryMemory.Count();
	}

	int GetElements(int nFirstElement, int nCount, UtlTSHashHandle_t* pHandles) const
	{
		int nIndex = 0;
		for (int nBucketIndex = 0; nBucketIndex < nBucketCount; nBucketIndex++)
		{
			const HashBucket_t& hashBucket = aBuckets[nBucketIndex];

			HashFixedData_t* pElement = hashBucket.pFirstUncommited;
			for (; pElement; pElement = pElement->pNext)
			{
				if (--nFirstElement >= 0)
					continue;

				pHandles[nIndex++] = reinterpret_cast<UtlTSHashHandle_t>(pElement);

				if (nIndex >= nCount)
					return nIndex;
			}
		}

		return nIndex;
	}

	tElement Element(UtlTSHashHandle_t hHash)
	{
		return ((HashFixedData_t*)(hHash))->Data;
	}

	const tElement& Element(UtlTSHashHandle_t hHash) const
	{
		return reinterpret_cast<HashFixedData_t*>(hHash)->Data;
	}

	tElement& operator[](UtlTSHashHandle_t hHash)
	{
		return reinterpret_cast<HashFixedData_t*>(hHash)->Data;
	}

	const tElement& operator[](UtlTSHashHandle_t hHash) const
	{
		return reinterpret_cast<HashFixedData_t*>(hHash)->Data;
	}

	tKey GetID(UtlTSHashHandle_t hHash) const
	{
		return reinterpret_cast<HashFixedData_t*>(hHash)->uiKey;
	}

private:
	template <typename tData>
	struct HashFixedDataInternal_t
	{
		tKey uiKey;
		HashFixedDataInternal_t<tData>* pNext;
		tData Data;
	};

	using HashFixedData_t = HashFixedDataInternal_t<tElement>;

	struct HashBucket_t
	{
	private:
		[[maybe_unused]] std::byte pad0[0x18];

	public:
		HashFixedData_t* pFirst;
		HashFixedData_t* pFirstUncommited;
	};

	UtlTSHashHandle_t Find(tKey uiKey, HashFixedData_t* pFirstElement, HashFixedData_t* pLastElement)
	{
		for (HashFixedData_t* pElement = pFirstElement; pElement != pLastElement; pElement = pElement->pNext)
		{
			if (tHashFuncs::Compare(pElement->uiKey, uiKey))
				return reinterpret_cast<UtlTSHashHandle_t>(pElement);
		}

		return InvalidHandle();
	}

	CUtlMemoryPool EntryMemory;
	char pad[0x40];
	HashBucket_t aBuckets[nBucketCount];
	bool bNeedsCommit;
};

typedef struct _schema_class_info_data_t schema_class_info_data_t;
class schema_system_type_scope;

class schema_enum_binding
{
public:
	virtual const char* get_binding_name() = 0;
	virtual void* as_class_binding() = 0;
	virtual schema_enum_binding* as_enum_binding() = 0;
	virtual const char* get_binary_name() = 0;
	virtual const char* get_project_name() = 0;
public:
	char* m_binding_name;
};

class schema_type
{
public:
	bool get_sizes(int* out_size1, uint8_t* unk_probably_not_size)
	{
		return reinterpret_cast<int(__thiscall*)(void*, int*, uint8_t*)>(this->m_vtable[3])(this, out_size1, unk_probably_not_size);
	}
public:
	bool get_size(int* out_size)
	{
		uint8_t smh = 0;
		return get_sizes(out_size, &smh);
	}
public:
	std::uintptr_t* m_vtable;
	const char* m_name;
	schema_system_type_scope* m_type_scope;
	std::uint8_t m_type_category;
	std::uint8_t m_atomic_category;

	schema_type* get_ref_class()
	{
		if (this->m_type_category != 1)
		{
			return nullptr;
		}

		schema_type* ptr = this->m_schema_type;

		while (ptr && ptr->m_type_category == 1)
		{
			ptr = ptr->m_schema_type;
		}

		return ptr;
	}

	typedef struct _array_t
	{
		std::uint32_t array_size;
		std::uint32_t unknown;
		schema_type* element_type_;
	} array_t;

	typedef struct _atomic_t
	{
		std::uint64_t gap[2];
		schema_type* template_typename;
	} atomic_t;

	typedef struct _atomic_tt
	{
		std::uint64_t gap[2];
		schema_type* templates[2];
	} atomic_tt;

	typedef struct _atomic_i
	{
		std::uint64_t gap[2];
		std::uint64_t integer;
	} atomic_i;

	union
	{
		schema_type* m_schema_type;
		schema_class_info_data_t* m_class_info;
		void* m_enum_binding_;
		array_t m_array_;
		atomic_t m_atomic_t_;
		atomic_tt m_atomic_tt_;
		atomic_i m_atomic_i_;
	};
};

typedef struct _schema_class_field_data_t
{
	const char* name;
	schema_type* type;
	short offset;
	unsigned char pad1[0xE];
} schema_class_field_data_t;

typedef struct _schema_class_info_data_t
{
	unsigned char pad1[0x8];
	const char* name;
	char* module;
	std::int32_t size;
	std::int16_t field_size;
	std::int16_t static_size;
	std::int16_t metadata_size;
	std::int16_t i_unk1;
	std::int16_t i_unk2;
	std::int16_t i_unk3;
	schema_class_field_data_t* fields;
} schema_class_info_data_t;

typedef struct _schema_type_t
{
	std::uintptr_t* vtable;
	const char* name;
} schema_type_t;

typedef struct _schema_class_binding_t
{
	_schema_class_binding_t* parent;
	const char* binary_name;
	const char* module_name;
	const char* class_name;
	void* class_info_old_synthesized;
	void* class_info;
	void* this_module_binding_pointer;
	schema_type_t* schema_type;
} schema_class_binding_t;

class schema_system_type_scope
{
public:
	schema_class_info_data_t* find_type_declared_class(const char* name)
	{
		// %s Schema Type: %s\n
		schema_class_info_data_t* class_info;
		using function_t = void(__thiscall*)(void*, schema_class_info_data_t**, const char*);
		(*reinterpret_cast<function_t**>(this))[2](this, &class_info, name);
		return class_info;
	}

public:
	char pad1[0x8];
	char m_name[256];
	unsigned char pad2[0x4B8];
	CUtlTSHash<schema_class_binding_t*, 256, unsigned int> m_classes;
	//char pad3[0x2804];
};

class i_schema_system
{
public:
	schema_system_type_scope* global_type_scope()
	{
		using function_t = schema_system_type_scope*(__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[11](this);
	}

	schema_system_type_scope* find_type_scope_for_module(const char* module)
	{
		using function_t = schema_system_type_scope*(__thiscall*)(void*, const char*, std::uintptr_t*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[13](this, module, nullptr);
	}
};