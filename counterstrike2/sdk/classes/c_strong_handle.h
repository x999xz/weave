#pragma once

template <class T>
class strong_handle {
public:
    operator T* () {

        if (!binding)
            return nullptr;

        return binding->data;
    }
    T* operator->() {

        if (!binding)
            return nullptr;

        return binding->data;
    }
public:
    const resource_binding<T>* binding;
};