#pragma once
#include "../common.hpp"

class features_t
{
private:
public:
	void run()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			players::local->weapon()->set_no_recoil();
			//players.local->weapon()->set_no_sway();

			players::local->physical()->set_stamina(100.f);
			//players.local->physical()->set_no_fall_damage();
			
			players::local->profile()->magazine()->set_fast_reload();
			
			const std::vector<Shot*> shot_list = players::local->weapon()->get_ballistics()->get_shot_list();
			for (auto& shot : shot_list)
			{
				if (shot->has_hit_player())
					PlaySoundA(hitmarker_sound, NULL, SND_MEMORY | SND_SYNC);
			}
		}
	}
} features;

class aimbot_t
{
private:
	Vector3 get_target()
	{
		float smallest_distance = FLT_MAX;

		Vector3 final_target_position{};

		for (auto& current_entity : entity_list.players_list)
		{
			player_t* player = reinterpret_cast<player_t*>(current_entity);

			if (player->is_local_player()) 
				continue;

			//if (player->is_dead())
			//	continue;

			const Vector3 head = player->get_bone(bones::HumanHead/*HumanSpine3*/);

			Vector2 screen_head{};

			if (!world_to_screen(head, screen_head))
				continue;

			float distance = screen_head.distance(globals.screen_center);

			float fov_limit = 80.f;

			if (distance < smallest_distance && fov_limit >= distance)
			{
				final_target_position = head;
				smallest_distance = distance;
			}
		}

		return final_target_position;
	}
public:
	void run()
	{
		while (true)
		{
			Vector3 target = get_target();

			if (GetAsyncKeyState(VK_XBUTTON2) && players::local && target.is_valid())
				players::local->movement()->set_viewangles(calculate_angle(players::local->weapon()->get_fireport(), target));

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
} aimbot;