#include "texture/include/checker.h"
#include "texture/include/solid_color.h"

ray_tracing::texture::checker::checker(const std::shared_ptr<texture>& even, const std::shared_ptr<texture>& odd)
	: even_(even), odd_(odd) {}

ray_tracing::texture::checker::checker(color c1, color c2)
	: even_(std::make_shared<solid_color>(c1)), odd_(std::make_shared<solid_color>(c2)) {}

ray_tracing::color ray_tracing::texture::checker::value(const float u, const float v, const point3& p) const
{
	const auto sines = sin(10 * p.a[0]) * sin(10 * p.a[1]) * sin(10 * p.a[2]);
	return (sines < 0 ? odd_ : even_)->value(u, v, p);
}

