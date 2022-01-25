#pragma once
#include "../../common.hpp"

class player_t
{
private:
public:
	bool is_local_player()
	{
		return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + 0x7FB);
	}

	bool is_dead()
	{
		return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + 0x6A0);
	}

	Vector3 get_bone(int bone_index)
	{
		return bone.get_bone(reinterpret_cast<uintptr_t>(this), bone_index);
	}

	Physical* physical()
	{
		return memory.read<Physical*>(reinterpret_cast<uintptr_t>(this) + 0x4C8);
	}

	Profile* profile()
	{
		return memory.read<Profile*>(reinterpret_cast<uintptr_t>(this) + 0x4B8);
	}

	MovementContext* movement()
	{
		return memory.read<MovementContext*>(reinterpret_cast<uintptr_t>(this) + 0x40);
	}
	
	ProceduralWeaponAnimation* weapon()
	{
		return memory.read<ProceduralWeaponAnimation*>(reinterpret_cast<uintptr_t>(this) + 0x190);
	}
};