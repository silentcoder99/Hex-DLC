#pragma once
#include <cmath>

struct Vec2 {
	int x;
	int y;

	Vec2() {
		x = 0;
		y = 0;
	}

	Vec2(int xx, int yy) {
		x = xx;
		y = yy;
	}

	float distance(Vec2 other) {
		return std::sqrt(std::pow((other.x + 0.5 * other.y) - (x + 0.5 * y), 2) + std::pow(other.y - y, 2));
	}

	bool operator==(Vec2 other) {
		return x == other.x && y == other.y;
	}
};