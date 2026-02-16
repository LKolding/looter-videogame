#pragma once

#include "../common/TextureID.hpp"

struct RenderItem 
{
	TextureID id;
	float source_x;
	float source_y;

	float width;
	float height;

	float x;
	float y;
};
