#pragma once
#include <unordered_map>
#include <utility>
#include "raylib.h"

#include <CPhysics/Vector2.h>

class Electronic;

namespace CPh = CPhysics;

struct Pairhash
{
	std::size_t operator()(const std::pair<int, int> &p) const noexcept
	{
		auto hash1 = std::hash<int>{}(p.first);
		auto hash2 = std::hash<int>{}(p.second);
		return hash1 ^ (hash2 << 1);
	}
};
class BuildMap
{
public:
	BuildMap(int cellSize);
	bool addElectronic(int x, int y, Electronic *electronic);
	Electronic *getElectronic(int x, int y);

	CPh::Vector2 getPosition(int x, int y) { return CPh::Vector2(x * cellSize, y * cellSize); }
	CPh::Vector2 getPosition(std::pair<int, int> cell) { return CPh::Vector2(cell.first * cellSize, cell.second * cellSize); }

	CPh::Vector2 getPositionCenter(int x, int y) { return CPh::Vector2(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2); }
	CPh::Vector2 getPositionCenter(std::pair<int, int> cell) { return CPh::Vector2(cell.first * cellSize + cellSize / 2, cell.second * cellSize + cellSize / 2); }

	void draw(CPh::Vector2 pos);
	void updateConnectionMaps();
	std::pair<int, int> positionToCell(CPh::Vector2 pos) const;

private:
	int cellSize;
	std::unordered_map<std::pair<int, int>, Electronic *, Pairhash> electronicsMap;
	std::vector<std::pair<int, int>> newElectricPosition;
};
