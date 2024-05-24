#pragma once

#include <cstdint>

class c_address
{
public:
	template<typename t>
	t as()
	{
		return (t)(value_);
	}

	std::uintptr_t get()
	{
		return value_;
	}

	template<typename t>
	t cast()
	{
		return *(t*)(value_);
	}

	c_address add(int offset)
	{
		this->value_ += offset;
		return *this;
	}

	c_address get_absolute_address(size_t start, size_t end) {
		value_ += start;
		value_ = value_ + sizeof(std::int32_t) + *reinterpret_cast<std::int32_t*>(value_);
		value_ += end;
		return *this;
	}

	c_address abs(std::ptrdiff_t offset = 0x3, std::ptrdiff_t length = 7)
	{
		std::uintptr_t base = value_;

		const auto displacement = *reinterpret_cast<std::int32_t*>(base + offset);

		base += displacement;
		base += length;

		return *this;
	}

	c_address relative_address()
	{
		std::uintptr_t rva = *reinterpret_cast<std::uint32_t*>(value_);
		std::uintptr_t rip = value_ + sizeof(std::uint32_t);

		this->value_ = rva + rip;

		return *this;
	}
protected:
	std::uintptr_t value_;
public:
	c_address() = default;
	c_address(std::uint64_t value) : value_(value) {};
};