#pragma once
#include "common.hpp"

class globals_t
{
private:
public:
	HANDLE pid{};
	uintptr_t peb{};
	uintptr_t unityplayer{};

	const Vector2 screen = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	const Vector2 screen_center = { GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2 };

	float accent_color[4]{ 0.75f, 0.29f, 0.54f, 1.f };
} globals;