#pragma once
#include "../../common.hpp"

class Profile
{
public:
	Magazine* magazine()
	{
		return memory.read<Magazine*>(reinterpret_cast<uintptr_t>(this) + 0x60);
	}

	std::string get_name()
	{
        const uintptr_t info = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x28);

        const std::uintptr_t name_pointer = memory.read<std::uintptr_t>(info + 0x10);
        const int name_size = memory.read<int>(name_pointer + 0x10);

        return get_unicode_str(name_pointer, name_size);
	}

	bool is_scav()
	{
		const uintptr_t player_info = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x28);
        
        const uintptr_t account_id = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x18);
		const int registration_date = memory.read<int>(player_info + 0x5C);

		return (!registration_date && account_id);
	}

    std::string get_role()
    {
        const uintptr_t info = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x28);

        if (!info)
            return _("");

        const uintptr_t settings = memory.read<uintptr_t>(info + 0x38);

        if (!settings)
            return _("");

       const unsigned int role = memory.read<unsigned int>(settings + 0x10);

       switch (role)
       {
           case 1:
               return _("Sniper Scav");
               break;
           case 2:
               return _("Scav");
               break;
           case 8:
               return _("Reshala");
               break;
           case 16:
               return _("Follower");
               break;
           case 32:
               return _("Reshala Demon");
               break;
           case 64:
               return _("Killa");
               break;
           case 128:
               return _("Shturman");
               break;
           case 256:
               return _("Shturman Demon");
               break;
           case 512:
               return _("Raider");
               break;
           case 1024:
               return _("Cultist");
               break;
           case 2048:
               return _("Gluhar");
               break;
           case 4096:
               return _("Gluhar Demon");
               break;
           case 8192:
               return _("Gluhar Demon");
               break;
           case 16384:
               return _("Gluhar Demon");
               break;
           case 32768:
               return _("Gluhar Demon");
               break;
           case 65536:
               return _("Sanitar Demon");
               break;
           case 131072:
               return _("Sanitar");
               break;
           case 524288:
               return _("Raider");
               break;
           case 4194304:
               return _("Tagilla");
               break;
       }

       return _("");
    }
};