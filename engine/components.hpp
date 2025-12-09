#pragma once

// Interface
class IComponent {
public:
	virtual ~IComponent() = default;
};

// Implmentations
struct Position: public IComponent {
	float x, y;
};

struct Velocity : public IComponent {
	float dx, dy;
};

struct Transform {

};