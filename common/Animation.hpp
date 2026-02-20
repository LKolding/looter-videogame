#pragma once
#include <cstdint>
#include <vector>

#include "../common/types.hpp"


struct AnimationFrame
{
    int x;
    int y;

    int w;
    int h;

    int duration; //miliseconds
};


struct AnimationClip // one for each "facing"
{
    std::vector<AnimationFrame> frames;
};


struct AnimationSet // one for each texture
{
    std::unordered_map<Direction, AnimationClip> _animations;
};

