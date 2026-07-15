#pragma once

#include <iostream>

#include "raylib.h"
#include "ImageObject.h"
#include "BuildMap.h"

// CPhysics
#include <CPhysics/Object.h>
namespace CPh = CPhysics;

class Player : public CPhysics::Object, public ImageObject
{
public:
	Player(json data, float scale, float rotation, float speed, BuildMap *map, const char *BuildModeTexturePath);

	void draw() override;

	void update(float dt);

private:
	float speed;
	void checkInput(float dt);
	bool buildMode = false;
	BuildMap *map;
	const char *BuildModeTexturePath;
	const char *PlayerTexturePath;
};