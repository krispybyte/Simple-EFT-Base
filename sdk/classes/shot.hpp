#pragma once
#include "../../common.hpp"

class Shot
{
public:
	uintptr_t get_player()
	{
		return memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);
	}

	bool has_hit_player()
	{
		uintptr_t hitted_collider = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x38);
		int hit_material_id = memory.read<int>(hitted_collider + 0x30);

		return hit_material_id == 2 || hit_material_id == 32 || hit_material_id == 34 || hit_material_id == 35 || hit_material_id == 36;
	}
};