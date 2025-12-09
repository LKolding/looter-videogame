#pragma once

// Interface
class IComponent {
public:
	virtual ~IComponent() = default;
};

// Implmentations
struct Position: public IComponent {
	float x = 0.0;
	float y = 0.0;
};

struct Velocity : public IComponent {
	float dx = 0.0;
	float dy = 0.0;
};

struct Transform {

};