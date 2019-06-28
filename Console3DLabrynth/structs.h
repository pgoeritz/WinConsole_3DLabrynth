#pragma once

#include <string>

template<class T>
struct Coordinate {
	T x;
	T y;
};

struct PlayerData {
	Coordinate<float> pos;
	float angle;
};

struct MapData {
	int dimensions;
	std::string data;
};