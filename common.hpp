#pragma once
#define WIN32_LEAN_AND_MEAN

#pragma warning (disable : 4838)
#pragma warning (disable : 4309)
#pragma warning (disable : 4312)
#pragma warning (disable : 4244)
#pragma warning (disable : 4996)

#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <cstdint>
#include <thread>
#include <array>
#include <winternl.h>
#include <playsoundapi.h>
#include <codecvt>
#include <vector>
#include <string>
#include <algorithm>

#include <d3d9.h>
#include <d3dx9tex.h>
#include <d3dx9.h>

#include "dependencies/utils/xor_str.hpp"
#include "dependencies/utils/utils.hpp"
#include "dependencies/utils/math.hpp"
#include "dependencies/utils/hitmarker_sound.hpp"

#include "globals.hpp"

/* imgui, fonts, images */
#include "dependencies/rendering/imgui/imgui.h"
/* ... */

void outline_text(ImVec2 position, ImU32 color, const char* text, float alpha = 1.f)
{
	ImU32 black = ImColor(0.f, 0.f, 0.f, alpha);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 0, position.y - 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 0, position.y + 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 1, position.y + 0), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x - 1, position.y + 0), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 1, position.y + 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x - 1, position.y + 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 1, position.y - 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x - 1, position.y - 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x - 1, position.y - 1), black, text);
	ImGui::GetBackgroundDrawList()->AddText(position, color, text);
}

#include "dependencies/communication/communication.hpp"
#include "dependencies/communication/driver.hpp"
#include "dependencies/communication/memory.hpp"

uintptr_t get_game_component(uintptr_t game_object, const char* component_name)
{
	char name[256];

	uintptr_t test = memory.read<uintptr_t>(game_object + 0x30);

	if (!test)
		return NULL;

	for (int i = 0x8; i < 0x1000; i += 0x10)
	{
		uintptr_t fields = memory.read<uintptr_t>(memory.read<uintptr_t>(test + i) + 0x28);

		if (!fields)
			return NULL;

		uintptr_t name_pointer = memory.read<uintptr_t>(memory.read<uintptr_t>(memory.read<uintptr_t>(fields)) + 0x48);

		if (!name_pointer)
			return NULL;

		memory.read(name_pointer, name, 256);

		if (strcmp(name, component_name) == 0)
			return fields;
	}

	return NULL;
}

std::string get_unicode_str(uintptr_t address, size_t size)
{
	address = address + 0x14;
	char16_t wcharTemp[64] = { '\0' };
	memory.read(address, wcharTemp, size * 2);
	std::string u8_conv = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(wcharTemp);
	return u8_conv;
}

#include "sdk/offsets.hpp"

#include "sdk/classes/bones.hpp"
#include "sdk/classes/camera.hpp"
#include "sdk/classes/world.hpp"
#include "sdk/classes/gameobjectmanager.hpp"
#include "sdk/classes/magazine.hpp"
#include "sdk/classes/profile.hpp"
#include "sdk/classes/physical.hpp"
#include "sdk/classes/movement.hpp"
#include "sdk/classes/shot.hpp"
#include "sdk/classes/ballistics.hpp"
#include "sdk/classes/weaponanimation.hpp"
#include "sdk/classes/player.hpp"

#include "sdk/players.hpp"
#include "sdk/game/entity_list.hpp"

#include "sdk/features.hpp"

/*
*	Include your overlay here
*/