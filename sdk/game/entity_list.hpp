#pragma once
#include "../../common.hpp"
#include "../../dependencies/rendering/imgui/imgui.h"

struct player_info_t
{
	std::string name;
	Vector2 head_location;
	Vector2 feet_location;
	bone_struct_t player_bones;
};

class entity_list_t
{
public:
	GameObjectManager* game_object_manager{};
	World* world{};
	std::vector<uintptr_t> players_list{};

	void update()
	{
		while (true)
		{
			game_object_manager = memory.read<GameObjectManager*>(globals.unityplayer + 0x17F8D28);
			camera.object = game_object_manager->get_fps_camera();

			world = game_object_manager->get_game_world();
			
			if (world)
			{
				players_list = world->get_player_list();
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		}
	}

	void run()
	{
		camera.position = memory.read<Vector3>(camera.object + 0x42C);
		
		for (auto& player_address : players_list)
		{
			player_t* player = reinterpret_cast<player_t*>(player_address);

			if (player->is_local_player())
			{
				players::local = player;
				continue;
			}

			const Vector3 head_location = player->get_bone(bones::HumanHead);
			const Vector3 center_location = (player->get_bone(bones::HumanLFoot) + player->get_bone(bones::HumanRFoot)) / 2;

			player_info_t info{};

			/* ESP */
			if (world_to_screen({ head_location.x, head_location.y + 0.25f, head_location.z }, info.head_location)
				&& world_to_screen({ center_location.x, center_location.y - 0.125f, center_location.z }, info.feet_location))
			{
				const ImVec2 size = { (info.feet_location.y - info.head_location.y) / 2, info.feet_location.y - info.head_location.y };

				/*
				*	esp here
				*/
			}
		}
	}
} entity_list;