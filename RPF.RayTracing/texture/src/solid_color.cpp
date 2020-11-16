#include "texture/include/solid_color.h"

ray_tracing::texture::solid_color::solid_color(const color c)
	: color_value_(c) {}

ray_tracing::texture::solid_color::solid_color(const float red, const float green, const float blue)
	: solid_color(color{ red, green, blue }) {}

ray_tracing::color ray_tracing::texture::solid_color::value(float u, float v, const point3& p) const
{
	return color_value_;
}

