#pragma once

// Matches sprite sheet row order (crucial for animation)
// 0 = South, 1 = West, 2 = East, 3 = North
enum class Direction : uint8_t
{
    North,
    South,
    East,
    West
};


enum class State : uint8_t 
{ 
    Idle,
    Moving,
    Attacking
};

using SpriteDefinitionID = std::uint32_t;
// struct SpriteDefinitionID
// {
//     std::uint32_t value;
// };



/* CUSTOM HASH FUNCTIONS */
namespace std {
template<> struct hash<Direction> {
    size_t operator()(Direction d) const noexcept { return static_cast<size_t>(d); }
};
}
