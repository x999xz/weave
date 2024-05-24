#pragma once
#include "../sdk/interfaces/virtual.hpp"

class c_shared_object;

class c_gc_client_shared_object_type_cache {
public:
    auto add_object(c_shared_object* pObject) {
        return CALL_VIRTUAL(bool, 1, this, pObject);
    }

    auto remove_object(c_shared_object* soIndex) {
        return CALL_VIRTUAL(c_shared_object*, 3, this, soIndex);
    }

    template <typename T>
    auto& get_vec_objects() {
        return *reinterpret_cast<c_utl_vector<T>*>((uintptr_t)(this) + 0x8);
    }
};