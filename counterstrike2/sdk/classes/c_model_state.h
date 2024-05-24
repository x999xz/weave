#pragma once

class c_model_state
{
public:
    __forceinline strong_handle<c_model>& m_hModel() {
        return *reinterpret_cast<strong_handle<c_model>*>(reinterpret_cast<std::uint64_t>(this) + 0xA0 );
    };
    __forceinline unsigned long long MeshGroupMask() {
        return *reinterpret_cast<unsigned long long*>(reinterpret_cast<std::uint64_t>(this) + 0x180 );
    };

    c_bone_data*& get_bone_data() {
        return *(c_bone_data**)(std::uintptr_t(this) + 0x80);
    }
};