#pragma once
#include "../../common.hpp"

class MovementContext
{
public:
	Vector2 get_viewangles()
	{
		return memory.read<Vector2>(reinterpret_cast<uintptr_t>(this) + 0x22C);
	}

	void set_viewangles(Vector2 value)
	{
		memory.write<Vector2>(reinterpret_cast<uintptr_t>(this) + 0x22C, value);
	}
};