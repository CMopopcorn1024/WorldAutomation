#include "Electronic.h"
#include <iostream>
Electronic::Electronic(float scale, float rotation, int LocalX, int LocalY, BuildMap *map, ElectronicPreset config, std::vector<Electronic *> connectedElectronics)
	: ImageObject("Assets/Unloaded.png", scale, rotation), LocalX(LocalX), LocalY(LocalY), map(map), config(config)
{
	position = map->getPosition(LocalX, LocalY);
	ImageObject::makeSize(50);

	if (!map->addElectronic(LocalX, LocalY, this))
	{
		delete (this);
	}
}

float Electronic::AddPower(float delta)
{
	currentPowerStorage += delta;
	if (currentPowerStorage > config.powerStorageCapacity)
	{
		float excess = currentPowerStorage - config.powerStorageCapacity;
		currentPowerStorage = config.powerStorageCapacity;
		return excess;
	}
	return 0;
}

void Electronic::sendPower(float dt)
{
	for (Electronic *e : connectedElectronics)
	{
		float returnPower = e->AddPower(config.powerFlowRate * dt);
		currentPowerStorage -= (config.powerFlowRate * dt) - returnPower;
	}
}

void Electronic::connectionMapUpdate(int x, int y)
{
	int dx = x - LocalX;
	int dy = y - LocalY;
	std::pair<int, int> direction = std::make_pair(dx, dy);
	if (std::find(connectionDirections.begin(), connectionDirections.end(), direction) == connectionDirections.end())
	{
		connectionDirections.push_back(direction);
		std::cout << "Adding a connection to " << LocalX << " " << LocalY << "  with direction: " << direction.first << ", " << direction.second << "    new direction count: " << connectionDirections.size() << "    with ID: " << this << std::endl;
	}
}

void Electronic::draw()
{
	ImageObject::draw(position.x - texture->height * scale / 2, position.y - texture->height * scale / 2);
}

void Electronic::connectionElectronicUpdate()
{
}