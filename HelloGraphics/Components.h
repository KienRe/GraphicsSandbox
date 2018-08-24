#pragma once

#include <unordered_map>

using EntityID = int64_t;

struct Position
{
	float x;
	float y;
	float z;
};

struct Velocity
{
	float x;
	float y;
	float z;
};

template <typename Type>
using ComponentMap = std::unordered_map<EntityID, Type>;

using Positions = ComponentMap<Position>;
using Velocities = ComponentMap<Velocity>;

struct Components
{
	Positions positions;
	Velocities velocities;
};