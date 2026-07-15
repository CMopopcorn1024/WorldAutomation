#pragma once
#include "ImageObject.h"
#include <CPhysics/Object.h>

#include <raylib.h>

namespace CPh = CPhysics;

class Harvestable : public ImageObject, public CPhysics::Object
{
public:
	Harvestable(json data, float scale, float rotation);
	void draw() override;
};
