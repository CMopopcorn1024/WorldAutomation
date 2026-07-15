#include "Harvestable.h"

Harvestable::Harvestable(json data, float scale, float rotation) : CPh::Object(data), ImageObject(data["ImagePath"].get<std::string>().c_str(), scale, rotation)
{
}

void Harvestable::draw()
{
	ImageObject::draw(position.x, position.y);
	/*for (CPh::Rectangle* rect : rects)
	{
		DrawRectangle(rect->topLeft.x, rect->topLeft.y, rect->bottomRight.x - rect->topLeft.x, rect->bottomRight.y - rect->topLeft.y, RED);
	}*/
}