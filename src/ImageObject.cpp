#include "ImageObject.h"

#include <iostream>

std::unordered_map<const char *, Texture2D> ImageObject::textures;
ImageObject::ImageObject(const char *texturePath, float scale, float rotation) : scale(scale), rotation(rotation)
{
	if (textures.find(texturePath) == textures.end())
		textures.emplace(texturePath, LoadTexture(texturePath));
	this->texture = &textures[texturePath];
}

void ImageObject::draw(float x, float y)
{
	if (texture->id == 0)
		std::cout << "Texture not loaded correctly" << std::endl;

	Rectangle source = {0, 0, (float)texture->width, (float)texture->height};
	Rectangle dest = {x, y, (float)texture->width * scale, (float)texture->height * scale};
	Vector2 origin = {texture->width / 2.0f * scale, texture->height / 2.0f * scale};

	DrawTexturePro(*texture, source, dest, origin, rotation, WHITE);
}

void ImageObject::makeSize(float size)
{
	float width = static_cast<float>(texture->width);
	float height = static_cast<float>(texture->height);
	float maxDimension = std::max(width, height);
	scale = size / maxDimension;
}

void ImageObject::setTexture(const char *texturePath)
{
	if (textures.find(texturePath) == textures.end())
		textures.emplace(texturePath, LoadTexture(texturePath));
	this->texture = &textures[texturePath];
}