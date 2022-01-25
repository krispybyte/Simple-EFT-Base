#pragma once
#include "../../common.hpp"

class ProceduralWeaponAnimation
{
private:
public:
	void set_no_recoil()
	{
		if (!reinterpret_cast<uintptr_t>(this))
			return;

		uintptr_t shot_effector = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x48);
		memory.write<float>(shot_effector + 0x70, 0.f);
	}

	void set_no_sway()
	{
		if (!reinterpret_cast<uintptr_t>(this))
			return;

		uintptr_t breath_effector = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x28);
		uintptr_t walk_effector = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x30);
		uintptr_t motion_effector = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x38);
		uintptr_t force_effector = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x40);

		memory.write<float>(breath_effector + 0xA4, 0.f);
		memory.write<float>(walk_effector + 0x44, 0.f);
		memory.write<float>(motion_effector + 0xD0, 0.f);
		memory.write<float>(force_effector + 0x30, 0.f);
	}

	Vector3 get_fireport()
	{
		if (!reinterpret_cast<uintptr_t>(this))
			return {};

		uintptr_t fire_arm_controller = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x80);
		uintptr_t transform = memory.read<uintptr_t>(fire_arm_controller + 0xE8);
		transform = memory.read<uintptr_t>(transform + 0x10);
		transform = memory.read<uintptr_t>(transform + 0x10);
		return bone.get_transform_position(transform);
	}

	BallisticsCalculator* get_ballistics()
	{
		if (!reinterpret_cast<uintptr_t>(this))
			return {};

		uintptr_t fire_arm_controller = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x80);
		return memory.read<BallisticsCalculator*>(fire_arm_controller + 0xE0);
	}

	bool set_instant_aim()
	{
		if (!reinterpret_cast<uintptr_t>(this))
			return false;

		memory.write<float>(reinterpret_cast<uintptr_t>(this) + 0x194, 10.f);
	}
};