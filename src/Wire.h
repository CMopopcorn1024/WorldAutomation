#pragma once
#include "Electronic.h"
#include "ElectronicPresets.h"

class Wire : public Electronic
{
public:
	Wire(int LocalX, int LocalY, BuildMap *map, WirePreset config);
	void connectionElectronicUpdate() override;
};
