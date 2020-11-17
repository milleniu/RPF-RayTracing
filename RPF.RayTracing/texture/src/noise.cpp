#include "texture/include/noise.h"

ray_tracing::texture::noise::noise(const float sc)
	:scale_(sc) {}

ray_tracing::color ray_tracing::texture::noise::value(float u, float v, const point3& p) const
{
	return color{ 1, 1, 1 } *0.5F * (1.F + sin(scale_ * p.a[2] + 10 * perlin_noise_.turbulence(p)));
}
