#pragma once
#include "../../common.hpp"

struct base_object_t
{
	uint64_t previousObjectLink; //0x0000
	uint64_t nextObjectLink; //0x0008
	uint64_t object; //0x0010
};

struct game_object_manager_t
{
	uint64_t lastTaggedObject; //0x0
	uint64_t taggedObjects; //0x8
	uint64_t lastMainCameraTagged; // 0x10
	uint64_t MainCameraTagged; // 0x18
	uint64_t lastActiveObject; //0x20
	uint64_t activeObjects; // 0x28
};

class GameObjectManager
{
private:
public:
	uintptr_t get_fps_camera()
	{
		auto camera_objects = memory.read<std::array<uint64_t, 2>>(reinterpret_cast<uintptr_t>(this) + offsetof(game_object_manager_t, lastMainCameraTagged));

		char name[256];
		uint64_t class_name_ptr = 0x00;

		base_object_t activeObject = memory.read<base_object_t>(camera_objects[1]);
		base_object_t lastObject = memory.read<base_object_t>(camera_objects[0]);

		if (activeObject.object)
		{
			while (activeObject.object != 0 && activeObject.object != lastObject.object)
			{
				class_name_ptr = memory.read<uint64_t>(activeObject.object + 0x60);
				memory.read(class_name_ptr + 0x0, &name, sizeof(name));

				if (strcmp(name, _("BaseOpticCamera(Clone)"/*"FPS Camera"*/)) == 0)
				{
					auto unk1 = memory.read<uintptr_t>(activeObject.object + 0x30);
					return memory.read<uintptr_t>(unk1 + 0x18);
				}

				activeObject = memory.read<base_object_t>(activeObject.nextObjectLink);
			}
		}

		if (lastObject.object)
		{
			class_name_ptr = memory.read<uint64_t>(lastObject.object + 0x60);
			memory.read(class_name_ptr + 0x0, &name, 256);

			if (strcmp(name, _("BaseOpticCamera(Clone)"/*"FPS Camera"*/)) == 0)
			{
				auto unk1 = memory.read<uintptr_t>(lastObject.object + 0x30);
				return memory.read<uintptr_t>(unk1 + 0x18);
			}
		}

		return NULL;
	}



	World* get_game_world()
	{
		auto camera_objects = memory.read<std::array<uintptr_t, 2>>(reinterpret_cast<uintptr_t>(this) + offsetof(game_object_manager_t, lastActiveObject));

		char name[256];
		uintptr_t class_name_ptr = 0x00;

		base_object_t activeObject = memory.read<base_object_t>(camera_objects[1]);
		base_object_t lastObject = memory.read<base_object_t>(camera_objects[0]);

		if (activeObject.object)
		{
			while (activeObject.object != 0 && activeObject.object != lastObject.object)
			{
				class_name_ptr = memory.read<uintptr_t>(activeObject.object + 0x60);
				memory.read(class_name_ptr + 0x0, &name, sizeof(name));

				if (strcmp(name, _("GameWorld")) == 0)
				{
					auto unk1 = memory.read<uintptr_t>(activeObject.object + 0x30);
					auto unk2 = memory.read<uintptr_t>(unk1 + 0x18);
					return memory.read<World*>(unk2 + 0x28);
				}

				activeObject = memory.read<base_object_t>(activeObject.nextObjectLink);
			}
		}

		if (lastObject.object)
		{
			class_name_ptr = memory.read<uint64_t>(lastObject.object + 0x60);
			memory.read(class_name_ptr + 0x0, name, 256);

			if (strcmp(name, _("GameWorld")) == 0)
			{
				auto unk1 = memory.read<uintptr_t>(lastObject.object + 0x30);
				auto unk2 = memory.read<uintptr_t>(unk1 + 0x18);
				return memory.read<World*>(unk2 + 0x28);
			}
		}
		return nullptr;
	}
};