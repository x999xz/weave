#pragma once

#include "../sdk.hpp"
#include <optional>

template <typename K, typename V>
class CUtlMap {
public:
    struct node_t {
        int m_left;
        int m_right;
        int m_parent;
        int m_tag;
        K m_key;
        V m_value;
    };

    auto begin() const { return m_data; }
    auto end() const { return m_data + m_size; }

    std::optional<V> find_by_key(K key) {
        int current = m_root;

        for (node_t* it = begin(); it != end(); it++)
        {
            if (it->m_key == key)
                return it->m_value;
        }

        return {};
    }

    char pad0[0x8];  // no idea
    node_t* m_data;
    char pad1[0x8];  // no idea
    int m_root;
    int m_size;
    char pad2[0x8];  // no idea
};