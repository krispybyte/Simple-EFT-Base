#pragma once
#include "../../common.hpp"

class BallisticsCalculator
{
public:
	std::vector<Shot*> get_shot_list()
	{
		uintptr_t shot_list = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x18);

		int count = memory.read<int>(shot_list + 0x18);
		uintptr_t list_ptr = memory.read<uintptr_t>(shot_list + 0x10);

		std::vector<Shot*> temp{};

		for (int i = 0; i < count; i++) 
			temp.push_back(memory.read<Shot*>(list_ptr + (0x20 + (i * 8))));

		return temp;
	}
};