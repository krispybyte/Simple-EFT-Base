#pragma once
#include "../../common.hpp"

struct vmatrix_t
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class camera_t
{
public:
	uintptr_t object = NULL;
	Vector3 position{};
	vmatrix_t vmatrix{};
} camera;

bool world_to_screen(const Vector3& world, Vector2& screen)
{
	vmatrix_t vmatrix = memory.read<vmatrix_t>(camera.object + 0xDC /*0x2E4*/);

	Vector3 trans_vec{ vmatrix._14, vmatrix._24, vmatrix._34 };
	Vector3 right_vec{ vmatrix._11, vmatrix._21, vmatrix._31 };
	Vector3 up_vec{ vmatrix._12, vmatrix._22, vmatrix._32 };

	float w = trans_vec.dot(world) + vmatrix._44;

	if (w < 0.098f) return false;

	float y = up_vec.dot(world) + vmatrix._42;
	float x = right_vec.dot(world) + vmatrix._41;

	Vector2 temp = Vector2((globals.screen_center.x) * (1 + x / w), (globals.screen_center.y) * (1 - y / w));

	if (!temp.y) 
		return false;

	screen = temp;
	return true;
}