#pragma once
#include <cmath>

// For use to represent tile coordinates on a hex board
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

	double distance(Vec2 other) const {
		return std::sqrt(std::pow((other.x + 0.5 * other.y) - (x + 0.5 * y), 2) + std::pow(other.y - y, 2));
	}

	bool operator==(Vec2 other) const {
		return x == other.x && y == other.y;
	}

	Vec2 operator+(Vec2 other) const {
		return Vec2(x + other.x, y + other.y);
	}

	size_t hash() const{
		return x*11 + y;
	}
};

namespace std {

	template <>
	struct hash<Vec2>
	{
		std::size_t operator()(const Vec2& k) const
		{
			return k.hash();
		}
	};

}