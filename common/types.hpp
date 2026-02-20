#pragma once

// Matches sprite sheet row order (crucial for animation)
// 0 = South, 1 = West, 2 = East, 3 = North
enum class Direction : uint8_t
{
    South = 0,
    West  = 1,
    East  = 2,
    North = 3
};
namespace std {
template<> struct hash<Direction> {
    size_t operator()(Direction d) const noexcept { return static_cast<size_t>(d); }
};
}


enum class State : uint8_t 
{ 
    Moving=0, 
    Idle=1, 
    Attacking=2 
};