#pragma once

namespace utils
{
	std::string random_str(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
			{
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
			};

			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

	std::string random_lower_str(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
			{
				"0123456789"
				"abcdefghijklmnopqrstuvwxyz"
			};

			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

	int random_int(int min, int max)
	{
		static bool first = true;
		if (first)
		{
			srand((unsigned int)time(NULL));
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}

	bool is_running(const char* name)
	{
		return FindWindowA(NULL, name);
	}

	HANDLE get_process_id(LPCWSTR name)
	{
		if (!name)
			return NULL;

		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		HANDLE process_id = NULL;

		if (handle == INVALID_HANDLE_VALUE)
			return process_id;

		PROCESSENTRY32W entry{};
		entry.dwSize = sizeof(PROCESSENTRY32W);

		if (Process32FirstW(handle, &entry))
		{
			if (!_wcsicmp(name, entry.szExeFile))
				process_id = (HANDLE)entry.th32ProcessID;

			else while (Process32NextW(handle, &entry))
			{
				if (!_wcsicmp(name, entry.szExeFile))
					process_id = (HANDLE)entry.th32ProcessID;
			}
		}

		CloseHandle(handle);

		return (HANDLE)process_id;
	}
}