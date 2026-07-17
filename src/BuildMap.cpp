#include "BuildMap.h"
#include "Electronic.h"

#include <iostream>
BuildMap::BuildMap(int cellSize) : cellSize(cellSize) {}

bool BuildMap::addElectronic(int x, int y, Electronic *electronic)
{
	std::pair<int, int> key = std::make_pair(x, y);
	newElectricPosition.push_back(key);
	if (electronicsMap.find(key) != electronicsMap.end())
	{
		return false;
	}
	electronicsMap.emplace(key, electronic);

	return true;
}

Electronic *BuildMap::getElectronic(int x, int y)
{
	std::pair<int, int> key = std::make_pair(x, y);
	auto it = electronicsMap.find(key);
	if (it != electronicsMap.end())
	{
		return it->second;
	}
	return nullptr;
}

void BuildMap::draw(CPh::Vector2 pos)
{
	for (const auto &entry : electronicsMap)
	{
		entry.second->draw();
	}

	std::pair<int, int> cell = positionToCell(pos);
	CPh::Vector2 cellPos = getPosition(cell);
	DrawRectangle(cellPos.x, cellPos.y, cellSize, cellSize, BLACK);
}

void BuildMap::updateConnectionMaps()
{
	std::vector<Electronic *> electronicsToUpdate;
	for (std::pair<int, int> pos : newElectricPosition)
	{
		Electronic *electronic = getElectronic(pos.first, pos.second);

		electronicsToUpdate.push_back(electronic);

		Electronic *nearElectronic = getElectronic(electronic->getLocalX() + 1, electronic->getLocalY());
		if (nearElectronic != nullptr)
		{
			nearElectronic->connectionMapUpdate(pos.first, pos.second);
			electronic->connectionMapUpdate(pos.first + 1, pos.second);
			electronicsToUpdate.push_back(nearElectronic);
		}

		if ((nearElectronic = getElectronic(electronic->getLocalX() - 1, electronic->getLocalY())) != nullptr)
		{
			nearElectronic->connectionMapUpdate(pos.first, pos.second);
			electronic->connectionMapUpdate(pos.first - 1, pos.second);
			electronicsToUpdate.push_back(nearElectronic);
		}

		if ((nearElectronic = getElectronic(electronic->getLocalX(), electronic->getLocalY() + 1)) != nullptr)
		{
			nearElectronic->connectionMapUpdate(pos.first, pos.second);
			electronic->connectionMapUpdate(pos.first, pos.second + 1);
			electronicsToUpdate.push_back(nearElectronic);
		}

		if ((nearElectronic = getElectronic(electronic->getLocalX(), electronic->getLocalY() - 1)) != nullptr)
		{
			nearElectronic->connectionMapUpdate(pos.first, pos.second);
			electronic->connectionMapUpdate(pos.first, pos.second - 1);
			electronicsToUpdate.push_back(nearElectronic);
		}
	}
	for (Electronic *e : electronicsToUpdate)
	{
		e->connectionElectronicUpdate();
	}

	newElectricPosition.clear();
}

std::pair<int, int> BuildMap::positionToCell(CPh::Vector2 pos) const
{
	std::pair<int, int> cell;
	cell.first = pos.x / cellSize;
	cell.second = pos.y / cellSize;
	return cell;
}
