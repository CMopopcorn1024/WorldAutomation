#pragma once
#include "raylib.h"
#include <unordered_map>
class ImageObject
{
public:
	ImageObject(const char *texture, float scale, float rotation);

	virtual void draw(float x, float y);
	virtual void draw() {};
	void makeSize(float size);

protected:
	float rotation, scale;
	Texture2D *texture;
	void setTexture(const char *texturePath);

private:
	static std::unordered_map<const char *, Texture2D> textures;
};
