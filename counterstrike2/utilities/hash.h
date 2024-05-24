#pragma once

#ifndef HASH_H
#define HASH_H

template< typename T, T value >
struct constant_holder_t
{
	enum class e_value_holder : T
	{
		m_value = value
	};
};

#define CONSTANT( value ) ( static_cast< decltype( value ) >( constant_holder_t< decltype( value ), value >::e_value_holder::m_value ) )

namespace fnv1a
{
	constexpr auto fnv_basis = 14695981039346656037ull;
	constexpr auto fnv_prime = 1099511628211ull;

	template< typename _ty >
	__attribute__((always_inline)) inline unsigned long long rt(const _ty* txt)
	{
		auto hash = fnv_basis;

		size_t length = 0;
		while (txt[length])
			++length;

		for (auto i = 0u; i < length; i++)
		{
			hash ^= txt[i];
			hash *= fnv_prime;
		}

		return hash;
	}

	template< typename _ty >
	constexpr unsigned long long ct(const _ty* txt, unsigned long long value = fnv_basis)
	{
		return !*txt ? value : ct(txt + 1, static_cast<unsigned long long>(1ull * (value ^ static_cast<unsigned char>(*txt)) * fnv_prime));
	}
}

#define HASH( s ) CONSTANT( fnv1a::ct( s ) )
#define HASH_RT( s ) fnv1a::rt( s )

#endif