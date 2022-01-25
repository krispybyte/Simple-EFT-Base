#pragma once
#include "../../common.hpp"

class Physical
{
public:
	void set_stamina(float value)
	{
		const uintptr_t body_stamina = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x38);
		const uintptr_t hand_stamina = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x40);

		memory.write<float>(body_stamina + 0x48, value);
		memory.write<float>(hand_stamina + 0x48, value);
	}

	void set_no_fall_damage()
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + 0xB4, 0.f);
	}
};