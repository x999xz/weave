#pragma once
#include <cstdint>

class c_gc_client_shared_object_cache;

struct soid_t {
    uint64_t m_id;
    uint32_t m_type;
    uint32_t m_padding;
};

class c_gc_client {
public:
    c_gc_client_shared_object_cache* find_so_cache(soid_t ID, bool bCreateIfMissing = true);
};