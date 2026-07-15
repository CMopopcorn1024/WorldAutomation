#include "Player.h"
#include "BuildMap.h"
#include "Wire.h"
#include "ElectronicPresets.h"

Player::Player(json data, float scale, float rotation, float speed, BuildMap *map, const char *BuildModeTexturePath) : CPh::Object(data), PlayerTexturePath(data["ImagePath"].get<std::string>().c_str()), ImageObject(data["ImagePath"].get<std::string>().c_str(), scale, rotation), speed(speed), map(map), BuildModeTexturePath(BuildModeTexturePath)
{
}

void Player::update(float dt)
{
	checkInput(dt);
}

void Player::checkInput(float dt)
{
	CPh::Vector2 changeVel(0, 0);
	if (IsKeyDown(KEY_W))
		changeVel.y -= 1;
	if (IsKeyDown(KEY_S))
		changeVel.y += 1;
	if (IsKeyDown(KEY_A))
		changeVel.x -= 1;
	if (IsKeyDown(KEY_D))
		changeVel.x += 1;
	changeVel = changeVel.Normalized() * speed;
	velocity += changeVel * 100 * dt;

	if (IsKeyPressed(KEY_B))
	{
		buildMode = !buildMode;
		if (buildMode)
		{
			setTexture(BuildModeTexturePath);
		}
		else
		{
			setTexture(PlayerTexturePath);
		}
	}

	if (buildMode)
	{

		if (IsKeyDown(KEY_ONE))
		{
			std::cout << "building" << std::endl;
			std::pair<int, int> cell = map->positionToCell(position);
			new Wire(cell.first, cell.second, map, ObjectPresets::BasicWire);
			map->updateConnectionMaps();
		}
	}
}

void Player::draw()
{
	ImageObject::draw(position.x, position.y);
	/*for (CPh::Rectangle* rect : rects)
	{
		DrawRectangle(rect->topLeft.x, rect->topLeft.y, rect->bottomRight.x - rect->topLeft.x, rect->bottomRight.y - rect->topLeft.y, RED);
	}*/
}