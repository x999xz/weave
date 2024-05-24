#pragma once

typedef int* utl_sym_large_id_t;

#define UTL_INVAL_SYMBOL_LARGE  ((utl_sym_large_id_t)~0)

class c_utl_symbol_large
{
public:
	// constructor, destructor
	c_utl_symbol_large()
	{
		u.m_id = UTL_INVAL_SYMBOL_LARGE;
	}

	c_utl_symbol_large(utl_sym_large_id_t id)
	{
		u.m_id = id;
	}
	c_utl_symbol_large(c_utl_symbol_large const& sym)
	{
		u.m_id = sym.u.m_id;
	}

	// operator=
	c_utl_symbol_large& operator=(c_utl_symbol_large const& src)
	{
		u.m_id = src.u.m_id;
		return *this;
	}

	// operator==
	bool operator==(c_utl_symbol_large const& src) const
	{
		return u.m_id == src.u.m_id;
	}

	// operator==
	bool operator==(utl_sym_large_id_t const& src) const
	{
		return u.m_id == src;
	}

	// operator==
	bool operator!=(c_utl_symbol_large const& src) const
	{
		return u.m_id != src.u.m_id;
	}

	// operator==
	bool operator!=(utl_sym_large_id_t const& src) const
	{
		return u.m_id != src;
	}

	// Gets at the symbol
	operator utl_sym_large_id_t const() const
	{
		return u.m_id;
	}

	// Gets the string associated with the symbol
	inline const char* string() const
	{
		if (u.m_id == UTL_INVAL_SYMBOL_LARGE)
			return "";
		return u.m_p_string;
	}

	inline bool is_valid() const
	{
		return u.m_id != UTL_INVAL_SYMBOL_LARGE ? true : false;
	}

private:
	// Disallowed
	c_utl_symbol_large(const char* pStr);       // they need to go through the table to assign the ptr
	bool operator==(const char* pStr) const; // disallow since we don't know if the table this is from was case sensitive or not... maybe we don't care

	union
	{
		utl_sym_large_id_t m_id;
		char const* m_p_string;
	} u;
};