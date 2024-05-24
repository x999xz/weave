#pragma once

class c_localize {
public:
    auto find_safe(const char* tokenName) {
        return CALL_VIRTUAL(const char*, 17, this, tokenName);
    }
};