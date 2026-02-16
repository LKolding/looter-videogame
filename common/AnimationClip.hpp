#pragma once
#include <cstdint>
#include <vector>

struct AnimationClip
{
    uint16_t row;
    uint16_t frame_count;
    float frame_time;

};

struct AnimationSet
{
	std::vector<AnimationClip> animations;
};

