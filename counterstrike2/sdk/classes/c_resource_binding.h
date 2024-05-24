#pragma once

template <class T>
struct resource_binding {
    T* data;
    unsigned long long unk;
    unsigned long long unk2;
    volatile unsigned int* ref_count;
};