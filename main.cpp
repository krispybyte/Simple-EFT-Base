#pragma once
#include "common.hpp"

int main()
{
	SetConsoleTitleA(utils::random_lower_str(utils::random_int(16, 28)).c_str());

	if (!driver.attach(_(L"EscapeFromTarkov.exe")))
	{
		printf(_("[-] Attach failure!"));
		getchar();
		return EXIT_FAILURE;
	}

	globals.unityplayer = memory.module_base_alternative(_("UnityPlayer.dll"));

	printf(_("[!] PID @ %d\n"), globals.pid);
	printf(_("[!] UnityPlayer.dll @ 0x%p\n"), globals.unityplayer);

	std::thread([&]()
	{ 
		entity_list.update();
	}).detach();

	std::thread([&]()
	{ 
		features.run();
	}).detach();
	
	std::thread([&]()
	{ 
		aimbot.run();
	}).detach();

	/*
	*	run your overlay here instead of the while true loop
	*/

	while (true) {}

	getchar();
	return EXIT_SUCCESS;
}