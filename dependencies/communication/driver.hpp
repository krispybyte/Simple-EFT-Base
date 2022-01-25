#pragma once
#include "../../common.hpp"

class driver_t
{
private:
	/*
	*	removed
	*/
public:
	template <const operations operation_value>
	bool send_cmd(cmd_t* cmd)
	{
		if (!globals.pid)
			return false;

		/*
		*	removed
		*/
	}

	bool attach(LPCWSTR name)
	{
		globals.pid = utils::get_process_id(name);

		/*
		*	removed
		*/

		return globals.pid;
	}
} driver;