#pragma once
#include "../../common.hpp"

class Magazine
{
private:
public:
	void set_fast_reload()
	{
		memory.write<float>(memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x170) + 0x28, 90.f);
		memory.write<float>(memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x178) + 0x28, 90.f);
		memory.write<float>(memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x190) + 0x28, 90.f);
	}
};