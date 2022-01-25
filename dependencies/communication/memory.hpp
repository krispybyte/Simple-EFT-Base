#pragma once

class memory_t
{
private:
public:
	bool read(uintptr_t address, void* buffer, size_t size)
	{
		/*
		*	removed
		*/

		return true;
	}

	template <typename T>
	T read(uintptr_t address)
	{
		/*
		*	removed
		*/

		return {};
	}

	std::string read_str(uintptr_t address, size_t size = 64)
	{
		/*
		*	removed
		*/

		return {};
	}

	std::wstring read_wstr(uintptr_t address)
	{
		/*
		*	removed
		*/

		return {};
	}

	template <typename T>
	T read_chain(uintptr_t address, std::vector<uintptr_t> chain)
	{
		/*
		*	removed
		*/

		return {};
	}

	template<typename V>
	bool write(uintptr_t address, const V& value)
	{
		/*
		*	removed
		*/

		return true;
	}

	uintptr_t module_base_alternative(const char* name)
	{
		/*
		*	removed
		*/

		return {};
	}

	uintptr_t module_base(const wchar_t* name)
	{
		/*
		*	removed
		*/

		return {};
	}

	uintptr_t peb()
	{
		if (globals.peb)
			return NULL;

		/*
		*	removed
		*/

		return {};
	}
} memory;